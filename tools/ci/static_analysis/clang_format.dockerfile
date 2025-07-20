FROM alpine:latest

RUN apk add --no-cache \
    bash \
    curl \
    findutils \
    git \
    libc6-compat \
    clang-extra-tools 
