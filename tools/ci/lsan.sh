#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

XDG_RUNTIME_DIR='/run/user/1000'
export XDG_RUNTIME_DIR

LSAN_OPTIONS="suppressions=$(git rev-parse --show-toplevel)/tools/ci/lsan.supp:fast_unwind_on_malloc=0:verbosity=1:report_objects=1"
export LSAN_OPTIONS

LSAN_SYMBOLIZER_PATH="$(which llvm-symbolizer)"
export LSAN_SYMBOLIZER_PATH

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D CMAKE_C_COMPILER="$(which clang)" \
    -D CMAKE_CXX_COMPILER="$(which clang++)" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_UNIT_TESTS=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS=" \
-fsanitize=leak \
-g \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-std=c++26 \
-nostdinc++ \
-isystem /usr/local/lib/libcxx_lsan/include/c++/v1/" \
    -D CMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=leak \
-g \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-std=c++26 \
-L/usr/local/lib/libcxx_lsan/lib \
-lc++ \
-lc++abi \
-Wl,-rpath,/usr/local/lib/libcxx_lsan/lib"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    "$test"
done < <(find ./build -type f -name '*_tests' -executable -print0)
