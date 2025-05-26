macro (add_library_module libname)
    if ("${ARGN}" STREQUAL "") # Header only library
        message("Adding INTERFACE library ${libname}")
        add_library(${libname} INTERFACE)
        target_include_directories(${libname} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/public)

        # Do not link universal_pch against universal_pch  :D
        if (NOT ${libname} STREQUAL "universal_pch")
            target_link_libraries(${libname} INTERFACE universal_pch)
        endif ()

    else () # Compiled library
        set(source_files)
        set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/private")
        foreach (source_file ${ARGN})
            list(APPEND source_files "${source_directory}/${source_file}")
        endforeach ()

        message("Adding library ${libname} with source files: ${source_files}")
        add_library(${libname} ${source_files})
        target_include_directories(${libname} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
        target_include_directories(${libname} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private)
        target_compile_options(${libname} PRIVATE ${WARNING_FLAGS})

        # Do not link universal_pch against universal_pch  :D
        if (NOT ${libname} STREQUAL "universal_pch")
            target_link_libraries(${libname} PUBLIC universal_pch)
        endif ()
    endif ()

    if (ENABLE_STATIC_ANALYSIS)
        set_target_properties(${libname} PROPERTIES CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
    endif ()
endmacro ()
