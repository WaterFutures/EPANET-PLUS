.. _usage:

***********
Basic Usage
***********

Quick example
-------------

.. raw:: html

    <a target="_blank" href="https://colab.research.google.com/github/WaterFutures/EPANET-PLUS/blob/main/docs/examples/basic_usage.ipynb">
    <img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/>
    </a>

.. code-block:: python

    from epanet_plus import EPyT, EpanetConstants

    if __name__ == "__main__":
        # Load an .inp file in EPANET using the toolkit class
        epanet_api = EPyT("net2-cl2.inp")

        # Print some general information
        print(f"All nodes: {epanet_api.get_all_nodes_id()}")
        print(f"All links: {epanet_api.get_all_links_id()}")
        
        print(f"Simulation duration in seconds: {epanet_api.get_simulation_duration()}")
        print(f"Hydraulic time step in seconds: {epanet_api.get_hydraulic_time_step()}")
        print(f"Demand model: {epanet_api.get_demand_model()}")

        # Run hydraulic simulation and output pressure at each node (at every simulation step)
        epanet_api.openH()
        epanet_api.initH(EpanetConstants.EN_NOSAVE)

        tstep = 1
        r = []
        while tstep > 0:
            t = epanet_api.runH()

            print(epanet_api.getnodevalues(EpanetConstants.EN_PRESSURE))

            tstep = epanet_api.nextH()

        epanet_api.closeH()

        # Close EPANET
        epanet_api.close()


More examples
-------------

More complete examples can be found in the `examples` folder in the GitHub repository
and also in the provided :ref:`Jupyter notebooks <tut.examples>`.
