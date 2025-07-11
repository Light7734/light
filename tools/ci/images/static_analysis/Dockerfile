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
    py3-pip


RUN pip install --no-cache-dir --break-system-packages conan gitpython

RUN clang --version  \
    && conan --version \
    && pip --version \
    && cmake --version

RUN git clone 'https://git.light7734.com/light7734/light.git' --recursive \
    && cd light \
    && conan install . -o enable_static_analysis=True --build=missing
