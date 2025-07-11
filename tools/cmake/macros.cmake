macro (add_library_module libname)
    if ("${ARGN}" STREQUAL "") # Header only library
        message("Adding INTERFACE library ${libname}")
        add_library(${libname} INTERFACE)
        target_include_directories(${libname} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

        # Do not link base against base :D
        if (NOT ${libname} STREQUAL "base")
            target_link_libraries(${libname} INTERFACE base)
        endif ()

    else () # Compiled library
        set(source_files)
        set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/src")
        foreach (source_file ${ARGN})
            list(APPEND source_files "${source_directory}/${source_file}")
        endforeach ()

        message("Adding library ${libname} with source files: ${source_files}")
        add_library(${libname} ${source_files})
        target_include_directories(${libname} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

        # Do not link base against base :D
        if (NOT ${libname} STREQUAL "base")
            target_link_libraries(${libname} PUBLIC base)
        endif ()
    endif ()
endmacro ()

macro (add_executable_module exename)
    set(source_files)
    set(source_directory "${CMAKE_CURRENT_SOURCE_DIR}/src")
    foreach (source_file ${ARGN})
        list(APPEND source_files "${source_directory}/${source_file}")
    endforeach ()

    message("Adding executable ${exename} with source files: ${source_files}")
    add_executable(${exename} ${source_files})
    target_include_directories(${exename} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${exename} PUBLIC base)
endmacro ()

macro (add_option option help)
    option(${option} ${help})

    if (${option})
        message(STATUS "${option}: ON")
        add_compile_definitions(${option}=1)
    else ()
        message(STATUS "${option}: OFF")
    endif ()
endmacro ()
