#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build && mkdir build/ && cd build

export CXX=$(which g++)
export CC=$(which gcc)

lshw -C display
vulkaninfo --summary

# gcc uses libstdc++ by default
cmake .. \
-G Ninja \
-DCMAKE_LINKER_TYPE=MOLD \
-DENABLE_UNIT_TESTS=ON \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_CXX_FLAGS="-std=c++23 -g -fno-omit-frame-pointer" \
&& cmake --build . -j `nproc`

for test in $(find ./ -type f -name '*_tests' -executable); do
  echo "Running $test"
  gdb -ex='set confirm off' -ex='run' -ex='bt' -ex='quit' "$test"

done
