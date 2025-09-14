"""
This module tests the EPANET functions.
"""
from epanet_plus import EpanetAPI, EpanetConstants


def test():
    epanet_api = EpanetAPI()
    epanet_api.open("net2-cl2.inp", "net2-cl2.rpt", "")

    assert epanet_api.gettitle() is not None
    assert epanet_api.getcount(EpanetConstants.EN_NODECOUNT) > 0
    assert epanet_api.getcount(EpanetConstants.EN_LINKCOUNT) > 0
    assert epanet_api.getcount(EpanetConstants.EN_TANKCOUNT) > 0

    epanet_api.close()
