"""
This module tests the toolkit functions implemented in the clas EPyT.
"""
from epanet_plus import EPyT, EpanetConstants


def test_topology():
    def __test_code(epanet_api: EPyT):
        assert len(epanet_api.get_all_nodes_id()) > 0
        assert len(epanet_api.get_all_links_id()) > 0

        assert len(epanet_api.get_all_nodes_idx()) > 0
        assert len(epanet_api.get_all_links_idx()) > 0

        epanet_api.get_all_junctions_id()
        epanet_api.get_all_junctions_idx()

        assert len(epanet_api.get_all_pipes_id()) > 0
        assert len(epanet_api.get_all_pipes_idx()) > 0

        assert len(epanet_api.get_all_tanks_id()) > 0
        assert len(epanet_api.get_all_tanks_idx()) > 0

        epanet_api.get_all_reservoirs_id()
        epanet_api.get_all_reservoirs_idx()
        epanet_api.get_all_pumps_id()
        epanet_api.get_all_pumps_idx()

    with EPyT("net2-cl2.inp") as epanet_api:
        __test_code(epanet_api)

    with EPyT("net2-cl2.inp", use_project=True) as epanet_api:
        __test_code(epanet_api)


def test_parameters():
    def __test_code(epanet_api: EPyT):
        assert epanet_api.get_simulation_duration() > 0
        assert epanet_api.get_hydraulic_time_step() > 0
        assert epanet_api.get_reporting_start_time() >= 0
        assert epanet_api.get_reporting_time_step() > 0
        assert epanet_api.get_quality_time_step() > 0

    with EPyT("net2-cl2.inp") as epanet_api:
        __test_code(epanet_api)

    with EPyT("net2-cl2.inp", use_project=True) as epanet_api:
        __test_code(epanet_api)


def test_hyd_simulation():
    def __test_code(epanet_api: EPyT):
        epanet_api.openH()
        epanet_api.initH(EpanetConstants.EN_NOSAVE)

        tstep = 1
        while tstep > 0:
            epanet_api.runH()

            assert len(epanet_api.getnodevalues(EpanetConstants.EN_PRESSURE)) > 0
            assert len(epanet_api.getlinkvalues(EpanetConstants.EN_FLOW)) > 0

            tstep = epanet_api.nextH()

        epanet_api.closeH()

    with EPyT("net2-cl2.inp") as epanet_api:
        __test_code(epanet_api)

    with EPyT("net2-cl2.inp", use_project=True) as epanet_api:
        __test_code(epanet_api)


def test_quality_simulation():
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

    with EPyT("net2-cl2.inp") as epanet_api:
        __test_code(epanet_api)

    with EPyT("net2-cl2.inp", use_project=True) as epanet_api:
        __test_code(epanet_api)


def test_msx():
    with EPyT("net2-cl2.inp", use_project=False) as epanet_api:
        epanet_api.load_msx_file("net2-cl2.msx")

        assert epanet_api.get_msx_time_step() > 0
        epanet_api.set_msx_time_step(150)
        assert epanet_api.get_msx_time_step() == 150

        epanet_api.get_all_msx_species_id()
        epanet_api.get_all_msx_species_info()
