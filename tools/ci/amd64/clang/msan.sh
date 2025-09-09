#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

Xvfb :99 -screen 0 1024x768x16 &
export DISPLAY=:99

conan build . \
    -c tools.system.package_manager:mode=install \
    -c tools.cmake.cmaketoolchain:generator=Ninja \
    -c tools.build:cxxflags='["-g", "-fno-omit-frame-pointer", "-nostdinc++", "-isystem", "/libcxx_msan/include/c++/v1/", "-fsanitize=memory", "-fsanitize-memory-track-origins"]' \
    -c tools.build:sharedlinkflags='["-L/libcxx_msan/lib", "-Wl,-rpath,/libcxx_msan/lib", "-lc++", "-lc++abi", "-fsanitize=memory", "-fsanitize-memory-track-origins"]' \
    -c tools.build:exelinkflags='["-L/libcxx_msan/lib", "-Wl,-rpath,/libcxx_msan/lib", "-lc++", "-lc++abi", "-fsanitize=memory", "-fsanitize-memory-track-origins"]' \
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
