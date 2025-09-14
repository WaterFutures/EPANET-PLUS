"""
This module tests EPANET-MSX functions.
"""
from epanet_plus import EPyT, EpanetAPI, EpanetConstants


def test_msx_basic():
    epanet_api = EpanetAPI()
    epanet_api.MSXENopen("net2-cl2.inp", "net2-cl2.rpt", "")
    epanet_api.MSXopen("net2-cl2.msx")

    epanet_api.gettitle()
    epanet_api.MSXgetspecies(1)
    epanet_api.MSXgetID(3, 1)

    epanet_api.MSXclose()
    epanet_api.MSXENclose()


def test_simulation():
    with EPyT("net2-cl2.inp", use_project=False) as epanet_api:
        epanet_api.load_msx_file("net2-cl2.msx")

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
