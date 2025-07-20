#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

conan build . \
    -c tools.system.package_manager:mode=install \
    -c tools.cmake.cmaketoolchain:generator=Ninja \
    -c tools.build:cxxflags='["-fprofile-instr-generate", "-fcoverage-mapping"]' \
    -c tools.build:sharedlinkflags='["-fprofile-instr-generate", "-fcoverage-mapping"]' \
    -c tools.build:exelinkflags='["-fprofile-instr-generate", "-fcoverage-mapping"]' \
    -c tools.info.package_id:confs='["tools.build:cxxflags","tools.build:sharedlinkflags","tools.build:exelinkflags"]' \
    -c tools.build:compiler_executables='{"c": "clang", "cpp": "clang++"}' \
    -s build_type=Release \
    -s compiler=clang \
    -s compiler.version=20 \
    -s compiler.libcxx=libc++ \
    -o use_mold=True \
    --build=missing

for test in $(find ./build -type f -name '*_tests' -executable); do
  echo "Running $test"
  "$test"
done

