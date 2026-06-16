function(add_module)
    cmake_parse_arguments(
        ARGS
        ""
        "NAME"
        "INTERFACES;ROOT_DIR;SOURCES;DEPENDENCIES;PRIVATE_DEPENDENCIES;TESTS;TEST_INTERFACES;ENTRYPOINT;"
        ${ARGN}
    )

    if(NOT ARGS_NAME)
        message(FATAL_ERROR "You MUST provide a name")
    endif()

    set(target_library_name ${ARGS_NAME})
    set(target_executable_name ${ARGS_NAME})

    set(module_directory "${CMAKE_CURRENT_SOURCE_DIR}/${target_library_name}")
    if(ARGS_ROOT_DIR)
        set(module_directory "${ARGS_ROOT_DIR}")
    endif()

    # In this case, the module is an executable, so we prepend "lib" to the
    # target name. And set the "executable_target" name to ARGS_NAME. The
    # rationale here is to easily be able to write tests for an executable
    # modules's interfaces... by splitting it into two targets:
    # lib"executable_name" for the interface and "executable_name" for the "int
    # main()" defining file (the entrypoint). the lib"executable_name" should
    # not be disruptive since an executable module's library will not be
    # dependent upon (except by the tests within the same module)
    if(ARGS_ENTRYPOINT)
        set(target_library_name "lib_${ARGS_NAME}")
        add_executable(
            ${target_executable_name} ${module_directory}/${ARGS_ENTRYPOINT}
        )
    endif()
    add_library(${target_library_name})

    if(ARGS_SOURCES)
        set(files)
        foreach(file ${ARGS_SOURCES})
            list(APPEND files "${module_directory}/${file}")
        endforeach()

        target_sources(${target_library_name} PRIVATE ${files})
    endif()

    if(ARGS_PUBLIC_SOURECS)
        set(files)
        foreach(file ${ARGS_PUBLIC_SOURECS})
            list(APPEND files "${module_directory}/${file}")
        endforeach()
        target_sources(${target_library_name} PUBLIC ${files})
    endif()

    if(ARGS_INTERFACES)
        set(files)
        foreach(file ${ARGS_INTERFACES})
            list(APPEND files "${module_directory}/${file}")
        endforeach()
        target_sources(
            ${target_library_name} PUBLIC FILE_SET public_cxx_modules TYPE
                                          CXX_MODULES FILES ${files}
        )
    endif()

    target_link_libraries(${target_library_name} PUBLIC ${ARGS_DEPENDENCIES})
    target_link_libraries(
        ${target_library_name} PRIVATE ${ARGS_PRIVATE_DEPENDENCIES}
    )

    if(ARGS_TESTS)
        set(test_files)
        foreach(test_file ${ARGS_TESTS})
            list(APPEND test_files "${module_directory}/${test_file}")
        endforeach()

        add_executable("${target_library_name}_tests" ${test_files})
        target_link_libraries(
            "${target_library_name}_tests"
            PRIVATE ${target_library_name}
                    #
                    test
        )
        if(ARGS_TEST_INTERFACES)
            set(test_interface_files)
            foreach(file ${ARGS_TEST_INTERFACES})
                list(APPEND test_interface_files "${module_directory}/${file}")
            endforeach()
            target_sources(
                "${target_library_name}_tests"
                PRIVATE FILE_SET test_cxx_modules TYPE CXX_MODULES FILES
                        ${test_interface_files}
            )
        endif()
    endif()

    if(ARGS_ENTRYPOINT)
        target_link_libraries(
            ${target_executable_name} PRIVATE ${target_library_name}
        )
    endif()
endfunction()
