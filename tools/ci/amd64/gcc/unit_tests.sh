#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

CC=$(which gcc)
export CC

CXX=$(which g++)
export CXX

DISPLAY=:99
export DISPLAY

Xvfb :99 -screen 0 1024x768x16 &

# gcc uses libstdc++ by default
cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D ENABLE_UNIT_TESTS=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS="-std=c++26 -g -fno-omit-frame-pointer"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    gdb \
        --return-child-result \
        -ex='set confirm off' \
        -ex='set pagination off' \
        -ex='run' \
        -ex='bt full' \
        -ex='quit' \
        -q \
        "$test"

done < <(find ./build -type f -name '*_tests' -executable -print0)
