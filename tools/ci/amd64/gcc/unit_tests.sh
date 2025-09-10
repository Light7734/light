#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

Xvfb :99 -screen 0 1024x768x16 &
export DISPLAY=:99
export CXX=$(which g++)
export CC=$(which gcc)

conan build . \
    -c tools.system.package_manager:mode=install \
    -c tools.cmake.cmaketoolchain:generator=Ninja \
    -c tools.build:compiler_executables='{"c": "gcc", "cpp": "g++"}' \
    -s build_type=Release \
    -s compiler=gcc \
    -s compiler.version=15 \
    -s compiler.libcxx=libstdc++ \
    -o use_mold=True \
    -o enable_unit_tests=True \
    -o enable_fuzz_tests=False \
    -o enable_llvm_coverage=False \
    -o enable_static_analysis=False \
    -o use_mold=True \
    -o export_compile_commands=False \
    --build=missing

for test in $(find ./build -type f -name '*_tests' -executable); do
  echo "Running $test"
  "$test"
done
