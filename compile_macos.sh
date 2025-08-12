#!/bin/bash
mkdir -p "../customlibs/"
gcc-15 -w -O3 -march=native -dynamiclib -fPIC -install_name libepanetplus.dylib -o "bin/libepanetplus.dylib" epanet-src/*.c -Iepanet-src/include epanet-src/util/*.c -Iepanet-src/util/  epanet-msx-src/*.c -Iepanet-msx-src/include src/*.c -Isrc/include -Iepanet-src -Depanetmsx_EXPORTS -lc -lm -pthread -lgomp  -fopenmp