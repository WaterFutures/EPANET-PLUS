"""
This module tests the EPANET-PLUS function for loading an .inp file from a buffer.
"""
import os
import tempfile
import epanet
from epanet_plus import EpanetConstants, EPyT


def test_load_from_buffer():
    inp_buffer = ""
    with open(os.path.join("tests", "net2-cl2.inp"), "rt") as f_in:
        inp_buffer = "".join(f_in.readlines())

    assert epanet.ENopenfrombuffer(inp_buffer, os.path.join("tests", "net2-cl2.inp"),
                                   os.path.join("tests", "net2-cl2.rpt"), "") == (0,)

    assert epanet.ENgettitle() == (0, "EPANET Example Network 2", "", "")
    assert epanet.ENgetcount(EpanetConstants.EN_NODECOUNT)[1] > 0

    epanet.ENclose()


def test_epyt_load_from_buffer():
    def __test_code(epanet_api: EPyT):
        epanet_api.openH()
        epanet_api.initH(EpanetConstants.EN_NOSAVE)

        epanet_api.openQ()
        epanet_api.initQ(EpanetConstants.EN_NOSAVE)

        tstep = 1
        while tstep > 0:
            epanet_api.runH()
            epanet_api.runQ()

            assert len(epanet_api.getnodevalues(EpanetConstants.EN_PRESSURE)) > 0
            assert len(epanet_api.getlinkvalues(EpanetConstants.EN_FLOW)) > 0
            assert len(epanet_api.getnodevalues(EpanetConstants.EN_QUALITY)) > 0
            assert len(epanet_api.getlinkvalues(EpanetConstants.EN_QUALITY)) > 0            

            tstep = epanet_api.nextH()
            epanet_api.nextQ()

        epanet_api.closeQ()
        epanet_api.closeH()

    # Load .inp file into buffer
    inp_buffer = ""
    with open(os.path.join("tests", "net2-cl2.inp"), "rt") as f_in:
        inp_buffer = "".join(f_in.readlines())

    # Load .inp buffer into EPANET via EPyT
    with EPyT(os.path.join(tempfile.gettempdir(), "net2-cl2.inp"), inp_buffer=inp_buffer) as epanet_api:
        __test_code(epanet_api)

    with EPyT(os.path.join(tempfile.gettempdir(), "net2-cl2.inp"), use_project=True,
              inp_buffer=inp_buffer) as epanet_api:
        __test_code(epanet_api)
