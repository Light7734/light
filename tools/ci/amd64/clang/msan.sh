#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

source '/1.4.328.1/setup-env.sh'

CC=$(which clang)
export CC

CXX=$(which clang++)
export CXX

DISPLAY=:99
export DISPLAY

PKG_CONFIG_PATH="/msan/lib/pkgconfig:${PKG_CONFIG_PATH}"
export PKG_CONFIG_PATH

VK_ICD_FILENAMES='/usr/share/vulkan/icd.d/lvp_icd.x86_64.json'
export VK_ICD_FILENAMES

Xvfb :99 -screen 0 1024x768x16 &

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D ENABLE_UNIT_TESTS=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS=" \
-fsanitize=memory \
-fsanitize-memory-track-origins \
-g \
-fno-omit-frame-pointer \
-std=c++23 \
-nostdinc++ \
-isystem /libcxx_msan/include/c++/v1/" \
    -D CMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=memory \
-fsanitize-memory-track-origins \
-g \
-std=c++23 \
-L/msan/lib -Wl,-rpath,/msan/lib \
-L/libcxx_msan/lib -Wl,-rpath,/libcxx_msan/lib \
-lc++ \
-lc++abi"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    "$test"
done < <(find ./build -type f -name '*_tests' -executable -print0)
