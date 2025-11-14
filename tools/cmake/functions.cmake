function(add_library_module)
    cmake_parse_arguments(
        ARGS
        ""
        "NAME"
        "INTERFACES;ROOT_DIR;PRIVATE_INTERFACES;SOURCES;DEPENDENCIES;PRIVATE_DEPENDENCIES"
        ${ARGN}
    )

    if(NOT ARGS_NAME)
        message(FATAL_ERROR "You must provide a name")
    endif()

    add_library(${ARGS_NAME})

    set(module_directory "${CMAKE_CURRENT_SOURCE_DIR}/${ARGS_NAME}")
    if(ARGS_ROOT_DIR)
        set(module_directory "${ARGS_ROOT_DIR}")
    endif()

    if(ARGS_SOURCES)
        set(files)
        foreach(file ${ARGS_SOURCES})
            list(APPEND files "${module_directory}/${file}")
        endforeach()
        target_sources(${ARGS_NAME} PRIVATE ${files})
    endif()

    if(ARGS_INTERFACES)
        set(files)
        foreach(file ${ARGS_INTERFACES})
            list(APPEND files "${module_directory}/${file}")
        endforeach()
        target_sources(
            ${ARGS_NAME} PUBLIC FILE_SET public_cxx_modules TYPE CXX_MODULES
                                FILES ${files}
        )
    endif()

    if(ARGS_PRIVATE_INTERFACES)
        set(files)
        foreach(file ${ARGS_PRIVATE_INTERFACES})
            list(APPEND files "${module_directory}/${file}")
        endforeach()
        target_sources(
            ${ARGS_NAME} PRIVATE FILE_SET private_cxx_modules TYPE CXX_MODULES
                                 FILES ${files}
        )
    endif()

    target_link_libraries(${ARGS_NAME} PUBLIC ${ARGS_DEPENDENCIES})
    target_link_libraries(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE_DEPENDENCIES})
endfunction()

function(add_executable_module exename)
    set(source_files)
    set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
    foreach(source_file ${ARGN})
        list(APPEND source_files "${source_directory}/${source_file}")
    endforeach()

    message("Adding executable ${exename} with source files: ${source_files}")

    set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/public_includes")
    file(MAKE_DIRECTORY "${PUBLIC_INCLUDE_DIR}")
    file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/public/"
         "${PUBLIC_INCLUDE_DIR}/${exename}" SYMBOLIC
    )
    set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/private_includes")
    file(MAKE_DIRECTORY "${PRIVATE_INCLUDE_DIR}")
    file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/private/"
         "${PRIVATE_INCLUDE_DIR}${exename}" SYMBOLIC
    )

endfunction()

function(add_test_module target_lib_name)
    # if(NOT ${ENABLE_UNIT_TESTS}) return() endif()

    add_executable(${target_lib_name}_tests ${ARGN})
    target_link_libraries(
        ${target_lib_name}_tests
        PRIVATE ${target_lib_name}
                #
                test
    )

    return()

    set(source_files)
    set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
    foreach(source_file ${ARGN})
        list(APPEND source_files "${source_directory}/${source_file}")
    endforeach()

    message(
        "Adding test executable ${target_lib_name}_tests with source files: ${source_files}"
    )

    set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/public_includes")
    file(MAKE_DIRECTORY "${PUBLIC_INCLUDE_DIR}")
    file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/public/"
         "${PUBLIC_INCLUDE_DIR}/${target_lib_name}" SYMBOLIC
    )
    set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/private_includes")
    file(MAKE_DIRECTORY "${PRIVATE_INCLUDE_DIR}")
    file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/private/"
         "${PRIVATE_INCLUDE_DIR}/${target_lib_name}" SYMBOLIC
    )

    add_executable(${target_lib_name}_tests ${source_files})
    target_link_libraries(
        ${target_lib_name}_tests PRIVATE ${target_lib_name} std test
    )
    target_include_directories(
        ${target_lib_name}_tests
        PRIVATE ${PUBLIC_INCLUDE_DIR}
        PRIVATE ${PRIVATE_INCLUDE_DIR}
    )
endfunction()

function(add_fuzz_module target_lib_name)
    if(NOT ${ENABLE_FUZZ_TESTS})
        return()
    endif()

    set(source_files)
    set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
    foreach(source_file ${ARGN})
        list(APPEND source_files "${source_directory}/${source_file}")
    endforeach()

    message(
        "Adding fuzz executable ${target_lib_name}_fuzz with source files: ${source_files}"
    )

    set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/public_includes")
    file(MAKE_DIRECTORY "${PUBLIC_INCLUDE_DIR}")
    file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/public/"
         "${PUBLIC_INCLUDE_DIR}/${target_lib_name}" SYMBOLIC
    )
    set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/private_includes")
    file(MAKE_DIRECTORY "${PRIVATE_INCLUDE_DIR}")
    file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/private/"
         "${PRIVATE_INCLUDE_DIR}/${target_lib_name}" SYMBOLIC
    )

    add_executable(${target_lib_name}_fuzz ${source_files})
    target_link_libraries(
        ${target_lib_name}_fuzz PRIVATE ${target_lib_name} std fuzz_test
    )
    target_link_options(${target_lib_name}_fuzz PRIVATE -fsanitize=fuzzer)
    target_compile_options(${target_lib_name}_fuzz PRIVATE -fsanitize=fuzzer)
    target_include_directories(
        ${target_lib_name}_fuzz
        PRIVATE ${PUBLIC_INCLUDE_DIR}
        PRIVATE ${PRIVATE_INCLUDE_DIR}
    )
endfunction()

function(add_option option help)
    option(${option} ${help})

    if(${option})
        message(STATUS "${option}: ON")
        add_compile_definitions(${option}=1)
    else()
        message(STATUS "${option}: OFF")
    endif()
endfunction()
