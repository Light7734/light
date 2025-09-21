#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build
mkdir -p ./build/coverage/ && cd build

Xvfb :99 -screen 0 1024x768x16 &
export DISPLAY=:99
export CXX=$(which clang++)
export CC=$(which clang)

cmake .. \
-G Ninja \
-DCMAKE_LINKER_TYPE=MOLD \
-DENABLE_UNIT_TESTS=ON \
-DENABLE_LLVM_COVERAGE=ON \
-DCMAKE_BUILD_TYPE=Release
&& cmake --build . -j`nproc`

for test in $(find ./build -type f -name '*_tests' -executable); do
    export LLVM_PROFILE_FILE="./build/coverage/$(basename "$(dirname "$test")").profraw";
    echo ${LLVM_PROFILE_FILE} >> ./build/coverage/list;
    "$test"
done

llvm-profdata merge --input-files './build/coverage/list' -o "./build/coverage/merged.profdata" 
find ./modules -type f -name "*.profraw" -exec rm -fv {} +

# fix for imgui code is temporary
# we will remove imgui as dependency in future versions
LLVM_COV_SHOW=$(llvm-cov show \
        -instr-profile='./build/coverage/merged.profdata' \
        $(find ./build -type f -name '*_tests' -executable -exec printf -- '-object %s ' {} \;) \
        $(find ./build -type f -name '*\.a' -exec printf -- '-object %s ' {} \;) \
        -ignore-filename-regex='\.test\.cpp$' \
        -ignore-filename-regex='./external/' \
)

echo "${LLVM_COV_SHOW}" > './build/coverage/coverage.txt'
wget -qO- "https://codecov.io/bash" | bash
