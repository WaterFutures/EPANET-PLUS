Introduction
============

The Python package contains two important classes, the EPANET wrapper
:class:`~epanet_plus.epanet_wrapper.EpanetAPI` for direct access to EPANET and EPANET-MSX functions,
and the EPANET toolkit class :class:`~epanet_plus.epanet_toolkit.EPyT` for a high-level interface
to EPANET functions.

EPANET API
++++++++++

Besides providing an interface for each C-function from EPANET and EPANET-MSX,
the :class:`~epanet_plus.epanet_wrapper.EpanetAPI` class also implements an error handling that
allows the user fine-grained control over the handling of warnings and errors that may occur when
calling EPANET-(MSX) functions. The user can decide to:

- output a warning
- raise an exception
- ignore certain warnings/errors.

The initial behavior on warnings can be specified in the constructor of
:class:`~epanet_plus.epanet_wrapper.EpanetAPI`.
However, this behavior can also be changed later by using the function
:func:`~epanet_plus.epanet_wrapper.EpanetAPI.set_error_handling`

.. code-block:: python

    # Create new instance of EPANET
    epanet = EpanetAPI()

    # ...

    # Change error/warning handling
    # Output warnings but ignore the following EPANET error codes: 110, 120
    epanet.set_error_handling(raise_exception_on_error=False, warn_on_error=True,
                              ignore_error_codes=[110, 120])

Furthermore, all EPANET-(MSX) constants are also defined in the
:class:`~epanet_plus.epanet_toolkit.EpanetConstants` class, and the
:class:`~epanet_plus.epanet_wrapper.EpanetAPI` class also abstracts away from the
different EPANET version (e.g., EPANET-MSX is not compatible with projects and EPANET >= 2.2) and
automatically includes the pointer to the current project if projects are used (i.e., EPANET >= 2.2).
However, the user still has the opportunity to directly call specific EPANET-(MSX)
C functions -- this is only advisable if you know what you are doing!

.. code-block:: python

    from epanet_plus import epanet, EpanetAPI

    # Open new EPANET instance
    # Note that it uses EPANET < 2.2 by default
    epanet_api = EpanetAPI()

    # Load an .inp file using ENopen
    epanet_api.open("Net1.inp", "Net1.rpt", "")

    # Print the title of the network
    print(epanet_api.gettitle())

    # Calling the C function ENgettitle directly
    print(epanet.ENgettitle())

    # Do not forget to close EPANET
    epanet_api.close()


Example of using projects (i.e., EPANET >= 2.2):

.. code-block:: python

    from epanet_plus import epanet, EpanetAPI

    # Open new EPANET instance and create a new project
    # Note that use_project=True => latest EPANET (i.e, >= 2.2)
    epanet_api = EpanetAPI(use_project=True)
    epanet_api.createproject()

    # Load an .inp file using EN_open
    epanet_api.open("Net1.inp", "Net1.rpt", "")

    # Print the title of the network
    print(epanet_api.gettitle())

    # Calling the C function EN_gettitle directly
    print(epanet.EN_gettitle(epanet_api.ph))

    # Do not forget to close EPANET and delete the project
    epanet_api.close()
    epanet_api.deleteproject()


EPANET Toolkit
++++++++++++++

The :class:`~epanet_plus.epanet_toolkit.EPyT` class builds on top of
:class:`~epanet_plus.epanet_wrapper.EpanetAPI` and provides a more high-level interface for working
with EPANET-(MSX). It also takes care of creating and deleting projects, as well as releasing all
other resources when closing -- for this, the :class:`~epanet_plus.epanet_toolkit.EPyT` class
supports the ``with`` statement.
However, the user still has the opportunity to directly call specific EPANET-(MSX)
C functions -- only advisable if you know what you are doing.

A detailed list of all functions, their parameters and return values, can be found in the
documentation of the :class:`~epanet_plus.epanet_toolkit.EPyT` class.

Example of running a simulation of an .inp file:

.. code-block:: python

    from epanet_plus import EPyT, EpanetConstants

    # Load an .inp file in EPANET using the toolkit class and
    # run a hydraulic simulation and output pressure at each node (at every simulation step)
    with EPyT("net2-cl2.inp") as epanet_api:
        epanet_api.openH()
        epanet_api.initH(EpanetConstants.EN_NOSAVE)

        tstep = 1
        while tstep > 0:
            t = epanet_api.runH()

            print(epanet_api.getnodevalues(EpanetConstants.EN_PRESSURE))

            tstep = epanet_api.nextH()

        epanet_api.closeH()
