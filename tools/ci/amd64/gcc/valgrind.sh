#!/bin/bash

export DEBUGINFOD_URLS="https://debuginfod.archlinux.org/"

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build && mkdir build/

Xvfb :99 -screen 0 1024x768x16 &
export CXX=$(which g++)
export CC=$(which gcc)
export DISPLAY=:99

# gcc uses libstdc++ by default
cmake . \
-Bbuild \
-GNinja \
-DCMAKE_LINKER_TYPE=MOLD \
-DENABLE_UNIT_TESTS=ON \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_CXX_FLAGS="-std=c++23 -g -fno-omit-frame-pointer" \
&& cmake --build ./build -j `nproc`

for test in $(find ./build -type f -name '*_tests' -executable); do
    echo "Running $test"
    valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --verbose \
    --num-callers=50 \
    --gen-suppressions=all \
    --suppressions='./tools/ci/amd64/gcc/valgrind.supp' \
    --error-exitcode=255 ${test} || exit 1
done
