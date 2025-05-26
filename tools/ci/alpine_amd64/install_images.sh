#!/bin/bash

ALPINE_AMD64=$(git rev-parse --show-toplevel)/tools/ci/alpine_amd64/

cd ${ALPINE_AMD64}/clang_format/
docker build -t alpine_amd64__clang_format
