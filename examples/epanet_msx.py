"""
Basic example demonstrating how to run an EPANET-MSX simulation.
"""
from epanet_plus import EPyT, EpanetConstants


if __name__ == "__main__":
    # Load an .inp and .msx file -- recall that for using EPANET-MSX,
    # we have to fall back to EPANET < 2.2 (i.e., use_project=False)
    epanet_api = EPyT("net2-cl2.inp", use_project=False)
    epanet_api.load_msx_file("net2-cl2.msx")

    print(f"Simulation duration: {epanet_api.gettimeparam(EpanetConstants.EN_DURATION)}")

    # Solve hydraulics by calling MSXsolveH -- alternatively, the hydraulics can be solved
    # in EPANET once and exported as a .hyd file, which can then be loaded into EPANET-MSX
    epanet_api.MSXsolveH()

    #epanet_api.solveH()    # Only do this once -- you can then just load the .hyd file
    #epanet_api.savehydfile("mySimNet2.hyd")
    #epanet_api.MSXusehydfile("mySimNet2.hyd")

    # Run EPANET-MSX simulation
    epanet_api.MSXinit(0)
    print(f"Species ID: {epanet_api.MSXgetindex(EpanetConstants.MSX_SPECIES, 'CL2')}")

    while True:
        t, tleft = epanet_api.MSXstep()

        print(f"{epanet_api.MSXgetqual(EpanetConstants.MSX_NODE, 2, 1)} mg/L")

        if tleft == 0:
            break

    epanet_api.close()
