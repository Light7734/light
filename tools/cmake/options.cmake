add_option(ENABLE_UNIT_TESTS "Enables the building of the unit test modules")
add_option(ENABLE_FUZZ_TESTS "Enables the building of the fuzz test modules")
add_option(ENABLE_STATIC_ANALYSIS "Makes the clang-tidy checks mandatory for compilation")
add_option(ENABLE_LLVM_COVERAGE "Enables the code coverage instrumentation for clang")

if (ENABLE_STATIC_ANALYSIS)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--warnings-as-errors=*;--allow-no-checks")
endif ()

if(ENABLE_LLVM_COVERAGE)
    include(CheckCXXSourceCompiles)

    if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        message(FATAL_ERROR "ENABLE_LLVM_COVERAGE only supports the clang compiler")
    endif ()

    # Check for libc++
    check_cxx_source_compiles("
        #include <string>
        #ifdef _LIBCPP_VERSION
        int main() { return 0; }
        #else
        #error Not using libc++
        #endif
    " USING_LIBCXX)
    if(NOT USING_LIBCXX)
        message(FATAL_ERROR "ENABLE_LLVM_COVERAGE requires libc++, please compile with -stdlib=libc++")
    endif()

    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif ()
