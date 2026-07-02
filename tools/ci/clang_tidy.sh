#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
rm -rf ./build/

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D CMAKE_C_COMPILER="$(which clang)" \
    -D CMAKE_CXX_COMPILER="$(which clang++)" \
    -D CMAKE_CXX_FLAGS="-std=c++26 -stdlib=libc++" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_UNIT_TESTS=ON \
    -D ENABLE_STATIC_ANALYSIS=ON \
    -D CMAKE_BUILD_TYPE=Release

cmake --build ./build -j"$(nproc)"
