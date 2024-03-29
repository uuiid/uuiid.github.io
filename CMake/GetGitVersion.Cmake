include(CMakePrintHelpers)

function(get_git_version)
    set(options IS)
    set(oneValueArgs WORK_DIR)
    set(multiValueArgs DIR)
    cmake_parse_arguments(
            DOODLE_GIT
            "${options}"
            "${oneValueArgs}"
            "${multiValueArgs}"
            ${ARGN}
    )

    find_package(Git)
    #    if(Git_FOUND)
    #        message("Git found: ${GIT_EXECUTABLE}")
    #    endif()
    execute_process( # get_git_version
            COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
            WORKING_DIRECTORY ${DOODLE_GIT_WORK_DIR}
            OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
            RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    #    cmake_print_variables(
    #            DOODLE_GIT_WORK_DIR
    #            GIT_DESCRIBE_ERROR_CODE
    #            GIT_DESCRIBE_VERSION)

    if (NOT GIT_DESCRIBE_ERROR_CODE)
        string(REGEX MATCH [[^v([0-9]+)\.([0-9]+)\.([0-9]+)-?([0-9]+)?(.*)]] _ "${GIT_DESCRIBE_VERSION}")
        #        set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}")
        #        cmake_print_variables(
        #                GIT_DESCRIBE_VERSION
        #                DOODLE_TEST
        #                CMAKE_MATCH_COUNT
        #                CMAKE_MATCH_0
        #                CMAKE_MATCH_1
        #                CMAKE_MATCH_2
        #                CMAKE_MATCH_3
        #                CMAKE_MATCH_4
        #                CMAKE_MATCH_5)
        set(v_major ${CMAKE_MATCH_1} PARENT_SCOPE)
        set(v_minor ${CMAKE_MATCH_2} PARENT_SCOPE)
        set(v_patch ${CMAKE_MATCH_3} PARENT_SCOPE)
        set(v_tweak ${CMAKE_MATCH_4} PARENT_SCOPE)
        set(v_sha1 ${CMAKE_MATCH_5} PARENT_SCOPE)
        if (${CMAKE_MATCH_4})
            set(v_short "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}.${CMAKE_MATCH_4}" PARENT_SCOPE)
        else ()
            set(v_short "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}" PARENT_SCOPE)
        endif ()

    endif ()
endfunction()
