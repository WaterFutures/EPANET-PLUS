[![pypi](https://img.shields.io/pypi/v/epanet-plus.svg)](https://pypi.org/project/epanet-plus/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![PyPI - Python Version](https://img.shields.io/pypi/pyversions/epanet-plus)
[![Build + Test](https://github.com/WaterFutures/EPANET-PLUS/actions/workflows/build_test.yml/badge.svg)](https://github.com/WaterFutures/EPANET-PLUS/actions/workflows/build_test.yml)
[![Documentation Status](https://readthedocs.org/projects/epanet-plus/badge/?version=stable)](https://epanet-plus.readthedocs.io/en/stable/?badge=stable)
[![Downloads](https://static.pepy.tech/badge/epanet-plus)](https://pepy.tech/project/epanet-plus)
[![Downloads](https://static.pepy.tech/badge/epanet-plus/month)](https://pepy.tech/project/epanet-plus)

# EPANET-PLUS

EPANET-PLUS is a C library that merges [EPANET](https://github.com/OpenWaterAnalytics/EPANET) 
and [EPANET-MSX](https://github.com/OpenWaterAnalytics/epanet-msx) into a single library.
Most importantly, it also provides a Python package with a high-performance interface
(i.e., C extension) to the C library, together with additional helper functions for an easier
use of EPANET and EPANET-MSX.

## Unique Features

Unique features of EPANET-PLUS that make it superior to other Python interfaces of EPANET are the following:

- High-performance (single) interface to the latest version of EPANET and EPANET-MSX
- Additional C-functions to extend EPANET and EPANET-MSX
- Python toolkit with handy functions for working with EPANET and EPANET-MSX 

## Installation

Note that EPANET-PLUS supports Python 3.9 - 3.13. 
The Python package contains the the C library as a C extension and is
already pre-build for all major platforms.

### PyPI

```
pip install epanet-plus
```


### Git

Download or clone the repository:

```
git clone https://github.com/WaterFutures/EPANET-PLUS.git
cd EPANET-PLUS
```

Install all requirements as listed in [REQUIREMENTS.txt](https://raw.githubusercontent.com/WaterFutures/EPANET-PLUS/main/REQUIREMENTS.txt):

```
pip install -r REQUIREMENTS.txt
```

Build and install the package:

```
pip install .
```

## Quick Example

```python
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
```

## Documentation

Documentation is available on readthedocs: [https://epanet-plus.readthedocs.io/en/latest/](https://epanet-plus.readthedocs.io/en/stable)

# License

MIT license -- see [LICENSE](LICENSE)

## How to Cite?

If you use this software, please cite it as follows:

```bibtex
@misc{github:epanetplus,
        author = {André Artelt},
        title = {{EPANET-PLUS}},
        year = {2025},
        publisher = {GitHub},
        journal = {GitHub repository},
        howpublished = {https://github.com/WaterFutures/EPANET-PLUS}
}
```

## How to get Support?

If you come across any bug or need assistance please feel free to open a new
[issue](https://github.com/WaterFutures/EPyT-Flow/issues/)
if non of the existing issues answers your questions.

## How to Contribute?

Contributions (e.g. creating issues, pull-requests, etc.) are welcome --
please make sure to read the [code of conduct](CODE_OF_CONDUCT.md) and
follow the [developers' guidelines](DEVELOPERS.md).
