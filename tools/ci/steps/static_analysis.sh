#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

conan build . \
-c tools.system.package_manager:mode=install \
-c tools.cmake.cmaketoolchain:generator=Ninja \
-s build_type=Release \
-o enable_static_analysis=True \
-o enable_tests=True \
-o use_mold=True \
--build=missing
