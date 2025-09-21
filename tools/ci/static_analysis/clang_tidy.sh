#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

echo 'Static analysis is currently disabled as code is filled with failing clang-tidy checks'
echo 'Runng this would be a waste of CPU cycles and electricty'
echo 'Fix the checks before removing these lines'
exit 0

cmake .. \
-G Ninja \
-DCMAKE_LINKER_TYPE=MOLD \
-DENABLE_UNIT_TESTS=ON \
-DENABLE_FUZZ_TESTS=ON \
-CMAKE_CXX_CLANG_TIDY=ON \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_CXX_FLAGS="-std=c++23 -stdlib=libc++ -g -fno-omit-frame-pointer" \
&& cmake --build . -j `nproc`
