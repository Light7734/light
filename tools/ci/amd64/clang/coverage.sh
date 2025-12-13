#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

CC=$(which clang)
export CC

CXX=$(which clang++)
export CXX

DISPLAY=:99
export DISPLAY

Xvfb :99 -screen 0 1024x768x16 &

cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_LINKER_TYPE=MOLD \
    -D ENABLE_UNIT_TESTS=ON \
    -D ENABLE_LLVM_COVERAGE=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_CXX_FLAGS="-std=c++23 -stdlib=libc++ -g -fno-omit-frame-pointer"

cmake --build ./build -j"$(nproc)"

mkdir -p ./build/coverage/
while IFS= read -r -d '' test; do
    LLVM_PROFILE_FILE="./build/coverage/$(basename "$(dirname "$test")").profraw"
    export LLVM_PROFILE_FILE

    echo "${LLVM_PROFILE_FILE}" >>./build/coverage/list
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

llvm-profdata merge --input-files './build/coverage/list' -o "./build/coverage/merged.profdata"
find ./build/modules -type f -name "*.profraw" -exec rm -fv {} +

LLVM_COV_SHOW=$(
    llvm-cov show \
        -instr-profile='./build/coverage/merged.profdata' \
        "$(find ./build -type f -name '*_tests' -executable -exec printf -- '--object=%s ' {} \;)" \
        "$(find ./build -type f -name '*\.a' -exec printf -- '--object=%s ' {} \;)" \
        -ignore-filename-regex='\.test\.cpp$' \
        -ignore-filename-regex='\.fuzz\.cpp$'
)

echo "${LLVM_COV_SHOW}" >'./build/coverage/coverage.txt'
cd ./build/coverage/ && wget -qO- "https://codecov.io/bash" | bash
