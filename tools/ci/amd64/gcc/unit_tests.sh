#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build && mkdir build/ && cd build

Xvfb :99 -screen 0 1024x768x16 &
export CXX=$(which g++)
export CC=$(which gcc)
export DISPLAY=:99

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
  gdb --return-child-result -q -ex='set confirm off' -ex='set pagination off' -ex='run' -ex='bt full' -ex='quit' "$test"
done
