"""
This module tests EPANET-MSX functions.
"""
import ctypes
import os

import epanet
import pytest

from epanet_plus import EPyT, EpanetAPI, EpanetConstants


def test_msx_basic():
    epanet_api = EpanetAPI()
    epanet_api.MSXENopen(os.path.join("tests", "net2-cl2.inp"),
                         os.path.join("tests", "net2-cl2.rpt"), "")
    epanet_api.MSXopen(os.path.join("tests", "net2-cl2.msx"))

    epanet_api.gettitle()
    epanet_api.MSXgetspecies(1)
    epanet_api.MSXgetID(3, 1)

    epanet_api.MSXclose()
    epanet_api.MSXENclose()


def test_simulation():
    with EPyT(os.path.join("tests", "net2-cl2.inp"), use_project=False) as epanet_api:
        epanet_api.load_msx_file(os.path.join("tests", "net2-cl2.msx"))

        epanet_api.MSXsolveH()

        epanet_api.MSXinit(0)
        while True:
            _, tleft = epanet_api.MSXstep()

            for idx in epanet_api.get_all_nodes_idx():
                assert epanet_api.MSXgetqual(EpanetConstants.MSX_NODE, idx, 1) >= 0
            for idx in epanet_api.get_all_pipes_idx():
                assert epanet_api.MSXgetqual(EpanetConstants.MSX_LINK, idx, 1) >= 0

            if tleft == 0:
                break


@pytest.mark.skipif(not os.path.exists("/dev/fd"),
                    reason="File descriptor counting requires /dev/fd")
def test_msx_temp_name_does_not_leak_file_descriptors(tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)

    library = ctypes.CDLL(epanet.__file__)
    get_temp_name = library.MSXutils_getTempName
    get_temp_name.argtypes = [ctypes.POINTER(ctypes.c_char)]
    get_temp_name.restype = ctypes.c_char_p

    initial_fd_count = len(os.listdir("/dev/fd"))

    for _ in range(100):
        temp_name = ctypes.create_string_buffer(1024)
        assert get_temp_name(temp_name) is not None
        os.remove(temp_name.value.decode())

    final_fd_count = len(os.listdir("/dev/fd"))

    assert final_fd_count <= initial_fd_count + 1