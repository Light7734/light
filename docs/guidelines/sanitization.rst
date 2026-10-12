How to Sanitize
--------------------------------
**Sanitization** is a way of detecting bugs via a compiler injecting instrumentation code into the runtime.

Light engine uses **four** types of sanitizers, the following description of each sanitizer is taken from the clang's own official documentation:

Address Sanitizer
""""""""""""""""""""""""""
ASan is a fast memory error detector. It consists of a compiler instrumentation module and a run-time library. The tool can detect the following types of bugs:

- Out-of-bounds accesses to heap, stack and globals
- Use-after-free
- Use-after-return (clang flag :code:`-fsanitize-address-use-after-return=(never|runtime|always)` default: :code:`runtime`)
    - Enable with: :code:`ASAN_OPTIONS=detect_stack_use_after_return=1` (already enabled on Linux).
    - Disable with: :code:`ASAN_OPTIONS=detect_stack_use_after_return=0`.
- Use-after-scope (clang flag :code:`-fsanitize-address-use-after-scope`)
- Double-free, invalid free
- Memory leaks (experimental)

Typical slowdown introduced by AddressSanitizer is 2x.

Memory Sanitizer
""""""""""""""""""""""""""
MSan is a detector of uninitialized memory use. It consists of a compiler instrumentation module and a run-time library.

Here is a not comprehensive of list cases when MemorySanitizer will report an error:

- Uninitialized value was used in a conditional branch.
- Uninitialized pointer was used for memory accesses.
- Uninitialized value was passed or returned from a function call, which is considered an undefined behavior. The check can be disabled with :code:`-fno-sanitize-memory-param-retval`.
- Uninitialized data was passed into some libc calls.

Typical slowdown introduced by MemorySanitizer is 3x.

Thread Sanitizer
""""""""""""""""""""""""""
TSan is a tool that detects data races. It consists of a compiler instrumentation module and a run-time library. 

Typical slowdown introduced by ThreadSanitizer is about 5x-15x.

Typical memory overhead introduced by ThreadSanitizer is about 5x-10x.

Undefined Behavior Sanitizer
""""""""""""""""""""""""""""""""""""""""""""""""""""
UBSan is a fast undefined behavior detector. UBSan modifies the program at compile-time to catch various kinds of undefined behavior during program execution, for example:

- Array subscript out of bounds, where the bounds can be statically determined
- Bitwise shifts that are out of bounds for their data type
- Dereferencing misaligned or null pointers
- Signed integer overflow
- Conversion to, from, or between floating-point types which would overflow the destination

See the full list of available checks below.

UBSan has an optional run-time library which provides better error reporting.

The checks have small runtime cost and no impact on address space layout or ABI.

Sanitizing
""""""""""""""""""""""""""""""""
First, clone the llvm project with the same tag as your :code:`clang --version`, so in case of version :code:`23.1.1`, do:

.. code:: bash
 
    git clone https://github.com/llvm/llvm-project --depth=1 --branch='llvmorg-23.1.1' 'llvm-23.1.1' 
    cd llvm-23.1.1`

Then generate a cmake project for the specific type of sanitizer you want.
You could set the :code:`CMAKE_INSTALL_PREFIX` to a directory inside :code:`/usr/local/lib/`, eg. :code:`/usr/local/lib/libcxx_lsan/`, or any other directory you want.
As long as you link properly against it when building for sanitization with the following flags, for example for leak sanitizer:

.. code:: bash

    # Generate build files for compiling the C++ standard library with sanitization support
    cmake \
        -S ./runtimes \
        -B ./build-lsan \
        -G Ninja \
        -D CMAKE_LINKER_TYPE="MOLD" \
        -D CMAKE_BUILD_TYPE=Release \
        -D CMAKE_INSTALL_PREFIX="/PATH_TO_LIBCXX_LSAN_INSTALL_PREFIX/" \
        -D CMAKE_C_COMPILER=$(which clang) \
        -D CMAKE_CXX_COMPILER=$(which clang++) \
        -D LLVM_ENABLE_PROJECTS="clang;compiler-rt" \
        -D LLVM_ENABLE_RUNTIMES="libcxx;libcxxabi" \
        -D LLVM_TARGETS_TO_BUILD="X86;SPIRV" \
        -D LLVM_ENABLE_PIC=ON \
        -D LIBCXX_INSTALL_MODULES=ON \
        -D LIBCXXABI_USE_LLVM_UNWINDER=OFF \
        -D LLVM_USE_SANITIZER=Leaks \
        -D LLVM_USE_LINKER="MOLD"

        cd ./build-lsan/

    # (much later...) the actual project you're sanitizing
    cmake # your cmake stuff ...
        -D CMAKE_CXX_FLAGS=" \
            -fsanitize=leak \
            -g \
            -fno-omit-frame-pointer \
            -fno-inline-functions \
            -fno-common \
            -std=c++26 \
            -nostdinc++ \
            -isystem /PATH_TO_LIBCXX_LSAN_INSTALL_PREFIX/include/c++/v1/" \
        -D CMAKE_EXE_LINKER_FLAGS=" \
            -fsanitize=leak \
            -g \
            -fno-omit-frame-pointer \
            -fno-inline-functions \
            -fno-common \
            -std=c++26 \
            -L/PATH_TO_LIBCXX_LSAN_INSTALL_PREFIX/lib \
            -lc++ \
            -lc++abi \
            -Wl,-rpath,/PATH_TO_LIBCXX_LSAN_INSTALL_PREFIX/lib"

After generating the build files, invoke :code:`ninja cxx cxxabi` to build the C++ standard library and the C++ abi with the sanitizer flags enabled.
And finally invoke :code:`ninja install-cxx install-cxxabi` to install what is built under the previously set :code:`CMAKE_INSTALL_PREFIX`.

The bits that change between different sanitizer types are the :code:`LLVM_USE_SANITIZER` when compiling the standard library,
and the :code:`-fsanitize=xxx` flag(s) when compiling your own project. Also note that, for some sanitizers to perform/report better, you need to provide some helping flags, eg. :code:`-fno-omit-frame-pointer`

The available options for :code:`LLVM_USE_SANITIZER` are: 
:code:`Address`, :code:`HWAddress`, :code:`Memory`, :code:`MemoryWithOrigins`, :code:`Undefined`, :code:`Thread`, :code:`DataFlow`, :code:`Leaks`, and :code:`Address;Undefined`

For our purposes: 

- ASan: :code:`LLVM_USE_SANITIZER=Address`
- MSan: :code:`LLVM_USE_SANITIZER=MemoryWithOrigins`
- TSan: :code:`LLVM_USE_SANITIZER=Thread`
- UBSan: :code:`LLVM_USE_SANITIZER=Undefined`

Finally, simply run the engine's runtime or the tests to detect errors.
