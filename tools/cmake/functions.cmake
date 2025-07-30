function (add_library_module libname)
    set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/public_includes")
    file(MAKE_DIRECTORY "${PUBLIC_INCLUDE_DIR}")
    file(CREATE_LINK
        "${CMAKE_CURRENT_SOURCE_DIR}/public/"
        "${PUBLIC_INCLUDE_DIR}/${libname}"
        SYMBOLIC
    )

    if ("${ARGN}" STREQUAL "") # Header only library
        message("Adding INTERFACE library ${libname}")
        add_library(${libname} INTERFACE)
        target_include_directories(${libname} INTERFACE ${PUBLIC_INCLUDE_DIR})

        # Do not link base against base :D
        if (NOT ${libname} STREQUAL "base")
            target_link_libraries(${libname} INTERFACE base)
        endif ()

    else () # Compiled library
        set(source_files)
        set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
        foreach (source_file ${ARGN})
            list(APPEND source_files "${source_directory}/${source_file}")
        endforeach ()

        message("Adding library ${libname} with source files: ${source_files}")
        add_library(${libname} ${source_files})

        set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/private_includes")
        file(MAKE_DIRECTORY "${PRIVATE_INCLUDE_DIR}")
        file(CREATE_LINK
            "${CMAKE_CURRENT_SOURCE_DIR}/private/"
            "${PRIVATE_INCLUDE_DIR}/${libname}"
            SYMBOLIC
        )

        target_include_directories(${libname} 
            PUBLIC ${PUBLIC_INCLUDE_DIR}
            PRIVATE ${PRIVATE_INCLUDE_DIR}
        )

        # Do not link base against base :D
        if (NOT ${libname} STREQUAL "base")
            target_link_libraries(${libname} PUBLIC base)
        endif ()
    endif ()

endfunction ()

function (add_executable_module exename)
    set(source_files)
    set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
    foreach (source_file ${ARGN})
        list(APPEND source_files "${source_directory}/${source_file}")
    endforeach ()

    message("Adding executable ${exename} with source files: ${source_files}")

    set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/public_includes")
    file(MAKE_DIRECTORY "${PUBLIC_INCLUDE_DIR}")
    file(CREATE_LINK
        "${CMAKE_CURRENT_SOURCE_DIR}/public/"
        "${PUBLIC_INCLUDE_DIR}/${exename}"
        SYMBOLIC
    )
    set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/private_includes")
    file(MAKE_DIRECTORY "${PRIVATE_INCLUDE_DIR}")
    file(CREATE_LINK
        "${CMAKE_CURRENT_SOURCE_DIR}/private/"
        "${PRIVATE_INCLUDE_DIR}${exename}"
        SYMBOLIC
    )

    add_executable(${exename} ${source_files})
    target_link_libraries(${exename} PRIVATE base)
    target_include_directories(${exename} PRIVATE ${PUBLIC_INCLUDE_DIR} ${PRIVATE_INCLUDE_DIR})
endfunction ()

function (add_test_module target_lib_name)
    if (NOT ${ENABLE_TESTS})
        return()
    endif ()

    set(source_files)
    set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
    foreach (source_file ${ARGN})
        list(APPEND source_files "${source_directory}/${source_file}")
    endforeach ()

    message("Adding test executable ${target_lib_name}_tests with source files: ${source_files}")

    set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/public_includes")
    file(MAKE_DIRECTORY "${PUBLIC_INCLUDE_DIR}")
    file(CREATE_LINK
        "${CMAKE_CURRENT_SOURCE_DIR}/public/"
        "${PUBLIC_INCLUDE_DIR}/${target_lib_name}"
        SYMBOLIC
    )
    set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/private_includes")
    file(MAKE_DIRECTORY "${PRIVATE_INCLUDE_DIR}")
    file(CREATE_LINK
        "${CMAKE_CURRENT_SOURCE_DIR}/private/"
        "${PRIVATE_INCLUDE_DIR}/${target_lib_name}"
        SYMBOLIC
    )

    add_executable(${target_lib_name}_tests ${source_files})
    target_link_libraries(${target_lib_name}_tests PRIVATE ${target_lib_name} base test)
    target_include_directories(${target_lib_name}_tests
        PRIVATE ${PUBLIC_INCLUDE_DIR}
        PRIVATE ${PRIVATE_INCLUDE_DIR}
    )
endfunction ()

function (add_fuzz_module target_lib_name)
    if (NOT ${ENABLE_TESTS})
        return()
    endif ()

    set(source_files)
    set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
    foreach (source_file ${ARGN})
        list(APPEND source_files "${source_directory}/${source_file}")
    endforeach ()

    message("Adding fuzz executable ${target_lib_name}_fuzz with source files: ${source_files}")

    set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/public_includes")
    file(MAKE_DIRECTORY "${PUBLIC_INCLUDE_DIR}")
    file(CREATE_LINK
        "${CMAKE_CURRENT_SOURCE_DIR}/public/"
        "${PUBLIC_INCLUDE_DIR}/${target_lib_name}"
        SYMBOLIC
    )
    set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/private_includes")
    file(MAKE_DIRECTORY "${PRIVATE_INCLUDE_DIR}")
    file(CREATE_LINK
        "${CMAKE_CURRENT_SOURCE_DIR}/private/"
        "${PRIVATE_INCLUDE_DIR}/${target_lib_name}"
        SYMBOLIC
    )

    add_executable(${target_lib_name}_fuzz ${source_files})
    target_link_libraries(${target_lib_name}_fuzz PRIVATE ${target_lib_name} base fuzz_test)
    target_link_options(${target_lib_name}_fuzz PRIVATE -fsanitize=fuzzer)
    target_compile_options(${target_lib_name}_fuzz PRIVATE -fsanitize=fuzzer)
    target_include_directories(${target_lib_name}_fuzz
        PRIVATE ${PUBLIC_INCLUDE_DIR}
        PRIVATE ${PRIVATE_INCLUDE_DIR}
    )
endfunction ()

function (add_option option help)
    option(${option} ${help})

    if (${option})
        message(STATUS "${option}: ON")
        add_compile_definitions(${option}=1)
    else ()
        message(STATUS "${option}: OFF")
    endif ()
endfunction ()
