#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

# shellcheck disable=SC1091
source "${PATH_TO_VULKAN_SDK}/setup-env.sh"

PKG_CONFIG_PATH="/msan/lib/pkgconfig:${PKG_CONFIG_PATH}"
export PKG_CONFIG_PATH

VK_ICD_FILENAMES='/usr/share/vulkan/icd.d/lvp_icd.x86_64.json'
export VK_ICD_FILENAMES

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
-fsanitize=memory \
-fsanitize-memory-track-origins \
-g \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-std=c++26 \
-nostdinc++ \
-isystem /libcxx_msan/include/c++/v1/" \
    -D CMAKE_EXE_LINKER_FLAGS=" \
-fsanitize=memory \
-fsanitize-memory-track-origins \
-g \
-fno-omit-frame-pointer \
-fno-inline-functions \
-fno-common \
-std=c++26 \
-L/msan/lib -Wl,-rpath,/msan/lib \
-L/libcxx_msan/lib -Wl,-rpath,/libcxx_msan/lib \
-lc++ \
-lc++abi"

cmake --build ./build -j"$(nproc)"

while IFS= read -r -d '' test; do
    echo "Running $test"
    "$test"
done < <(find ./build -type f -name '*_tests' -executable -print0)
