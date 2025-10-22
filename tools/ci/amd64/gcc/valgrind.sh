#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

CC=$(which gcc)
export CC

CXX=$(which g++)
export CXX

DISPLAY=:99
export DISPLAY

DEBUGINFOD_URLS="https://debuginfod.archlinux.org/"
export DEBUGINFOD_URLS

Xvfb :99 -screen 0 1024x768x16 &

# gcc uses libstdc++ by default
cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D ENABLE_UNIT_TESTS=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS="-std=c++26 -fno-omit-frame-pointer -fno-common -g"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"

    valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --num-callers=50 \
        --gen-suppressions=all \
        --suppressions='./tools/ci/amd64/gcc/valgrind.supp' \
        --error-exitcode=255 "${test}" || exit 1

done < <(find ./build -type f -name '*_tests' -executable -print0)
