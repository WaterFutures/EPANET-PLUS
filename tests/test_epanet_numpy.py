"""
This module tests the NumPy versions of the methods implemented in the class EpanetAPI.
"""
import os
import numpy as np
from epanet_plus import EPyT, EpanetConstants

def test_getnodevalues_numpy(): 
    def __test_code(epanet_api: EPyT):
        values = epanet_api.getnodevalues_numpy(EpanetConstants.EN_ELEVATION)
        expected = epanet_api.getnodevalues(EpanetConstants.EN_ELEVATION)

        # test if it is a numpy array
        assert isinstance(values, np.ndarray)
        # test if both methods have the same results
        assert np.allclose(values, expected)
        # test if we have a 1D array
        assert values.ndim == 1
        # test if we have only one value per node
        assert len(values) == len(epanet_api.get_all_nodes_id())

    with EPyT(os.path.join("tests", "net2-cl2.inp")) as epanet_api:
        __test_code(epanet_api)

    with EPyT(os.path.join("tests", "net2-cl2.inp"), use_project=True) as epanet_api:
        __test_code(epanet_api)


def test_getlinkvalues_numpy(): 
    def __test_code(epanet_api: EPyT):
        values = epanet_api.getlinkvalues_numpy(EpanetConstants.EN_DIAMETER)
        expected = epanet_api.getlinkvalues(EpanetConstants.EN_DIAMETER)

        assert isinstance(values, np.ndarray)
        assert np.allclose(values, expected)
        assert values.ndim == 1
        assert len(values) == len(epanet_api.get_all_links_id())

    with EPyT(os.path.join("tests", "net2-cl2.inp")) as epanet_api:
        __test_code(epanet_api)

    with EPyT(os.path.join("tests", "net2-cl2.inp"), use_project=True) as epanet_api:
        __test_code(epanet_api)


def test_setnodevalues_numpy():
    def __test_code(epanet_api: EPyT):
        values = epanet_api.getnodevalues_numpy(EpanetConstants.EN_ELEVATION)
        new_values = values.copy()
        new_values[0] += 1.0

        bad_index = epanet_api.setnodevalues_numpy(EpanetConstants.EN_ELEVATION, new_values)

        result = epanet_api.getnodevalues_numpy(EpanetConstants.EN_ELEVATION)

        assert isinstance(result, np.ndarray)
        assert np.allclose(result, new_values)
        assert bad_index == 0
        
    with EPyT(os.path.join("tests", "net2-cl2.inp")) as epanet_api:
        __test_code(epanet_api)
        
    with EPyT(os.path.join("tests", "net2-cl2.inp"), use_project=True) as epanet_api:
        __test_code(epanet_api)

def test_setlinkvalues_numpy():
    def __test_code(epanet_api: EPyT):
        values = epanet_api.getlinkvalues_numpy(EpanetConstants.EN_DIAMETER)
        new_values = values.copy()
        new_values[0] += 1.0

        bad_index = epanet_api.setlinkvalues_numpy(EpanetConstants.EN_DIAMETER, new_values)

        result = epanet_api.getlinkvalues_numpy(EpanetConstants.EN_DIAMETER)

        assert isinstance(result, np.ndarray)
        assert np.allclose(result, new_values)
        assert bad_index == 0

    with EPyT(os.path.join("tests", "net2-cl2.inp")) as epanet_api:
        __test_code(epanet_api)
        
    with EPyT(os.path.join("tests", "net2-cl2.inp"), use_project=True) as epanet_api:
        __test_code(epanet_api)

    


    

    


