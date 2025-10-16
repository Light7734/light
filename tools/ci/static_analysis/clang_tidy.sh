#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

CC=$(which clang)
export CC

CXX=$(which clang++)
export CXX

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D ENABLE_UNIT_TESTS=ON \
    -D ENABLE_STATIC_ANALYSIS=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS="-std=c++23 -stdlib=libc++"

cmake --build . -j"$(nproc)"
