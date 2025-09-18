FROM alpine:latest

RUN apk add --no-cache \
    bash \
    clang \
    llvm \
    cmake \
    git \
    make \
    g++ \
    python3 \
    py3-pip \
    mesa-dev \
    mesa-gl \
    pkgconf \
    clang-extra-tools \
    mold \
    ninja \
    doxygen \
    openssh

RUN pip install --no-cache-dir --break-system-packages \
    conan \
    gitpython \
    Sphinx \
    sphinx_rtd_theme \
    && conan profile detect
