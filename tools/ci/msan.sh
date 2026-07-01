#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
rm -rf ./build/

MSAN_OPTIONS="verbosity=1"
export MSAN_OPTIONS

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D CMAKE_C_COMPILER="$(which clang)" \
    -D CMAKE_CXX_COMPILER="$(which clang++)" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_UNIT_TESTS=ON \
    -D ENABLE_MSAN=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS=" \
-fsanitize=memory \
-fsanitize-memory-track-origins \
-g \
-fno-optimize-sibling-calls \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-std=c++26 \
-nostdinc++ \
-isystem /usr/local/lib/libcxx_msan/include/c++/v1/" \
    -D CMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=memory \
-fsanitize-memory-track-origins \
-g \
-fno-optimize-sibling-calls \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-std=c++26 \
-L/usr/local/lib/libcxx_msan/lib -Wl,-rpath,/usr/local/lib/libcxx_msan/lib \
-lc++ \
-lc++abi"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    "$test"
done < <(find ./build -type f -name '*_tests' -executable -print0)
