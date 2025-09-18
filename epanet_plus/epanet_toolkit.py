"""
This module contains a Python toolkit with higher-level functions for working with
EPANET and EPANET-MSX.
"""
import os
import re
import tempfile

from .epanet_wrapper import EpanetAPI


class EpanetConstants:
    """
    EPANET and EPANET-MSX constants.
    """
    EN_MAXID   = 31
    EN_MAXMSG  = 255
    EN_ELEVATION     = 0    # Elevation
    EN_BASEDEMAND    = 1    # Primary demand baseline value
    EN_PATTERN       = 2    # Primary demand time pattern index
    EN_EMITTER       = 3    # Emitter flow coefficient
    EN_INITQUAL      = 4    # Initial quality
    EN_SOURCEQUAL    = 5    # Quality source strength
    EN_SOURCEPAT     = 6    # Quality source pattern index
    EN_SOURCETYPE    = 7    # Quality source type (see @ref EN_SourceType)
    EN_TANKLEVEL     = 8    # Current computed tank water level (read only)
    EN_DEMAND        = 9    # Current computed demand (read only)
    EN_HEAD          = 10   # Current computed hydraulic head (read only)
    EN_PRESSURE      = 11   # Current computed pressure (read only)
    EN_QUALITY       = 12   # Current computed quality (read only)
    EN_SOURCEMASS    = 13   # Current computed quality source mass inflow (read only)
    EN_INITVOLUME    = 14   # Tank initial volume (read only)
    EN_MIXMODEL      = 15   # Tank mixing model (see @ref EN_MixingModel)
    EN_MIXZONEVOL    = 16   # Tank mixing zone volume (read only)
    EN_TANKDIAM      = 17   # Tank diameter
    EN_MINVOLUME     = 18   # Tank minimum volume
    EN_VOLCURVE      = 19   # Tank volume curve index
    EN_MINLEVEL      = 20   # Tank minimum level
    EN_MAXLEVEL      = 21   # Tank maximum level
    EN_MIXFRACTION   = 22   # Tank mixing fraction
    EN_TANK_KBULK    = 23   # Tank bulk decay coefficient
    EN_TANKVOLUME    = 24   # Current computed tank volume (read only)
    EN_MAXVOLUME     = 25   # Tank maximum volume (read only)
    EN_CANOVERFLOW   = 26   # Tank can overflow (= 1) or not (= 0)
    EN_DEMANDDEFICIT = 27

    EN_DIAMETER     = 0     # Pipe/valve diameter
    EN_LENGTH       = 1     # Pipe length
    EN_ROUGHNESS    = 2     # Pipe roughness coefficient
    EN_MINORLOSS    = 3     # Pipe/valve minor loss coefficient
    EN_INITSTATUS   = 4     # Initial status (see @ref EN_LinkStatusType)
    EN_INITSETTING  = 5     # Initial pump speed or valve setting
    EN_KBULK        = 6     # Bulk chemical reaction coefficient
    EN_KWALL        = 7     # Pipe wall chemical reaction coefficient
    EN_FLOW         = 8     # Current computed flow rate (read only)
    EN_VELOCITY     = 9     # Current computed flow velocity (read only)
    EN_HEADLOSS     = 10    # Current computed head loss (read only)
    EN_STATUS       = 11    # Current link status (see @ref EN_LinkStatusType)
    EN_SETTING      = 12    # Current link setting
    EN_ENERGY       = 13    # Current computed pump energy usage (read only)
    EN_LINKQUAL     = 14    # Current computed link quality (read only)
    EN_LINKPATTERN  = 15    # Pump speed time pattern index
    EN_PUMP_STATE   = 16    # Current computed pump state (read only) (see @ref EN_PumpStateType)
    EN_PUMP_EFFIC   = 17    # Current computed pump efficiency (read only)
    EN_PUMP_POWER   = 18    # Pump constant power rating
    EN_PUMP_HCURVE  = 19    # Pump head v. flow curve index
    EN_PUMP_ECURVE  = 20    # Pump efficiency v. flow curve index
    EN_PUMP_ECOST   = 21    # Pump average energy price
    EN_PUMP_EPAT    = 22

    EN_DURATION      = 0   # Total simulation duration
    EN_HYDSTEP       = 1   # Hydraulic time step
    EN_QUALSTEP      = 2   # Water quality time step
    EN_PATTERNSTEP   = 3   # Time pattern period
    EN_PATTERNSTART  = 4   # Time when time patterns begin
    EN_REPORTSTEP    = 5   # Reporting time step
    EN_REPORTSTART   = 6   # Time when reporting starts
    EN_RULESTEP      = 7   # Rule-based control evaluation time step
    EN_STATISTIC     = 8    # Reporting statistic code (see @ref EN_StatisticType)
    EN_PERIODS       = 9   # Number of reporting time periods (read only)
    EN_STARTTIME     = 10   # Simulation starting time of day
    EN_HTIME         = 11   # Elapsed time of current hydraulic solution (read only)
    EN_QTIME         = 12   # Elapsed time of current quality solution (read only)
    EN_HALTFLAG      = 13   # Flag indicating if the simulation was halted (read only)
    EN_NEXTEVENT     = 14   # Shortest time until a tank becomes empty or full (read only)
    EN_NEXTEVENTTANK = 15

    EN_ITERATIONS      = 0  # Number of hydraulic iterations taken
    EN_RELATIVEERROR   = 1  # Sum of link flow changes / sum of link flows
    EN_MAXHEADERROR    = 2  # Largest head loss error for links
    EN_MAXFLOWCHANGE   = 3  # Largest flow change in links
    EN_MASSBALANCE     = 4  # Cumulative water quality mass balance ratio
    EN_DEFICIENTNODES  = 5  # Number of pressure deficient nodes
    EN_DEMANDREDUCTION = 6

    EN_NODE    = 0     # Nodes
    EN_LINK    = 1     # Links
    EN_TIMEPAT = 2     # Time patterns
    EN_CURVE   = 3     # Data curves
    EN_CONTROL = 4     # Simple controls
    EN_RULE    = 5

    EN_NODECOUNT    = 0  # Number of nodes (junctions + tanks + reservoirs)
    EN_TANKCOUNT    = 1  # Number of tanks and reservoirs
    EN_LINKCOUNT    = 2  # Number of links (pipes + pumps + valves)
    EN_PATCOUNT     = 3  # Number of time patterns
    EN_CURVECOUNT   = 4  # Number of data curves
    EN_CONTROLCOUNT = 5  # Number of simple controls
    EN_RULECOUNT    = 6

    EN_JUNCTION    = 0   # Junction node
    EN_RESERVOIR   = 1   # Reservoir node
    EN_TANK        = 2

    EN_CVPIPE       = 0  # Pipe with check valve
    EN_PIPE         = 1  # Pipe
    EN_PUMP         = 2  # Pump
    EN_PRV          = 3  # Pressure reducing valve
    EN_PSV          = 4  # Pressure sustaining valve
    EN_PBV          = 5  # Pressure breaker valve
    EN_FCV          = 6  # Flow control valve
    EN_TCV          = 7  # Throttle control valve
    EN_GPV          = 8

    EN_CLOSED       = 0
    EN_OPEN         = 1

    EN_PUMP_XHEAD   = 0  # Pump closed - cannot supply head
    EN_PUMP_CLOSED  = 2  # Pump closed
    EN_PUMP_OPEN    = 3  # Pump open
    EN_PUMP_XFLOW   = 5

    EN_NONE        = 0   # No quality analysis
    EN_CHEM        = 1   # Chemical fate and transport
    EN_AGE         = 2   # Water age analysis
    EN_TRACE       = 3

    EN_CONCEN      = 0   # Sets the concentration of external inflow entering a node
    EN_MASS        = 1   # Injects a given mass/minute into a node
    EN_SETPOINT    = 2   # Sets the concentration leaving a node to a given value
    EN_FLOWPACED   = 3

    EN_HW          = 0   # Hazen-Williams
    EN_DW          = 1   # Darcy-Weisbach
    EN_CM          = 2

    EN_CFS         = 0   # Cubic feet per second
    EN_GPM         = 1   # Gallons per minute
    EN_MGD         = 2   # Million gallons per day
    EN_IMGD        = 3   # Imperial million gallons per day
    EN_AFD         = 4   # Acre-feet per day
    EN_LPS         = 5   # Liters per second
    EN_LPM         = 6   # Liters per minute
    EN_MLD         = 7   # Million liters per day
    EN_CMH         = 8   # Cubic meters per hour
    EN_CMD         = 9

    EN_DDA         = 0   # Demand driven analysis
    EN_PDA         = 1

    EN_TRIALS         = 0   # Maximum trials allowed for hydraulic convergence
    EN_ACCURACY       = 1   # Total normalized flow change for hydraulic convergence
    EN_TOLERANCE      = 2   # Water quality tolerance
    EN_EMITEXPON      = 3   # Exponent in emitter discharge formula
    EN_DEMANDMULT     = 4   # Global demand multiplier
    EN_HEADERROR      = 5   # Maximum head loss error for hydraulic convergence
    EN_FLOWCHANGE     = 6   # Maximum flow change for hydraulic convergence
    EN_HEADLOSSFORM   = 7   # Head loss formula (see @ref EN_HeadLossType)
    EN_GLOBALEFFIC    = 8   # Global pump efficiency (percent)
    EN_GLOBALPRICE    = 9   # Global energy price per KWH
    EN_GLOBALPATTERN  = 10  # Index of a global energy price pattern
    EN_DEMANDCHARGE   = 11  # Energy charge per max. KW usage
    EN_SP_GRAVITY     = 12  # Specific gravity
    EN_SP_VISCOS      = 13  # Specific viscosity (relative to water at 20 deg C)
    EN_UNBALANCED     = 14  # Extra trials allowed if hydraulics don't converge
    EN_CHECKFREQ      = 15  # Frequency of hydraulic status checks
    EN_MAXCHECK       = 16  # Maximum trials for status checking
    EN_DAMPLIMIT      = 17  # Accuracy level where solution damping begins
    EN_SP_DIFFUS      = 18  # Specific diffusivity (relative to chlorine at 20 deg C)
    EN_BULKORDER      = 19  # Bulk water reaction order for pipes
    EN_WALLORDER      = 20  # Wall reaction order for pipes (either 0 or 1)
    EN_TANKORDER      = 21  # Bulk water reaction order for tanks
    EN_CONCENLIMIT    = 22

    EN_LOWLEVEL    = 0   # Act when pressure or tank level drops below a setpoint
    EN_HILEVEL     = 1   # Act when pressure or tank level rises above a setpoint
    EN_TIMER       = 2   # Act at a prescribed elapsed amount of time
    EN_TIMEOFDAY   = 3

    EN_SERIES      = 0   # Report all time series points
    EN_AVERAGE     = 1   # Report average value over simulation period
    EN_MINIMUM     = 2   # Report minimum value over simulation period
    EN_MAXIMUM     = 3   # Report maximum value over simulation period
    EN_RANGE       = 4

    EN_MIX1        = 0   # Complete mix model
    EN_MIX2        = 1   # 2-compartment model
    EN_FIFO        = 2   # First in, first out model
    EN_LIFO        = 3

    EN_NOSAVE        = 0    # Don't save hydraulics; don't re-initialize flows
    EN_SAVE          = 1    # Save hydraulics to file, don't re-initialize flows
    EN_INITFLOW      = 10   # Don't save hydraulics; re-initialize flows
    EN_SAVE_AND_INIT = 11

    EN_CONST_HP    = 0   # Constant horsepower
    EN_POWER_FUNC  = 1   # Power function
    EN_CUSTOM      = 2   # User-defined custom curve
    EN_NOCURVE     = 3

    EN_VOLUME_CURVE  = 0   # Tank volume v. depth curve
    EN_PUMP_CURVE    = 1   # Pump head v. flow curve
    EN_EFFIC_CURVE   = 2   # Pump efficiency v. flow curve
    EN_HLOSS_CURVE   = 3   # Valve head loss v. flow curve
    EN_GENERIC_CURVE = 4

    EN_UNCONDITIONAL = 0    # Delete all controls and connecing links
    EN_CONDITIONAL   = 1

    N_NO_REPORT      = 0   # No status reporting
    EN_NORMAL_REPORT = 1    # Normal level of status reporting
    EN_FULL_REPORT   = 2

    EN_R_NODE      = 6   # Clause refers to a node
    EN_R_LINK      = 7   # Clause refers to a link
    EN_R_SYSTEM    = 8

    EN_R_DEMAND    = 0   # Nodal demand
    EN_R_HEAD      = 1   # Nodal hydraulic head
    EN_R_GRADE     = 2   # Nodal hydraulic grade
    EN_R_LEVEL     = 3   # Tank water level
    EN_R_PRESSURE  = 4   # Nodal pressure
    EN_R_FLOW      = 5   # Link flow rate
    EN_R_STATUS    = 6   # Link status
    EN_R_SETTING   = 7   # Link setting
    EN_R_POWER     = 8   # Pump power output
    EN_R_TIME      = 9   # Elapsed simulation time
    EN_R_CLOCKTIME = 10  # Time of day
    EN_R_FILLTIME  = 11  # Time to fill a tank
    EN_R_DRAINTIME = 12

    EN_R_EQ        = 0   # Equal to
    EN_R_NE        = 1   # Not equal
    EN_R_LE        = 2   # Less than or equal to
    EN_R_GE        = 3   # Greater than or equal to
    EN_R_LT        = 4   # Less than
    EN_R_GT        = 5   # Greater than
    EN_R_IS        = 6   # Is equal to
    EN_R_NOT       = 7   # Is not equal to
    EN_R_BELOW     = 8   # Is below
    EN_R_ABOVE     = 9

    EN_R_IS_OPEN   = 1   # Link is open
    EN_R_IS_CLOSED = 2   # Link is closed
    EN_R_IS_ACTIVE = 3

    EN_MISSING    = -1.E10

    MSX_NODE       = 0
    MSX_LINK       = 1
    MSX_TANK       = 2
    MSX_SPECIES    = 3
    MSX_TERM       = 4
    MSX_PARAMETER  = 5
    MSX_CONSTANT   = 6
    MSX_PATTERN    = 7
    MSX_BULK       = 0
    MSX_WALL       = 1
    MSX_NOSOURCE   = -1
    MSX_CONCEN     = 0
    MSX_MASS       = 1
    MSX_SETPOINT   = 2
    MSX_FLOWPACED  = 3


class EPyT(EpanetAPI):
    """
    Python toolkit for EPANET and EPANET-MSX.

    Parameters
    ----------
    inp_file_in : `str`
        Path to .inp file.
    use_project : `bool`, optional
        If True, projects will be used when calling EPANET functions (default in EPANET >= 2.2).
        Note that this is incompatible with EPANET-MSX. Please set to False when using EPANET-MSX.

        The default is False.
    """
    def __init__(self, inp_file_in: str, use_project: bool = False, **kwds):
        super().__init__(use_project=use_project, **kwds)

        if use_project is True:
            self.createproject()
        self.open(inp_file_in, inp_file_in + ".rpt", "")

        self._inp_file = inp_file_in
        self._msx_file = None

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.close()

    def load_msx_file(self, msx_file_in: str) -> None:
        """
        Loads an EPANET-MSX file.

        Parameters
        ----------
        msx_file_in : `str`
            Path to .msx file.
        """
        if self._use_project is True:
            raise ValueError("EPANET-MSX can not be used with EPANET projects")

        self.MSXopen(msx_file_in)
        self._msx_file = msx_file_in

    def close(self) -> None:
        """
        Closes EPANET and EPANET-MSX, and deletes all temprorary files.
        """
        if self._msx_file is not None:
            self.MSXclose()

        super().close()

        if self._use_project is True:
            self.deleteproject()

    @property
    def msx_file(self) -> str:
        """
        Returns the file path to the .msx file.

        Returns
        -------
        `str`
            File path to .msx file.
        """
        return self._msx_file

    def get_all_nodes_id(self) -> list[str]:
        """
        Returns all node IDs.

        Returns
        -------
        `list[str]`
            List of node IDs.
        """
        return [self.getnodeid(i + 1) for i in range(self.getcount(EpanetConstants.EN_NODECOUNT))]

    def get_num_nodes(self) -> int:
        """
        Returns the number of nodes in the network.

        Returns
        -------
        `int`
            Number of nodes.
        """
        return self.getcount(EpanetConstants.EN_NODECOUNT)

    def get_all_nodes_idx(self) -> list[int]:
        """
        Returns all node indices.

        Returns
        -------
        `list[int]`
            List of node indices:
        """
        return list(range(1, self.getcount(EpanetConstants.EN_NODECOUNT) + 1))

    def get_all_junctions_id(self) -> list[str]:
        """
        Returns all junction IDs -- i.e., IDs of nodes that are neither a reservoir
        nor a tank.

        Returns
        -------
        `list[str]`
            List of all junction IDs.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_NODECOUNT)):
            if self.getnodetype(i + 1) == EpanetConstants.EN_JUNCTION:
                r.append(self.getnodeid(i + 1))

        return []

    def get_all_junctions_idx(self) -> list[int]:
        """
        Returns all junction indices -- i.e., indices of nodes that are neither a reservoir
        nor a tank.

        Returns
        -------
        `list[int]`
            List of all junction indices.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_NODECOUNT)):
            if self.getnodetype(i + 1) == EpanetConstants.EN_JUNCTION:
                r.append(i + 1)

        return []

    def get_num_junctions(self) -> int:
        """
        Returns the number of junctions -- i.e., number of nodes that are neither a tank nor
        a reservoir.

        Returns
        -------
        `int`
            Number of junctions.
        """
        return len(self.get_all_junctions_idx())

    def get_all_links_id(self) -> list[str]:
        """
        Returns all link IDs.

        Returns
        -------
        `list[str]`
            List of all link IDs.
        """
        return [self.getlinkid(i + 1) for i in range(self.getcount(EpanetConstants.EN_LINKCOUNT))]

    def get_all_links_idx(self) -> list[int]:
        """
        Returns all link indcies.

        Returns
        -------
        `list[int]`
            List of all link indices.
        """
        return list(range(1, self.getcount(EpanetConstants.EN_LINKCOUNT) + 1))

    def get_num_links(self) -> int:
        """
        Returns the number of links in the network.

        Returns
        -------
        `int`
            Number of links.
        """
        return self.getcount(EpanetConstants.EN_LINKCOUNT)

    def get_all_pipes_idx(self) -> list[int]:
        """
        Return the indices of all pipes in the network.

        Returns
        -------
        `list[int]`
            List of pipe indices.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_LINKCOUNT)):
            link_type = self.getlinktype(i + 1)
            if link_type == EpanetConstants.EN_PIPE:
                r.append(i + 1)

        return r

    def get_all_pipes_id(self) -> list[str]:
        """
        Returns the IDs of all pipes in the network.

        Returns
        -------
        `list[str]`
            List of pipe IDs.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_LINKCOUNT)):
            link_type = self.getlinktype(i + 1)
            if link_type == EpanetConstants.EN_PIPE:
                r.append(self.getlinkid(i + 1))

        return r

    def get_num_pipes(self) -> int:
        """
        Returns the number of pipes in the network.

        Returns
        -------
        `int`
            Returns the maximum number of pipes.
        """
        return len(self.get_all_pipes_idx())

    def get_all_valves_id(self) -> list[str]:
        """
        Returns a list of all valve IDs.

        Returns
        -------
        `list[str]`
            List of all valve IDs.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_LINKCOUNT)):
            link_type = self.getlinktype(i + 1)
            if link_type != EpanetConstants.EN_PIPE and link_type != EpanetConstants.EN_PUMP:
                r.append(self.getlinkid(i + 1))

        return r

    def get_num_valves(self) -> int:
        """
        Returns the number of valves.

        Returns
        -------
        `int`
            Number of valves.
        """
        return len(self.get_all_valves_idx())

    def get_all_valves_idx(self) -> list[int]:
        """
        Returns all valve indices.

        Returns
        -------
        `list[int]`
            List of all valve indices.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_LINKCOUNT)):
            link_type = self.getlinktype(i + 1)
            if link_type != EpanetConstants.EN_PIPE and link_type != EpanetConstants.EN_PUMP:
                r.append(i + 1)

        return r

    def get_all_pumps_id(self) -> list[str]:
        """
        Returns all pump IDs.

        Returns
        -------
        `list[str]`
            List of all pump IDs.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_LINKCOUNT)):
            if self.getlinktype(i + 1) == EpanetConstants.EN_PUMP:
                r.append(self.getlinkid(i + 1))

        return r

    def get_num_pumps(self) -> int:
        """
        Returns the number of pumps in the network.

        Returns
        -------
        `int`
            Number of pumps.
        """
        return len(self.get_all_pumps_idx())

    def get_all_pumps_idx(self) -> list[int]:
        """
        Returns all pump_indices.

        Returns
        -------
        `list[int]`
            List of all pump indices.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_LINKCOUNT)):
            if self.getlinktype(i + 1) == EpanetConstants.EN_PUMP:
                r.append(i + 1)

        return r

    def get_all_tanks_id(self) -> list[str]:
        """
        Returns all tank IDs.

        Returns
        -------
        `list[str]`
            List of all tank IDs.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_NODECOUNT)):
            if self.getnodetype(i + 1) == EpanetConstants.EN_TANK:
                r.append(self.getnodeid(i + 1))

        return r

    def get_num_tanks(self) -> int:
        """
        Returns the number of tanks in the network.

        Returns
        -------
        `int`
            Number of tanks.
        """
        return self.getcount(EpanetConstants.EN_TANKCOUNT)

    def get_all_tanks_idx(self) -> list[int]:
        """
        Returns all tank indices.

        Returns
        -------
        `list[int]`
            List of all tank indices.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_NODECOUNT)):
            if self.getnodetype(i + 1) == EpanetConstants.EN_TANK:
                r.append(i + 1)

        return r

    def get_all_reservoirs_id(self) -> list[str]:
        """
        Returns all reservoir IDs.

        Returns
        -------
        `list[str]`
            List of all reservoir IDs.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_NODECOUNT)):
            if self.getnodetype(i + 1) == EpanetConstants.EN_RESERVOIR:
                r.append(self.getnodeid(i + 1))

        return r

    def get_num_reservoirs(self) -> int:
        """
        Returns the number of reservoirs in the network.

        Returns
        -------
        `int`
            Number of reservoirs.
        """
        return len(self.get_all_reservoirs_idx())

    def get_all_reservoirs_idx(self) -> list[int]:
        """
        Returns all reservoir indices.

        Returns
        -------
        `list[int]`
            List of all reservoir indices.
        """
        r = []

        for i in range(self.getcount(EpanetConstants.EN_NODECOUNT)):
            if self.getnodetype(i + 1) == EpanetConstants.EN_RESERVOIR:
                r.append(i + 1)

        return r

    def get_node_idx(self, node_id: str) -> int:
        """
        Returns the index of a given node.

        Parameters
        ----------
        node_id : `str`
            ID of the node.

        Returns
        -------
        `int`
            Index of the node.
        """
        return self.getnodeindex(node_id)

    def get_link_idx(self, link_id: str) -> int:
        """
        Returns the index of a given link.

        Parameters
        ----------
        link_id : `str`
            ID of the link.

        Returns
        -------
        `int`
            Index of the link.
        """
        return self.getlinkindex(link_id)

    def get_node_id(self, node_idx) -> str:
        """
        Returns the ID of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `str`
            ID of the node.
        """
        return self.getnodeid(node_idx)

    def get_link_id(self, link_idx) -> str:
        """
        Returns the ID of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `str`
            ID of the link.
        """
        return self.getlinkid(link_idx)

    def get_node_type(self, node_idx: int) -> int:
        """
        Returns the type of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `int`
            Type of the node. Will be one of the following:

                - EN_JUNCTION
                - EN_TANK
                - EN_RESERVOIR
        """
        return self.getnodetype(node_idx)

    def get_link_type(self, link_idx: int) -> int:
        """
        Returns the type of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `int`
            Type of the link. Will be one of the following:

                - EN_CVPIPE
                - EN_PIPE
                - EN_PUMP
                - EN_PRV
                - EN_PSV
                - EN_PBV
                - EN_FCV
                - EN_TCV
                - EN_GPV
        """
        return self.getlinktype(link_idx)

    def get_quality_info(self) -> dict:
        """
        Returns the water quality analysis parameters.

        Returns
        -------
        `dict`
            Water quality analysis information as a dictionary with the following entries:

                - 'qualType': type of quality analysis (EN_NONE, EN_CHEM, EN_AGE, or EN_TRACE);
                - 'chemName': name of chemical constituent;
                - 'chemUnits': concentration units of constituent;
                - 'traceNode': ID of node being traced (if applicable,
                               only if 'qualType' = EN_TRACE);
        """
        r = dict(zip(["qualType", "chemName", "chemUnits", "traceNode"], self.getqualinfo()))
        if r["qualType"] == EpanetConstants.EN_AGE:
            r["chemUnits"] = "hrs"

        if r["qualType"] == EpanetConstants.EN_TRACE:
            r["traceNode"] = self.get_node_id(r["traceNode"])
        else:
            r["traceNode"] = ""

        return r

    def get_quality_type(self) -> dict:
        """
        Returns the type of quality analysis.

        Returns
        -------
        `dict`
            Dictioanry containing the type of quality analysis and the
            ID of the node being traced (if applicable):

                - 'qualType': type of quality analysis (EN_NONE, EN_CHEM, EN_AGE, or EN_TRACE);
                - 'traceNode': ID of node being traced (if applicable, only if 'qualType' = EN_TRACE);
        """
        r = dict(zip(["qualType", "traceNode"], self.getqualtype()))
        if r["qualType"] == EpanetConstants.EN_TRACE:
            r["traceNode"] = self.get_node_id(r["traceNode"])
        else:
            r["traceNode"] = ""

        return r

    def set_quality_type(self, qual_code: int, chem_name: str, chem_units: str,
                         tracenode_id: str) -> None:
        """
        Specifies the water quality analysis parameters.

        Parameters
        ----------
        qual_code : `int`
            Type of quality analysis. Must be one of the following:

                - EN_NONE
                - EN_CHEM
                - EN_AGE
                - EN_TRACE
        chem_name : `str`
            Name of chemical constituent
        chem_units : `str`
            Concentration units of constituent
        tracenode_id : `str`
            ID of node being traced (if applicable, only if 'qualType' = EN_TRACE).
        """
        self.setqualtype(qual_code, chem_name, chem_units, tracenode_id)

    def get_num_controls(self) -> int:
        """
        Returns the number of controls.

        Returns
        -------
        `int`
            Number of controls.
        """
        return self.getcount(EpanetConstants.EN_CONTROLCOUNT)

    def add_control(self, control_type: int, link_index: int, setting: float, node_index: int,
                    level: float) -> None:
        """
        Adds a control.

        Parameters
        ----------
        control_type : `int`
            Type of control. Must be one of the following:

                - EN_LOWLEVEL
                - EN_HILEVEL
                - EN_TIMER
                - EN_TIMEOFDAY
        link_index : `int`
            Index of the link (i.e., valve or pump) that is being controlled.
        setting : `float`
            Link control setting (e.g., pump speed).
        node_index : `int`
            Index of the node that is controlling the link.
        level : `float`
            Control activation level -- pressure for junction nodes, water level for tank nodes
            or time value for time-based control.
        """
        self.addcontrol(control_type, link_index, setting, node_index, level)

    def remove_all_controls(self) -> None:
        """
        Removes all controls.
        """
        while self.getcount(EpanetConstants.EN_CONTROLCOUNT) > 0:
            self.deletecontrol(1)

    def get_num_rules(self) -> int:
        """
        Returns the numer of rules.

        Returns
        -------
        `int`
            Number of rules.
        """
        return self.getcount(EpanetConstants.EN_RULECOUNT)

    def get_all_rules_id(self) -> list[str]:
        """
        Returns the IDs of all rules.

        Returns
        -------
        `list[str]`
            List of rule IDs -- ordered by their index.
        """
        return [self.getruleid(i + 1) for i in range(self.getcount(EpanetConstants.EN_RULECOUNT))]

    def remove_all_rules(self) -> None:
        """
        Removes all rules.
        """
        while self.getcount(EpanetConstants.EN_RULECOUNT) > 0:
            self.deleterule(1)

    def get_hydraulic_time_step(self) -> int:
        """
        Returns the hydraulic time step in seconds.

        Returns
        -------
        `int`
            Hydraulic time step.
        """
        return self.gettimeparam(EpanetConstants.EN_HYDSTEP)

    def set_hydraulic_time_step(self, time_step: int) -> None:
        """
        Specifies the hydraulic time step.

        Parameters
        ----------
        time_step : `int`
            Hydraulic time step in seconds.
        """
        self.settimeparam(EpanetConstants.EN_HYDSTEP, time_step)

    def get_quality_time_step(self) -> int:
        """
        Returns the quality time step in seconds.

        Returns
        -------
        `int`
            Quality time step.
        """
        return self.gettimeparam(EpanetConstants.EN_QUALSTEP)

    def set_quality_time_step(self, time_step: int) -> None:
        """
        Specifies the water quality time step.

        Parameters
        ----------
        time_step : `int`
            Water quality time step in seconds.
        """
        self.settimeparam(EpanetConstants.EN_QUALSTEP, time_step)

    def get_reporting_time_step(self) -> int:
        """
        Returns the reporting time step in seconds.

        Returns
        -------
        `int`
            Reporting time step.
        """
        return self.gettimeparam(EpanetConstants.EN_REPORTSTEP)

    def set_reporting_time_step(self, time_step: int) -> None:
        """
        Specifies the reporting time step.

        Parameters
        ----------
        time_step : `int`
            Reporting time step in seconds.
        """
        self.settimeparam(EpanetConstants.EN_REPORTSTEP, time_step)

    def get_reporting_start_time(self) -> int:
        """
        Returns the reporting start time in seconds since the simulation start.

        Returns
        -------
        `int`
            Reporting start time.
        """
        return self.gettimeparam(EpanetConstants.EN_REPORTSTART)

    def set_reporting_start_time(self, start_time: int) -> None:
        """
        Specifies the start time of reporting.

        Parameters
        ----------
        time_step : `int`
            Reporting start time step in seconds since simulation start.
        """
        self.settimeparam(EpanetConstants.EN_REPORTSTART, start_time)

    def get_simulation_duration(self) -> int:
        """
        Returns the simulation duration in seconds.

        Returns
        -------
        `int`
            Simulation duration.
        """
        return self.gettimeparam(EpanetConstants.EN_DURATION)

    def set_simulation_duration(self, duration: int) -> None:
        """
        Sets the simulation duration.

        Parameters
        ----------
        duration : `int`
            Simulation duration in seconds.
        """
        self.settimeparam(EpanetConstants.EN_DURATION, duration)

    def get_demand_model(self) -> dict:
        """
        Returns the specifications of the demand model.

        Returns
        -------
        `dict`
            Dictionary contains the specifications of the demand model:

                - 'type': type of demand model (either EN_DDA or EN_PDA);
                - 'pmin': minimum pressure for any demand;
                - 'preq': required pressure for full demand;
                - 'pexp': exponent in pressure dependent demand formula;
        """
        return dict(zip(["type", "pmin", "preq", "pexp"], self.getdemandmodel()))

    def set_demand_model(self, model_type: int, pmin: float, preq: float, pexp: float) -> None:
        """
        Specifies the demand model.

        Parameters
        ----------
        model_type : `int`
            Type of demand model. Must be one of the following:

                - EN_DDA
                - EN_PDA
        pmin : `float`
            Minimum pressure for any demand.
        preq : `float`
            Required pressure for full demand.
        pexp : `float`
            Exponent in pressure dependent demand formula.
        """
        self.setdemandmodel(model_type, pmin, preq, pexp)

    def get_link_diameter(self, link_idx: int) -> float:
        """
        Returns the diameter of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Diameter of the link.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_DIAMETER)

    def get_link_length(self, link_idx: int) -> float:
        """
        Returns the length of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Length of the link.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_LENGTH)

    def get_link_roughness(self, link_idx: int) -> dict:
        """
        Returns the roughness coefficient of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Roughness coefficient of the link.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_ROUGHNESS)

    def get_link_minorloss(self, link_idx: int) -> float:
        """
        Returns the minor loss coefficient of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Minor loss coefficient of the link.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_MINORLOSS)

    def get_link_init_status(self, link_idx: int) -> int:
        """
        Returns the initial status (open or closed) of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `int`
            Initial status of the link. Will be one of the following:

                - EN_CLOSED
                - EN_OPEN
        """
        return int(self.getlinkvalue(link_idx, EpanetConstants.EN_INITSTATUS))

    def get_link_init_setting(self, link_idx: int) -> float:
        """
        Returns the initial setting of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Initial setting.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_INITSETTING)

    def get_link_bulk_deacy(self, link_idx: int) -> float:
        """
        Returns the bulk decay rate at a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Bulk decay rate.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_KBULK)

    def get_link_wall_decay(self, link_idx: int) -> float:
        """
        Returns the wall decay rate at a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Wall decay rate.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_KWALL)

    def get_node_comment(self, node_idx: int) -> str:
        """
        Returns the comment of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `str`
            Comment.
        """
        return self.getcomment(EpanetConstants.EN_NODE, node_idx)

    def get_node_elevation(self, node_idx: int) -> float:
        """
        Returns the evelvation of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Elevation.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_ELEVATION)

    def get_node_emitter_coeff(self, node_idx: int) -> float:
        """
        Returns the roughness coefficient of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Emitter coefficient of the node.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_EMITTER)

    def get_node_init_qual(self, node_idx: int) -> float:
        """
        Returns the initial quality value/state of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Initial quality state/value.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_INITQUAL)

    def get_node_source_qual(self, node_idx: int) -> float:
        """
        Returns the current quality state/value at a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Current quality state/value.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_SOURCEQUAL)

    def get_node_source_type(self, node_idx: int) -> int:
        """
        Returns the type of the water quality source at a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `int`
            Type of the water quality source. Will be one of the following:

                - EN_CONCEN
                - EN_MASS
                - EN_SETPOINT
                - EN_FLOWPACED
        """
        return int(self.getnodevalue(node_idx, EpanetConstants.EN_SOURCETYPE))

    def get_node_source_pattern_idx(self, node_idx: int) -> int:
        """
        Returns the index of the quality source pattern at a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `int`
            Index of the pattern.
        """
        return int(self.getnodevalue(node_idx, EpanetConstants.EN_SOURCEPAT))

    def get_node_pattern_idx(self, node_idx: int) -> float:
        """
        Returns the index of the primary demand pattern of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `int`
            Index of the primary demand pattern.
        """
        return int(self.getnodevalue(node_idx, EpanetConstants.EN_PATTERN))

    def get_node_base_demand(self, node_idx: int) -> float:
        """
        Returns the primary base demand of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `int`
            Primary base demand.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_BASEDEMAND)

    def get_node_base_demands(self, node_idx: int) -> list[float]:
        """
        Returns all base demands of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `list[int]`
            List of base demands.
        """
        r = []

        for i in range(self.getnumdemands(node_idx)):
            r.append(self.getbasedemand(node_idx, i + 1))

        return r

    def get_node_demand_patterns_idx(self, node_idx: int) -> list[int]:
        """
        Returns the index of all demand patterns of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `list[int]`
            List of indices of the demand patterns.
        """
        r = []

        for i in range(self.getnumdemands(node_idx)):
            r.append(self.getdemandpattern(node_idx, i + 1))

        return r

    def get_tank_init_vol(self, tank_idx) -> float:
        """
        Return the inital water volume in a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Initial water volume.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_INITVOLUME)

    def get_tank_level(self, tank_idx: int) -> float:
        """
        Returns the current water level in a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Current water level.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_TANKLEVEL)

    def get_tank_volume(self, tank_idx: int) -> float:
        """
        Returns the current water volume inside a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Current water volume.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_TANKVOLUME)

    def get_tank_mix_model(self, tank_idx: int) -> int:
        """
        Returns the mixing model of a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `int`
            Type of mixing model. Will be one of the following:

                - EN_MIX1
                - EN_MIX2
                - EN_FIFO
                - EN_LIFO
        """
        return int(self.getnodevalue(tank_idx, EpanetConstants.EN_MIXMODEL))

    def get_tank_mix_zone_vol(self, tank_idx: int) -> float:
        """
        Returns the mixing zone volume of a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Tank mixing zone valume.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_MIXZONEVOL)

    def get_tank_diameter(self, tank_idx: int) -> float:
        """
        Return the diameter of given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Diameter of the tank.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_TANKDIAM)

    def get_tank_min_vol(self, tank_idx: int) -> float:
        """
        Return the minimum volume of given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Minimum volume.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_MINVOLUME)

    def get_tank_max_vol(self, tank_idx: int) -> float:
        """
        Return the maxmium volume of given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Maximum volume.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_MAXVOLUME)

    def get_tank_vol_curve_idx(self, tank_idx: int) -> int:
        """
        Returns the index of the volume curve of a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `int`
            Index of the volume curve.
        """
        return int(self.getnodevalue(tank_idx, EpanetConstants.EN_VOLCURVE))

    def get_tank_min_level(self, tank_idx: int) -> float:
        """
        Returns the minimum water level of a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Minimum water level.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_MINLEVEL)

    def get_tank_max_level(self, tank_idx: int) -> float:
        """
        Returns the maximum water level of a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Maximum water level.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_MAXLEVEL)

    def get_tank_mix_fraction(self, tank_idx: int) -> float:
        """
        Returns the mixing fraction of a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Mixing fraction.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_MIXFRACTION)

    def get_tank_bulk_decacy(self, tank_idx: int) -> float:
        """
        Returns the bulk decay rate in a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Bulk decay rate.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_TANK_KBULK)

    def can_tank_overflow(self, tank_idx: int) -> bool:
        """
        Checks if a given tank can overflow or not.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `bool`
            True if the tank can overflow, False otherwise.
        """
        return bool(self.getnodevalue(tank_idx, EpanetConstants.EN_CANOVERFLOW))

    def get_pump_type(self, pump_idx: int) -> int:
        """
        Returns the type (type of pump curve) of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump.

        Returns
        -------
        `int`
            Pump curve type. Will be one of the following:

                - EN_CONST_HP
                - EN_POWER_FUNC
                - EN_CUSTOM
                - EN_NOCURVE
        """
        return self.getpumptype(pump_idx)

    def get_pump_energy_price_pattern(self, pump_idx) -> int:
        """
        Returns the index of the energy price pattern of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump.

        Returns
        -------
        `int`
            Pattern index.
        """
        return int(self.getlinkvalue(pump_idx, EpanetConstants.EN_PUMP_EPAT))

    def set_pump_energy_price_pattern(self, pump_idx: int, pattern_idx: int) -> None:
        """
        Sets the energy price pattern of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump.
        pattern_idx : `int`
            Index of the pattern.
        """
        self.setlinkvalue(pump_idx, EpanetConstants.EN_PUMP_EPAT, pattern_idx)

    def get_all_patterns_id(self) -> list[str]:
        """
        Returns a list of all pattern IDs.

        Returns
        -------
        `list[str]`
            List of IDs.
        """
        r = []

        for idx in range(1, self.getcount(EpanetConstants.EN_PATCOUNT) + 1):
            r.append(self.getpatternid(idx))

        return r

    def get_pattern(self, pattern_idx: int) -> list[float]:
        """
        Returns the values of a given pattern.

        Parameters
        ----------
        pattern_idx : `int`
            Index of the pattern.

        Returns
        -------
        `list[float]`
            Pattern values.
        """
        r = []

        for t in range(self.getpatternlen(pattern_idx)):
            r.append(self.getpatternvalue(pattern_idx, t + 1))

        return r

    def set_pattern(self, pattern_idx: int, pattern_values: list[float]) -> None:
        """
        Set the values of a given pattern.

        Parameters
        ----------
        pattern_idx : `int`
            Index of the pattern.
        pattern_values : `list[float]`
            New pattern values.
        """
        self.setpattern(pattern_idx, pattern_values, len(pattern_values))

    def add_pattern(self, pattern_id: str, pattern_values: list[float]) -> None:
        """
        Adds a new pattern.

        Parameters
        ----------
        pattern_id : `str`
            ID of the pattern.
        pattern_values : `list[float]`
            Pattern values.
        """
        self.addpattern(pattern_id)

        idx = self.getpatternindex(pattern_id)
        self.setpattern(idx, pattern_values, len(pattern_values))

    def get_all_links_connecting_nodes_id(self) -> list[tuple[str]]:
        """
        Returns a list of all connecting node IDs for each link in the network.

        Returns
        -------
        `list[tuple[str]]`
            List of tuple of connecting node IDs of all links.
        """
        r = []

        for link_idx in range(self.getcount(EpanetConstants.EN_LINKCOUNT)):
            node1_idx, node2_idx = self.getlinknodes(link_idx + 1)
            r.append((self.get_node_id(node1_idx), self.get_node_id(node2_idx)))

        return r

    def get_pump_avg_energy_price(self, pump_idx: int) -> float:
        """
        Returns the average energy price of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump

        Returns
        -------
        `float`
            Average energy price.
        """
        return self.getlinkvalue(pump_idx, EpanetConstants.EN_PUMP_ECOST)

    def set_pump_avg_energy_price(self, pump_idx: int, price: float) -> float:
        """
        Specifies the average energy price of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump
        price : `float`
            Average energy price.
        """
        self.setlinkvalue(pump_idx, EpanetConstants.EN_PUMP_ECOST, price)

    def get_pump_pattern(self, pump_idx: int) -> int:
        """
        Returns the pattern of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump

        Returns
        -------
        `int`
            Index of the pump pattern.
        """
        return int(self.getlinkvalue(pump_idx, EpanetConstants.EN_LINKPATTERN))

    def set_pump_pattern(self, pump_idx: int, pattern_idx: int) -> None:
        """
        Specifies the pattern of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump
        pattern_idx : `int`
            Index of the pattern.
        """
        self.setlinkvalue(pump_idx, EpanetConstants.EN_LINKPATTERN, pattern_idx)

    def set_node_data(self, node_idx: int, elev: float, base_demand: float,
                      demand_pattern_id: str) -> None:
        """
        Specifies some properties, such as elevation and demand, of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.
        elev : `float`
            Eleveation of the node.
        base_demand : `float`
            Base demand of the node.
        demand_pattern_id : `str`
            ID of the primary demand pattern of the node.
        """
        self.setjuncdata(node_idx, elev, base_demand, demand_pattern_id)

    def set_node_source(self, node_idx: int, source_type: int, source_strengh: float,
                        pattern_idx: int) -> None:
        """
        Specifies the quality source of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.
        source_type : `int`
            Type of the source. Must be one of the following:

                - EN_CONCEN
                - EN_MASS
                - EN_SETPOINT
                - EN_FLOWPACED
        source_strength : `float`
            Source strength.
        pattern_idx : `int`
            Index of the source pattern.
        """
        self.setnodevalue(node_idx, EpanetConstants.EN_SOURCETYPE, source_type)
        self.setnodevalue(node_idx, EpanetConstants.EN_SOURCEQUAL, source_strengh)

        if pattern_idx is not None:
            self.setnodevalue(node_idx, EpanetConstants.EN_SOURCEPAT, pattern_idx)

    def set_node_source_quality(self, node_idx, source_strength: float) -> None:
        """
        Specifies the strength of a node quality source.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.
        source_strength : `float`
            Source strength.
        """
        self.setnodevalue(node_idx, EpanetConstants.EN_SOURCEQUAL, source_strength)

    def get_node_init_quality(self, node_idx: int) -> float:
        """
        Returns the initial quality (e.g., concentration) of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Initial quality.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_INITQUAL)

    def set_node_init_quality(self, node_idx: int, init_qual: float) -> None:
        """
        Specifies the initial quality (e.g., concentration) of a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.
        init_qual : `float`
            Initial quality.
        """
        self.setnodevalue(node_idx, EpanetConstants.EN_INITQUAL, init_qual)

    def get_pipe_wall_reaction_order(self) -> int:
        """
        Returns the pipe wall reaction order.

        Returns
        -------
        `int`
            Reaction oder.
        """
        return int(self.getoption(EpanetConstants.EN_WALLORDER))

    def get_pipe_bulk_reaction_order(self) -> int:
        """
        Returns the the pipe bulk reaction order.

        Returns
        -------
        `int`
            Reaction order.
        """
        return int(self.getoption(EpanetConstants.EN_BULKORDER))

    def get_link_wall_raction_coeff(self, link_idx: int) -> float:
        """
        Returns the wall reaction coefficient of a given link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Wall reaction coefficient.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_KWALL)

    def get_link_bulk_raction_coeff(self, link_idx: int) -> float:
        """
        Returns the bulk reaction coefficient of a link.

        Parameters
        ----------
        link_idx : `int`
            Index of the link.

        Returns
        -------
        `float`
            Bulk reaction coefficient.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_KBULK)

    def get_tank_bulk_reaction_coeff(self, tank_idx: int) -> float:
        """
        Returns the bulk reaction coefficient of a given tank.

        Parameters
        ----------
        tank_idx : `int`
            Index of the tank.

        Returns
        -------
        `float`
            Bulk reaction coefficient.
        """
        return self.getnodevalue(tank_idx, EpanetConstants.EN_TANK_KBULK)

    def get_limiting_concentration(self) -> float:
        """
        Returns the limiting concentration in reactions.

        Returns
        -------
        `float`
            Limiting concentration.
        """
        return self.getoption(EpanetConstants.EN_CONCENLIMIT)

    def get_quality_tolerance(self) -> float:
        """
        Returns the water quality tolerance.

        Returns
        -------
        `float`
            Water quality tolerance.
        """
        return self.getoption(EpanetConstants.EN_TOLERANCE)

    def get_specific_diffusivity(self) -> float:
        """
        Returns the specific diffusivity.

        Returns
        -------
        `float`
            Specific diffusivity.
        """
        return self.getoption(EpanetConstants.EN_SP_DIFFUS)

    def get_specific_gravity(self) -> float:
        """
        Returns the specific gravity.

        Returns
        -------
        `float`
            Specific gravity.
        """
        return self.getoption(EpanetConstants.EN_SP_GRAVITY)

    def get_specific_viscosity(self) -> float:
        """
        Returns the specific viscosity.

        Returns
        -------
        `float`
            Specific viscosity.
        """
        return self.getoption(EpanetConstants.EN_SP_VISCOS)

    def get_tank_bulk_reaction_order(self) -> int:
        """
        Returns the bulk reaction order in tanks.

        Returns
        -------
        `int`
            Bulk reaction order.
        """
        return int(self.getoption(EpanetConstants.EN_TANKORDER))

    def get_node_quality(self, node_idx: int) -> float:
        """
        Returns the current quality value at a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Current node quality value.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_QUALITY)

    def get_link_quality(self, link_idx: int) -> float:
        """
        Returns the current quality value (e.g., concentration, age, ...) at a given link.

        Parameters
        ----------
        `link_idx`
            Index of the link.

        Returns
        -------
        `float`
            Current link quality value.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_LINKQUAL)

    def get_node_pressure(self, node_idx: int) -> float:
        """
        Returns the current pressure at a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Current pressure.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_PRESSURE)

    def get_node_head(self, node_idx: int) -> float:
        """
        Returns the current hydraulic head at a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Current hydraulic head.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_HEAD)

    def get_node_demand(self, node_idx: int) -> float:
        """
        Returns the current demand at a given node.

        Parameters
        ----------
        node_idx : `int`
            Index of the node.

        Returns
        -------
        `float`
            Current demand.
        """
        return self.getnodevalue(node_idx, EpanetConstants.EN_DEMAND)

    def get_link_flow(self, link_idx: int) -> float:
        """
        Returns the current flow rate at a given link.

        Parameters
        ----------
        `link_idx`
            Index of the link.

        Returns
        -------
        `float`
            Current flow rate.
        """
        return self.getlinkvalue(link_idx, EpanetConstants.EN_FLOW)

    def get_pump_status(self, pump_idx: int) -> int:
        """
        Returns the current pump status.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump.

        Returns
        -------
        `int`
            Current pump status. Will be one of the following:

                - EN_PUMP_XHEAD
                - EN_PUMP_CLOSED
                - EN_PUMP_OPEN
                - EN_PUMP_XFLOW
        """
        return int(self.getlinkvalue(pump_idx, EpanetConstants.EN_PUMP_STATE))

    def set_pump_status(self, pump_idx: int, status: int) -> None:
        """
        Sets the the current status of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump
        status : `int`
            Pump status. Must be one of the following:

                - EN_CLOSED
                - EN_OPEN
        """
        self.setlinkvalue(pump_idx, EpanetConstants.EN_STATUS, status)

    def get_pump_energy_usage(self, pump_idx: int) -> float:
        """
        Returns the current energy usage of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump

        Returns
        -------
        `float`
            Current energy usage.
        """
        return self.getlinkvalue(pump_idx, EpanetConstants.EN_ENERGY)

    def get_pump_efficiency(self, pump_idx: int) -> float:
        """
        Returns the current effciency of a given pump.

        Parameters
        ----------
        pump_idx : `int`
            Index of the pump

        Returns
        -------
        `float`
            Current pump effciency.
        """
        return self.getlinkvalue(pump_idx, EpanetConstants.EN_PUMP_EFFIC)

    def get_valve_status(self, valve_idx: int) -> int:
        """
        Returns the current status of a given valve.

        Parameters
        ----------
        valve_idx : `int`
            Index of the valve.

        Returns
        -------
        `int`
            Current status. Will be one of the following:

                - EN_CLOSED
                - EN_OPEN
        """
        return int(self.getlinkvalue(valve_idx, EpanetConstants.EN_STATUS))

    def set_valve_status(self, valve_idx, status: int):
        """
        Sets the current status of a given valve.

        Parameters
        ----------
        valve_idx : `int`
            Index of the valve.
        status : `int`
            New status of the valve. Must be one of the following:

                - EN_CLOSED
                - EN_OPEN
        """
        self.setlinkvalue(valve_idx, EpanetConstants.EN_STATUS, status)

    def split_pipe(self, pipe_id: str, new_pipe_id: str, new_node_id: str) -> None:
        """
        Splits a pipe (pipeID), creating two new pipes (pipeID and newPipeID) and adds a
        junction/node (newNodeID) in between. If the pipe is linear
        the pipe is splitted in half, otherwisw the middle point of
        the vertice array elemnts is taken as the split point.
        The two new pipes have the same properties as the one which is splitted.
        The new node's properties are the same with the nodes on the left and right
        and New Node Elevation and Initial quality is the average of the two.

        Note that this code is taken from EPyT -- slightly modified to fit into this toolkit.

        Parameters
        ----------
        pipe_id : `str`
            ID of the pipe to be split.
        new_pipe_id : `str`
            ID of the new pipe.
        new_node_id : `str`
            ID of the new node, placed in the middle of the splitted pipe.
        """
        # Find the coordinates of the Nodes connected with the link/pipe
        pipeIndex = self.get_link_idx(pipe_id)
        nodesIndex = self.getlinknodes(pipeIndex)
        leftNodeIndex = nodesIndex[0]
        rightNodeIndex = nodesIndex[1]
        coordNode1 = self.getcoord(leftNodeIndex)
        coordNode2 = self.getcoord(rightNodeIndex)

        if coordNode1[0] == 0 and coordNode1[1] == 0 \
                and coordNode2[0] == 0 and coordNode2[1] == 0:
            raise ValueError('Some nodes have zero values for coordinates')

        if self.getvertexcount(pipeIndex) == 0:
            # Calculate mid position of the link/pipe based on nodes
            midX = (coordNode1[0] + coordNode2[0]) / 2
            midY = (coordNode1[1] + coordNode2[1]) / 2
        else:
            # Calculate mid position based on vertices pick midpoint of vertices
            xVert = []
            yVert = []
            for i in range(self.getvertexcount(pipeIndex)):
                x, y = self.getvertex(pipeIndex, i)
                xVert.append(x)
                yVert.append(y)

            xMidPos = int(len(xVert) / 2)
            midX = xVert[xMidPos]
            midY = yVert[xMidPos]

        # Add the new node between the link/pipe and add the same properties
        # as the left node (the elevation is the average of left-right nodes)
        index = self.addnode(new_node_id, EpanetConstants.EN_JUNCTION)
        self.setcoord(index, midX, midY)

        newNodeIndex = self.get_node_idx(new_node_id)
        midElev = (self.get_node_elevation(leftNodeIndex) +
                   self.get_node_elevation(rightNodeIndex)) / 2
        self.setjuncdata(newNodeIndex, midElev, 0, "")
        self.setnodevalue(newNodeIndex, EpanetConstants.EN_EMITTER,
                          self.get_node_emitter_coeff(leftNodeIndex))
        if self.getqualtype()[0] > 0:
            midInitQual = (self.get_node_init_quality(leftNodeIndex) +
                           self.get_node_init_quality(rightNodeIndex)) / 2
            self.set_node_init_quality(newNodeIndex, midInitQual)
            self.set_node_source_quality(newNodeIndex, self.get_node_source_qual(leftNodeIndex))
            self.setnodevalue(newNodeIndex, EpanetConstants.EN_SOURCEPAT,
                              self.getnodevalue(leftNodeIndex, EpanetConstants.EN_SOURCEPAT))
            if self.getnodevalue(leftNodeIndex, EpanetConstants.EN_SOURCETYPE) != 0:
                self.setnodevalue(newNodeIndex, EpanetConstants.EN_SOURCETYPE,
                                  self.getnodevalue(leftNodeIndex, EpanetConstants.EN_SOURCETYPE))

        # Access link properties
        linkDia = self.get_link_diameter(pipeIndex)
        linkLength = self.get_link_length(pipeIndex)
        linkRoughnessCoeff = self.get_link_roughness(pipeIndex)
        linkMinorLossCoeff = self.get_link_minorloss(pipeIndex)
        linkInitialStatus = self.get_link_init_status(pipeIndex)
        linkInitialSetting = self.get_link_init_setting(pipeIndex)
        linkBulkReactionCoeff = self.get_link_bulk_raction_coeff(pipeIndex)
        linkWallReactionCoeff = self.get_link_wall_raction_coeff(pipeIndex)

        # Delete the link/pipe that is splitted
        self.deletelink(pipeIndex, 0)

        # Add two new pipes
        # d.addLinkPipe(pipeID, fromNode, toNode)
        # Add the Left Pipe and add the same properties as the deleted link
        leftNodeID = self.get_node_id(leftNodeIndex)
        leftPipeIndex = self.addlink(pipe_id, EpanetConstants.EN_PIPE, leftNodeID, new_node_id)
        self.setlinknodes(leftPipeIndex, leftNodeIndex, newNodeIndex)
        self.setpipedata(leftPipeIndex, linkLength, linkDia, linkRoughnessCoeff, linkMinorLossCoeff)
        self.setlinkvalue(leftPipeIndex, EpanetConstants.EN_INITSTATUS, linkInitialStatus)
        self.setlinkvalue(leftPipeIndex, EpanetConstants.EN_INITSETTING, linkInitialSetting)
        self.setlinkvalue(leftPipeIndex, EpanetConstants.EN_KBULK, linkBulkReactionCoeff)
        self.setlinkvalue(leftPipeIndex, EpanetConstants.EN_KWALL, linkWallReactionCoeff)

        # Add the Right Pipe and add the same properties as the deleted link
        rightNodeID = self.get_node_id(rightNodeIndex)
        rightPipeIndex = self.addlink(new_pipe_id, EpanetConstants.EN_PIPE, new_node_id, rightNodeID)
        self.setlinknodes(rightPipeIndex, newNodeIndex, rightNodeIndex)
        self.setpipedata(rightPipeIndex, linkLength, linkDia, linkRoughnessCoeff,
                         linkMinorLossCoeff)
        self.setlinkvalue(rightPipeIndex, EpanetConstants.EN_INITSTATUS, linkInitialStatus)
        self.setlinkvalue(rightPipeIndex, EpanetConstants.EN_INITSETTING, linkInitialSetting)
        self.setlinkvalue(rightPipeIndex, EpanetConstants.EN_KBULK, linkBulkReactionCoeff)
        self.setlinkvalue(rightPipeIndex, EpanetConstants.EN_KWALL, linkWallReactionCoeff)

    def _parse_msx_file(self) -> dict:
        if self._msx_file is None:
            raise ValueError("No .msx file loaded")

        # Code for parsing .msx files taken from EPyT
        keys = ["AREA_UNITS", "RATE_UNITS", "SOLVER", "COUPLING", "TIMESTEP", "ATOL", "RTOL",
                "COMPILER", "SEGMENTS", "PECLET"]
        float_values = ["TIMESTEP", "ATOL", "RTOL", "SEGMENTS", "PECLET"]
        values = {key: None for key in keys}

        # Flag to determine if we're in the [OPTIONS] section
        in_options = False

        # Open and read the file
        with open(self._msx_file, 'r') as file:
            for line in file:
                # Check for [OPTIONS] section
                if "[OPTIONS]" in line:
                    in_options = True
                elif "[" in line and "]" in line:
                    in_options = False  # We've reached a new section

                if in_options:
                    # Pattern to match the keys and extract values, ignoring comments and whitespace
                    pattern = re.compile(r'^\s*(' + '|'.join(keys) + r')\s+(.*?)\s*(?:;.*)?$')
                    match = pattern.search(line)
                    if match:
                        key, value = match.groups()
                        if key in float_values:
                            values[key] = float(value)
                        else:
                            values[key] = value
            return values

    def get_msx_time_step(self) -> int:
        """
        Returns the MSX time step.

        Returns
        -------
        `int`
            Time step.
        """
        return int(self._parse_msx_file()["TIMESTEP"])

    def set_msx_time_step(self, time_step: int) -> None:
        """
        Specifies the MSX time step.

        Parameters
        ----------
        time_step : `int`
            New MSX time step.
        """
        temp_folder = tempfile.gettempdir()
        file_name = os.path.basename(self._msx_file)
        temp_file = os.path.join(temp_folder, file_name)

        self.MSXsavemsxfile(temp_file)
        self.MSXclose()

        with open(temp_file, 'r+') as f:    # Code taken from EPyT -- workaround for missing functions
            lines = f.readlines()
            options_index = -1
            flag = 0
            for i, line in enumerate(lines):
                if line.strip() == '[OPTIONS]':
                    options_index = i
                elif line.strip().startswith("TIMESTEP"):
                    lines[i] = "TIMESTEP" + "\t" + str(time_step) + "\n"
                    flag = 1
            if flag == 0 and options_index != -1:
                lines.insert(options_index + 1, "TIMESTEP" + "\t" + str(time_step) + "\n")
            f.seek(0)
            f.writelines(lines)
            f.truncate()

        self.MSXopen(temp_file)
        self._msx_file = temp_file

    def get_msx_options(self) -> dict:
        """
        Returns the MSX options as specified in the .msx file.

        Returns
        -------
        `dict`
            Dictionary of MSX options as specified in the .msx file -- note that not all
            options might be specified.
            Possible options (dictinary keys) are: REA_UNITS, RATE_UNITS, SOLVER, COUPLING,
            TIMESTEP, ATOL, RTOL, COMPILER, SEGMENTS, PECLET
        """
        return self._parse_msx_file()

    def add_msx_pattern(self, pattern_id: str, pattern_mult: list[float]) -> None:
        """
        Adds a new MSX pattern.

        Parameters
        ----------
        pattern_id : `str`
            ID of the new pattern.
        pattern_mult : `list[float]`
            Pattern values (i.e., multipliers).
        """
        self.MSXaddpattern(pattern_id)
        pattern_idx = self.MSXgetindex(EpanetConstants.MSX_PATTERN, pattern_id)
        self.MSXsetpattern(pattern_idx, pattern_mult, len(pattern_mult))

    def set_msx_source(self, node_id: str, species_id: str, source_type: int,
                       source_concentration: float, msx_pattern_id: str) -> None:
        """
        Adds a species source (i.e., injection of a given species) at a given node.

        Parameters
        ----------
        node_id : `str`
            ID of the node where the species in injected into the network.
        species_id : `str`
            ID of the species to be injected.
        source_type : `int`
            Type of injection/source. Must be one of the following:

                - MSX_NOSOURCE  = -1 for no source,
                - MSX_CONCEN    =  0 for a concentration source,
                - MSX_MASS      =  1 for a mass booster source,
                - MSX_SETPOINT  =  2 for a setpoint source,
                - MSX_FLOWPACED =  3 for a flow paced source;
        source_concentration : `float`
            Injetion concentration -- can change over time according the the pattern of multiplies.
        msx_pattern_id : `str`
            ID of the injection pattern -- i.e., multipliers.
        """
        node_idx = self.get_node_idx(node_id)
        species_idx = self.get_msx_species_idx(species_id)
        msx_pattern_idx = self.MSXgetindex(EpanetConstants.MSX_PATTERN, msx_pattern_id)

        self.MSXsetsource(node_idx, species_idx, source_type, source_concentration, msx_pattern_idx)

    def get_msx_species_init_concentration(self, obj_type: int, obj_index: int,
                                           species_idx: int) -> float:
        """
        Returns the initial concentration of a given species at a given location in the network.

        Parameters
        ----------
        obj_type : `int`
            Type of the location (i.e., node or link). Must be one of the following:

                - MSX_NODE
                - MSX_LINK
        obj_index : `int`
            Index of the link or node.
        species_idx : `int`
            Index of the species.

        Returns
        -------
        `float`
            Initial concentration.
        """
        return self.MSXgetinitqual(obj_type, obj_index, species_idx)

    def get_msx_species_concentration(self, obj_type: int, obj_index: int,
                                      species_idx: int) -> float:
        """
        Returns the current concentration of a given species at a given location in the network.

        Parameters
        ----------
        obj_type : `int`
            Type of the location (i.e., node or link). Must be one of the following:

                - MSX_NODE
                - MSX_LINK
        obj_index : `int`
            Index of the link or node.
        species_idx : `int`
            Index of the species.

        Returns
        -------
        `float`
            Species concentration.
        """
        return self.MSXgetqual(obj_type, obj_index, species_idx)

    def get_all_msx_species_id(self) -> list[str]:
        """
        Returns a list of all species IDs.

        Returns
        -------
        `list[str]`
            List of all species IDs.
        """
        return [self.MSXgetID(EpanetConstants.MSX_SPECIES, i + 1)
                for i in range(self.MSXgetcount(EpanetConstants.MSX_SPECIES))]

    def get_msx_species_idx(self, species_id) -> int:
        """
        Returns the index of a given species.

        Parameters
        ----------
        species_id : `str`
            ID of the species.

        Returns
        -------
        `int`
            Index of the species.
        """
        return self.MSXgetindex(EpanetConstants.MSX_SPECIES, species_id)

    def get_num_msx_species(self) -> int:
        """
        Returns the total number of bulk and wall species.

        Returns
        -------
        `int`
            Number of species.
        """
        return self.MSXgetcount(EpanetConstants.MSX_SPECIES)

    def get_msx_species_info(self, species_idx: int) -> dict:
        """
        Returns information about a given species.

        Parameters
        ----------
        species_idx : `int`
            Index of the species.

        Returns
        -------
        `dict`
            Information as a dictionary. Will contains the following entries:

                - 'type': MSX_BULK for a bulk flow species or MSX_WALL for a surface species;
                - 'units': mass units;
                - 'atol': absolute concentration tolerance (concentration units);
                - 'rtol': relative concentration tolerance (unitless);
        """
        return dict(zip(["type", "units", "atol", "rtol"], self.MSXgetspecies(species_idx)))

    def get_all_msx_species_info(self) -> list[dict]:
        """
        Returns information about all species.

        Returns
        -------
        `list[dict]`
            List of species information -- ordered by species index.#
            Each entry in the list contains a dictionary with the following entries:

                - 'type': MSX_BULK for a bulk flow species or MSX_WALL for a surface species;
                - 'units': mass units;
                - 'atol': absolute concentration tolerance (concentration units);
                - 'rtol': relative concentration tolerance (unitless);
        """
        return [self.get_msx_species_info(i + 1)
                for i in range(self.MSXgetcount(EpanetConstants.MSX_SPECIES))]

    def get_all_bulk_species_id(self) -> list[str]:
        """
        Returns the IDs of all bulk species.

        Returns
        -------
        `list[int]`
            List of IDs.
        """
        r = []

        for i in range(self.MSXgetcount(EpanetConstants.MSX_SPECIES)):
            if self.MSXgetspecies(i + 1)[0] == EpanetConstants.MSX_BULK:
                r.append(self.get_msx_species_idx(i + 1))

        return r

    def get_all_bulk_species_idx(self) -> list[int]:
        """
        Returns the indices of all bulk species.

        Returns
        -------
        `list[int]`
            List of indices.
        """
        r = []

        for i in range(self.MSXgetcount(EpanetConstants.MSX_SPECIES)):
            if self.MSXgetspecies(i + 1)[0] == EpanetConstants.MSX_BULK:
                r.append(i + 1)

        return r

    def get_all_wall_species_id(self) -> list[str]:
        """
        Returns the IDs of all wall species.

        Returns
        -------
        `list[int]`
            List of IDs.
        """
        r = []

        for i in range(self.MSXgetcount(EpanetConstants.MSX_SPECIES)):
            if self.MSXgetspecies(i + 1)[0] == EpanetConstants.MSX_WALL:
                r.append(self.get_msx_species_idx(i + 1))

        return r

    def get_all_wall_species_idx(self) -> list[int]:
        """
        Returns the indices of all wall species.

        Returns
        -------
        `list[int]`
            List of indices.
        """
        r = []

        for i in range(self.MSXgetcount(EpanetConstants.MSX_SPECIES)):
            if self.MSXgetspecies(i + 1)[0] == EpanetConstants.MSX_WALL:
                r.append(i + 1)

        return r

    def get_msx_pattern(self, pattern_idx: int) -> list[float]:
        """
        Returns a particular MSX pattern -- i.e., returns the multipliers.

        Parameters
        ----------
        pattern_idx: `int`
            Index of the pattern.

        Returns
        -------
        `list[float]`
            Pattern multipliers.
        """
        r = []

        pattern_length = self.MSXgetpatternlen(pattern_idx)
        for idx in range(1, pattern_length + 1):
            r.append(self.MSXgetpatternvalue(pattern_idx, idx))

        return r

    def get_all_msx_pattern_id(self) -> list[str]:
        """
        Returns a list of the IDs of all MSX patterns.

        Returns
        -------
        `list[str]`
            List of patterns (IDs).
        """
        r = []

        n_msx_patterns = self.MSXgetcount(EpanetConstants.MSX_PATTERN)
        for pattern_idx in range(1, n_msx_patterns + 1):
            r.append(self.MSXgetID(EpanetConstants.MSX_PATTERN, pattern_idx))

        return r
