#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

conan build . \
  -c tools.system.package_manager:mode=install \
  -c tools.cmake.cmaketoolchain:generator=Ninja \
  -s build_type=Release \
  -o enable_unit_tests=True \
  -o use_mold=True \
  --build=missing

for test in $(find ./build -type f -name '*_tests' -executable); do
  echo "Running $test"
  "$test"
done
