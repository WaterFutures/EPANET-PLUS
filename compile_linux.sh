#!/bin/bash
mkdir -p "bin/"
gcc -w -O3 -march=native -shared -Wl,-soname,libepanetplus.so -fPIC -o "bin/libepanetplus.so" epanet-src/*.c -Iepanet-src/include epanet-src/util/*.c -Iepanet-src/util/  epanet-msx-src/*.c -Iepanet-msx-src/include src/*.c -Isrc/include -Iepanet-src -Depanetmsx_EXPORTS -lc -lm -pthread -lgomp  -fopenmp
