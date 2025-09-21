#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build
mkdir build/ && cd build

Xvfb :99 -screen 0 1024x768x16 &
export CXX=$(which clang++)
export CC=$(which clang)
export DISPLAY=:99

cmake .. \
-G Ninja \
-DCMAKE_LINKER_TYPE=MOLD \
-DENABLE_UNIT_TESTS=ON \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_CXX_FLAGS=" \
-fsanitize=leak \
-g \
-fno-omit-frame-pointer \
-std=c++23 \
-nostdinc++ \
-isystem /libcxx_lsan/include/c++/v1/" \
-DCMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=leak \
-L/libcxx_lsan/lib \
-lc++ \
-lc++abi \
-Wl,-rpath,/libcxx_lsan/lib" \
&& cmake --build . -j`nproc`

for test in $(find ./build -type f -name '*_tests' -executable); do
  echo "Running $test"
  "$test"
done
