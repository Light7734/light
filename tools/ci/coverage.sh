#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

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
    -D ENABLE_LLVM_COVERAGE=ON \
    -D CMAKE_BUILD_TYPE=Release

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

# if we wrap the find commands in double-quotes,
# they'll be treated as 1 object,
# we DO need word splitting in that case...
#
# shellcheck disable=SC2046
LLVM_COV_SHOW=$(
    llvm-cov show \
        -instr-profile='./build/coverage/merged.profdata' \
        $(find ./build -type f -name '*_tests' -executable -exec printf -- '--object=%s ' {} \;) \
        $(find ./build -type f -name '*\.a' -exec printf -- '--object=%s ' {} \;) \
        -ignore-filename-regex='\.test\.cpp$' \
        -ignore-filename-regex='\.fuzz\.cpp$'
)

echo "${LLVM_COV_SHOW}" >'./build/coverage/coverage.txt'
cd ./build/coverage/ && wget -qO- "https://codecov.io/bash" | bash
