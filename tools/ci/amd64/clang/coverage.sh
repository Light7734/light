#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

Xvfb :99 -screen 0 1024x768x16 &
export DISPLAY=:99

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

# fix for imgui code is temporary
# we will remove imgui as dependency in future versions
LLVM_COV_SHOW=$(llvm-cov show \
        -instr-profile='./build/coverage/merged.profdata' \
        $(find ./build -type f -name '*_tests' -executable -exec printf -- '-object %s ' {} \;) \
        $(find ./build -type f -name '*\.a' -exec printf -- '-object %s ' {} \;) \
        -ignore-filename-regex='\.test\.cpp$' \
        -ignore-filename-regex='./external/' \
        -ignore-filename-regex='gl\/backend.cpp$' \
        -ignore-filename-regex='gl\/backend.hpp$' \
        -ignore-filename-regex='gl\/loader.hpp$' \
        -ignore-filename-regex='glfw\/glfw.h$' \
        -ignore-filename-regex='glfw\/glfw.cpp$'
)

echo "${LLVM_COV_SHOW}" > './build/coverage/coverage.txt'
wget -qO- "https://codecov.io/bash" | bash
