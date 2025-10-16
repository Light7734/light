#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

CC=$(which clang)
export CC

CXX=$(which clang++)
export CXX

DISPLAY=:99
export DISPLAY

LSAN_OPTIONS="suppressions=$(git rev-parse --show-toplevel)/tools/ci/amd64/clang/lsan.supp:fast_unwind_on_malloc=0:verbosity=1:report_objects=1"
export LSAN_OPTIONS

LSAN_SYMBOLIZER_PATH="$(which llvm-symbolizer)"
export LSAN_SYMBOLIZER_PATH

Xvfb :99 -screen 0 1024x768x16 &

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D ENABLE_UNIT_TESTS=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS=" \
-fsanitize=leak \
-fno-common \
-g \
-fno-omit-frame-pointer \
-std=c++23 \
-nostdinc++ \
-isystem /libcxx_lsan/include/c++/v1/" \
    -D CMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=leak \
-L/libcxx_lsan/lib \
-lc++ \
-lc++abi \
-Wl,-rpath,/libcxx_lsan/lib"

cmake --build ./build --target='renderer_tests' -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    "$test"
done < <(find ./build -type f -name '*_tests' -executable -print0)
