function(add_option option help)
    option(${option} ${help})

    if(${option})
        message(STATUS "${option}: ON")
        add_compile_definitions(${option}=1)
    else()
        message(STATUS "${option}: OFF")
    endif()
endfunction()

add_option(
    ENABLE_SANDBOX
    "Enables the building of the sandbox module for experimentation"
)
add_option(ENABLE_UNIT_TESTS "Enables the building of the unit test modules")
add_option(ENABLE_FUZZ_TESTS "Enables the building of the fuzz test modules")
add_option(
    ENABLE_STATIC_ANALYSIS
    "Makes the clang-tidy checks mandatory for compilation"
)
add_option(
    ENABLE_LLVM_COVERAGE "Enables the code coverage instrumentation for clang"
)

add_option(
    ENABLE_LSAN "Disables build of modules that don't supprot leak sanitizer"
)
add_option(
    ENABLE_ASAN
    "Disables build of modules that don't supprot address sanitizer"
)
add_option(
    ENABLE_UBSAN
    "Disables build of modules that don't supprot undefined behavior sanatizer"
)
add_option(
    ENABLE_MSAN "Disables build of modules that don't supprot memory sanitizer"
)
add_option(
    ENABLE_TSAN "Disables build of modules that don't supprot thread sanitizer"
)

if(ENABLE_STATIC_ANALYSIS)
    set(CMAKE_CXX_CLANG_TIDY
        "clang-tidy;--warnings-as-errors=*;--allow-no-checks;--system-headers=false;--header-filter='./modules/*'"
    )
endif()

if(ENABLE_LLVM_COVERAGE)
    if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        message(
            FATAL_ERROR "ENABLE_LLVM_COVERAGE only supports the clang compiler"
        )
    endif()

    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif()
