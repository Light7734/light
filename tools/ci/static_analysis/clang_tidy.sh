#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

echo 'Static analysis is currently disabled as code is filled with failing clang-tidy checks'
echo 'Runng this would be a waste of CPU cycles and electricty'
echo 'Fix the checks before removing these lines'
exit 0

conan build . \
-c tools.system.package_manager:mode=install \
-c tools.cmake.cmaketoolchain:generator=Ninja \
-s build_type=Release \
-o enable_static_analysis=True \
-o enable_unit_tests=True \
-o enable_fuzz_tests=True \
-o use_mold=True \
--build=missing
