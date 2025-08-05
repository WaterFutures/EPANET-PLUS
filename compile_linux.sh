#!/bin/bash
mkdir -p "bin/"
gcc -w -O3 -march=native -shared -Wl,-soname,libepanetplus.so -fPIC -o "bin/libepanetplus.so" epanet-src/*.c -Iepanet-src/include  epanet-msx-src/*.c -Iepanet-msx-src/include -Iepanet-src -Depanetmsx_EXPORTS -lc -lm -pthread -lgomp  -fopenmp
