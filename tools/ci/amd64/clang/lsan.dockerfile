FROM archlinux:base-devel

RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
    bash \
    base-devel \
    clang \
    llvm \
    cmake \
    git \
    python \
    python-pip \
    mesa \
    mold \
    ninja \
    zlib \
    libc++ \
    libinput \
    libunwind \
    xorg-server-xvfb \
    libx11 \
    libxrandr \
    libxinerama \
    libxcursor \
    libxi

RUN pip install --no-cache-dir --break-system-packages conan gitpython \
    && conan profile detect

RUN clang --version  \
    && conan --version \
    && pip --version \
    && cmake --version \
    && g++ --version \
    && clang --version \
    && ninja --version \
    && mold --version

RUN git clone --depth=1 https://github.com/llvm/llvm-project.git -b llvmorg-20.1.8  \
    && cd llvm-project/  \
    && mkdir build/ \
    && cd build/ \
    && cmake \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_LINKER_TYPE="MOLD" \
    -DCMAKE_INSTALL_PREFIX=/libcxx_lsan \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi" \
    -DLLVM_ENABLE_PIC=ON \
    -DLIBCXX_INSTALL_MODULES=ON \
    -DLIBCXXABI_USE_LLVM_UNWINDER=OFF \
    -DLLVM_USE_SANITIZER=Leaks \
    ../runtimes \
    && ninja cxx cxxabi \
    && ninja -C . install-cxx install-cxxabi \
    && rm -r /llvm-project/

RUN git clone 'https://git.light7734.com/light7734/light.git' \
    && cd light \
    && conan install . \
        -c tools.system.package_manager:mode=install \
        -c tools.cmake.cmaketoolchain:generator=Ninja \
        -c tools.build:cxxflags='["-g", "-fno-omit-frame-pointer", "-nostdinc++", "-isystem", "/libcxx_lsan/include/c++/v1/", "-fsanitize=leak"]' \
        -c tools.build:sharedlinkflags='["-L/libcxx_lsan/lib", "-Wl,-rpath,/libcxx_lsan/lib", "-lc++", "-lc++abi", "-fsanitize=leak"]' \
        -c tools.build:exelinkflags='["-L/libcxx_lsan/lib", "-Wl,-rpath,/libcxx_lsan/lib", "-lc++", "-lc++abi", "-fsanitize=leak"]' \
        -c tools.info.package_id:confs='["tools.build:cxxflags","tools.build:sharedlinkflags","tools.build:exelinkflags"]' \
        -c tools.build:compiler_executables='{"c": "clang", "cpp": "clang++"}' \
        -s build_type=Release \
        -s compiler=clang \
        -s compiler.version=20 \
        -s compiler.libcxx=libc++ \
        -o use_mold=True \
        --build=missing
