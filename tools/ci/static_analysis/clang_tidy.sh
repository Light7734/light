#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build && mkdir build/ && cd build

export CC=$(which clang)

export CXX=$(which clang++)

cmake .. \
    -G Ninja \
    -DCMAKE_LINKER_TYPE=MOLD \
    -DENABLE_UNIT_TESTS=ON \
    -DENABLE_STATIC_ANALYSIS=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-std=c++23 -stdlib=libc++" &&
    cmake --build . -j $(nproc)
