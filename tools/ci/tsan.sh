#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
rm -rf ./build/

XDG_RUNTIME_DIR='/run/user/1000'
export XDG_RUNTIME_DIR

TSAN_OPTIONS="symbolize=1:stack_trace_format=v:halt_on_error=true:print_full_thread_history=true:verbosity=1"
export TSAN_OPTIONS

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D CMAKE_C_COMPILER="$(which clang)" \
    -D CMAKE_CXX_COMPILER="$(which clang++)" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_UNIT_TESTS=ON \
    -D ENABLE_TSAN=ON \
    -D CMAKE_BUILD_TYPE=Debug \
    -D CMAKE_CXX_FLAGS=" \
-fsanitize=thread \
-fno-optimize-sibling-calls \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-g \
-O0 \
-std=c++26 \
-nostdinc++ \
-isystem /usr/local/lib/libcxx_tsan/include/c++/v1/" \
    -D CMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=thread \
-fno-optimize-sibling-calls \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-g \
-O0 \
-lc++ \
-lc++abi \
-std=c++26 \
-L/usr/local/lib/libcxx_tsan/lib \
-Wl,-rpath,/usr/local/lib/libcxx_tsan/lib"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    "$test"
done < <(find ./build -type f -name '*_tests' -executable -print0)
