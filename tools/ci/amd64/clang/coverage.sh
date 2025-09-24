#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build
mkdir build/ && cd build

Xvfb :99 -screen 0 1024x768x16 &
export CXX=$(which clang++)
export CC=$(which clang)
export DISPLAY=:99

cmake .. \
-G Ninja \
-DCMAKE_LINKER_TYPE=MOLD \
-DENABLE_UNIT_TESTS=ON \
-DENABLE_LLVM_COVERAGE=ON \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_CXX_FLAGS="-std=c++23 -stdlib=libc++ -g -fno-omit-frame-pointer" \
&& cmake --build . -j `nproc`

mkdir -p ./coverage/ 
for test in $(find ./ -type f -name '*_tests' -executable); do
    export LLVM_PROFILE_FILE="./coverage/$(basename "$(dirname "$test")").profraw";
    echo ${LLVM_PROFILE_FILE} >> ./coverage/list;

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

llvm-profdata merge --input-files './coverage/list' -o "./coverage/merged.profdata" 
find ./modules -type f -name "*.profraw" -exec rm -fv {} +

LLVM_COV_SHOW=$(llvm-cov show \
        -instr-profile='./coverage/merged.profdata' \
        $(find ./ -type f -name '*_tests' -executable -exec printf -- '-object %s ' {} \;) \
        $(find ./ -type f -name '*\.a' -exec printf -- '-object %s ' {} \;) \
        -ignore-filename-regex='\.test\.cpp$' \
        -ignore-filename-regex='\.fuzz\.cpp$'
)

echo "${LLVM_COV_SHOW}" > './coverage/coverage.txt'
wget -qO- "https://codecov.io/bash" | bash
