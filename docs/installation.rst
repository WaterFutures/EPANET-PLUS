.. _installation:

************
Installation
************


Compilation of the C library
++++++++++++++++++++++++++++

.. note::

    Each release of EPANET-PLUS contains binaries build for all major platforms.

We offer platform-specific scripts for building the C library -- note that those
require the latest version of `gcc`:

    - Linux: `compile_linux.sh <https://raw.githubusercontent.com/WaterFutures/EPANET-PLUS/main/compile_linux.sh>`_
    - MacOS: `compile_macos.sh <https://raw.githubusercontent.com/WaterFutures/EPANET-PLUS/main/compile_macos.sh>`_


Installation of the Python Package
++++++++++++++++++++++++++++++++++

Note that EPANET-PLUS supports Python 3.9 - 3.13

.. note::

    The Python package contains the the C library as a C extension and is already pre-build
    for all major platforms.

PyPI
----

.. code:: bash

    pip install epanet-plus


Git
---

Download or clone the repository:

.. code:: bash

    git clone https://github.com/WaterFutures/EPANET-PLUS.git
    cd EPANET-PLUS

Install all requirements as listed in `REQUIREMENTS.txt <https://raw.githubusercontent.com/WaterFutures/EPANET-PLUS/main/REQUIREMENTS.txt>`_:

.. code:: bash

    pip install -r REQUIREMENTS.txt


Build and install the package:

.. code:: bash

    pip install .


.. note::

    This step triggers the build of the C extension, which requires a C compiler to be
    installed on the system.
