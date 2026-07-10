#!/bin/bash


set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
rm -rf ./build/

export GNOME_SETUP_DISPLAY='unix:/tmp/.X11-unix/X1'
export DISPLAY=':0'

WAYLAND_DISPLAY='wayland-0'
export WAYLAND_DISPLAY

XDG_RUNTIME_DIR='/run/user/1000'
export XDG_RUNTIME_DIR

DEBUGINFOD_URLS="https://debuginfod.archlinux.org/"
export DEBUGINFOD_URLS

DEBUGINFOD_CACHE_PATH="/home/light/.cache/debuginfod_client/"
export DEBUGINFOD_CACHE_PATH

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D CMAKE_C_COMPILER="$(which clang)" \
    -D CMAKE_CXX_COMPILER="$(which clang++)" \
    -D CMAKE_CXX_FLAGS="-std=c++26 -stdlib=libc++ -fno-omit-frame-pointer -fno-inline-functions -fno-common -g" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_UNIT_TESTS=ON \
    -D CMAKE_BUILD_TYPE=Release

cmake --build ./build -j"$(nproc)"

counter=0
while IFS= read -r -d '' test; do
    echo "Running $test"

    counter=$((counter + 1))

    valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --num-callers=50 \
        --gen-suppressions=all \
        --log-file="val_$counter" \
        --suppressions='./tools/ci/valgrind.supp' \
        --error-exitcode=255 "${test}" || exit 1

done < <(find ./build -type f -name '*_tests' -executable -print0)
