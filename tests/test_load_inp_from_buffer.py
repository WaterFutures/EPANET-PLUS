"""
This module tests the EPANET-PLUS function for loading an .inp file from a buffer.
"""
import epanet
from epanet_plus import EpanetConstants


def test_load_from_buffer():
    inp_buffer = ""
    with open("net2-cl2.inp", "rt") as f_in:
        inp_buffer = "".join(f_in.readlines())

    assert epanet.ENopenfrombuffer(inp_buffer, "net2-cl2.inp", "net2-cl2.rpt", "") == (0,)

    assert epanet.ENgettitle() == (0, "EPANET Example Network 2", "", "")
    assert epanet.ENgetcount(EpanetConstants.EN_NODECOUNT)[1] > 0

    epanet.ENclose()
