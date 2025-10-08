#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build && mkdir build/

Xvfb :99 -screen 0 1024x768x16 &
export CXX=$(which clang++)
export CC=$(which clang)
export DISPLAY=:99

cmake . \
-Bbuild \
-GNinja \
-DCMAKE_LINKER_TYPE=MOLD \
-DENABLE_UNIT_TESTS=ON \
-DENABLE_LLVM_COVERAGE=ON \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_CXX_FLAGS="-std=c++23 -stdlib=libc++ -g -fno-omit-frame-pointer" \
&& cmake --build ./build -j `nproc`

mkdir -p ./build/coverage/ 
for test in $(find ./build -type f -name '*_tests' -executable); do
    export LLVM_PROFILE_FILE="./build/coverage/$(basename "$(dirname "$test")").profraw";
    echo ${LLVM_PROFILE_FILE} >> ./build/coverage/list;

    gdb \
    --return-child-result \
    -ex='set confirm off' \
    -ex='set pagination off' \
    -ex='run' \
    -ex='bt full' \
    -ex='quit' \
    -q \
    "$test"
done

llvm-profdata merge --input-files './build/coverage/list' -o "./coverage/merged.profdata" 
find ./build/modules -type f -name "*.profraw" -exec rm -fv {} +

LLVM_COV_SHOW=$(llvm-cov show \
        -instr-profile='./build/coverage/merged.profdata' \
        $(find ./build -type f -name '*_tests' -executable -exec printf -- '-object %s ' {} \;) \
        $(find ./build -type f -name '*\.a' -exec printf -- '-object %s ' {} \;) \
        -ignore-filename-regex='\.test\.cpp$' \
        -ignore-filename-regex='\.fuzz\.cpp$'
)

echo "${LLVM_COV_SHOW}" > './build/coverage/coverage.txt'
cd ./build/coverage/ && wget -qO- "https://codecov.io/bash" | bash
