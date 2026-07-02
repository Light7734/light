#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
rm -rf ./build/

XDG_RUNTIME_DIR='/run/user/1000'
export XDG_RUNTIME_DIR

UBSAN_OPTIONS="print_stacktrace=1:verbosity=1"
export UBSAN_OPTIONS

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D CMAKE_C_COMPILER="$(which clang)" \
    -D CMAKE_CXX_COMPILER="$(which clang++)" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_UNIT_TESTS=ON \
    -D ENABLE_UBSAN=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS=" \
-fsanitize=undefined \
-fno-sanitize-recover=all \
-fno-optimize-sibling-calls \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-sanitize-merge \
-fno-common \
-g \
-std=c++26 \
-nostdinc++ \
-isystem /usr/local/lib/libcxx_ubsan/include/c++/v1/" \
    -D CMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=undefined \
-fno-sanitize-recover=all \
-fno-optimize-sibling-calls \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-sanitize-merge \
-fno-common \
-g \
-lc++ \
-lc++abi \
-std=c++26 \
-L/usr/local/lib/libcxx_ubsan/lib \
-Wl,-rpath,/usr/local/lib/libcxx_ubsan/lib"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    "$test"
done < <(find ./build -type f -name '*_tests' -executable -print0)
