#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

conan build . \
    -c tools.system.package_manager:mode=install \
    -c tools.cmake.cmaketoolchain:generator=Ninja \
    -c tools.build:compiler_executables='{"c": "clang", "cpp": "clang++"}' \
    -s build_type=Release \
    -s compiler=clang \
    -s compiler.version=20 \
    -s compiler.libcxx=libc++ \
    -o use_mold=True \
    -o enable_llvm_coverage=True \
    --build=missing

mkdir -p ./build/coverage/ 
for test in $(find ./build -type f -name '*_tests' -executable); do
    export LLVM_PROFILE_FILE="./build/coverage/$(basename "$(dirname "$test")").profraw";
    echo ${LLVM_PROFILE_FILE} >> ./build/coverage/list;
    "$test"
done

llvm-profdata merge --input-files './build/coverage/list' -o "./build/coverage/merged.profdata" 
find ./modules -type f -name "*.profraw" -exec rm -fv {} +
LLVM_COV_SHOW=$(llvm-cov show \
        -instr-profile='./build/coverage/merged.profdata' \
        $(find ./build -type f -name '*_tests' -executable -exec printf -- '-object %s ' {} \;) \
        $(find ./build -type f -name '*\.a' -exec printf -- '-object %s ' {} \;) \
        -ignore-filename-regex="*.test.cpp|./external*"
)

echo "${LLVM_COV_SHOW}" > './build/coverage/coverage.txt'
wget -qO- "https://codecov.io/bash" | bash
