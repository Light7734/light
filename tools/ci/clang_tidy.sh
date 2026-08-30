#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
rm -rf ./build/

# We need the `-Wno-reserved-module-identifier` because clang generates a warning when doing the std module...
# TODO(Light): resolve warning from std module somehow and remove `-Wno-reserved-module-identifier`
cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D CMAKE_C_COMPILER="$(which clang)" \
    -D CMAKE_CXX_COMPILER="$(which clang++)" \
    -D CMAKE_CXX_FLAGS="-std=c++26 -stdlib=libc++ -Werror -Wno-reserved-module-identifier" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_UNIT_TESTS=ON \
    -D ENABLE_STATIC_ANALYSIS=ON \
    -D CMAKE_BUILD_TYPE=Release

cmake --build ./build -j"$(nproc)"
