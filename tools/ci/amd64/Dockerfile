FROM archlinux:latest

## Packages ##
RUN \
sed -i 's/^#ParallelDownloads = .*/ParallelDownloads = 8/' /etc/pacman.conf \
&& echo 'NoExtract = usr/share/{man,doc,info}/*' >> /etc/pacman.conf \
&& pacman -Syyu --noconfirm --disable-download-timeout \
afl++ \
afl-utils \
base-devel \
bash \
clang \
cmake \
curl \
gcc \
gdb \
git \
libc++ \
libinput \
libunwind \
libx11 \
libxcursor \
libxi \
libxinerama \
libxrandr \
mesa \
mold \
ninja \
valgrind \
wget \
xcb-util-cursor \
xorg-server-xvfb \
xorg-util-macros \
xtrans \
zlib \
&& pacman -Scc --noconfirm

## Sanitizers ##
RUN \
git clone --depth=1 https://github.com/llvm/llvm-project.git -b llvmorg-20.1.8 \
&& mkdir llvm-project/build-lsan llvm-project/build-msan \
\
&& cd llvm-project/build-lsan \
&& cmake -G Ninja \
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
&& ninja install-cxx install-cxxabi \
\
&& cd ../build-msan \
&& cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_LINKER_TYPE="MOLD" \
  -DCMAKE_INSTALL_PREFIX=/libcxx_msan \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi" \
  -DLLVM_ENABLE_PIC=ON \
  -DLIBCXX_INSTALL_MODULES=ON \
  -DLIBCXXABI_USE_LLVM_UNWINDER=OFF \
  -DLLVM_USE_SANITIZER=MemoryWithOrigins \
  ../runtimes \
&& ninja cxx cxxabi \
&& ninja install-cxx install-cxxabi \
\
&& cd ../.. \
&& rm -rf llvm-project
