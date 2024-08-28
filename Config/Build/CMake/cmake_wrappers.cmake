    function(te_add_target)

    set(options STATIC SHARED INTERFACE EXECUTABLE SOURCE_GROUP CONSOLE_APPLICATION)
    set(oneValueArgs NAME NAMESPACE)
    set(multiValueArgs FILES_CMAKE INCLUDE_DIRECTORIES BUILD_DEPENDENCIES TARGET_PROPERTIES TARGET_DEFINITIONS TARGET_PLATFORM_FILES_CMAKE COMPILE_DEFINITIONS FILES_SOURCE)

    cmake_parse_arguments(te_add_target "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(PLATFORM_FILES "")
    set(ALL_FILES "")

    if(NOT te_add_target_NAME)
        message(FATAL_ERROR "Target name is missing.")
    endif()

    if(te_add_target_FILES_CMAKE)
        include(${te_add_target_FILES_CMAKE})
        #message(STATUS "${te_add_target_FILES_CMAKE}")
        list(APPEND ALL_FILES ${te_add_target_FILES_CMAKE})
    endif()

    if(te_add_target_TARGET_PLATFORM_FILES_CMAKE)
        include(${te_add_target_TARGET_PLATFORM_FILES_CMAKE})
        set(PLATFORM_FILES ${PLATFORM_FILES})
        list(APPEND ALL_FILES ${te_add_target_TARGET_PLATFORM_FILES_CMAKE})
    endif()

    list(APPEND ALL_FILES ${PLATFORM_FILES} ${FILES})

    if(te_add_target_FILES_SOURCE)
        list(APPEND ALL_FILES ${te_add_target_FILES_SOURCE})
    endif()

    set(is_library ON)

    if(te_add_target_STATIC)
        add_library(${te_add_target_NAME} STATIC ${ALL_FILES})
    endif()
    
    if(te_add_target_SHARED)
        add_library(${te_add_target_NAME} SHARED ${ALL_FILES})
    endif()
    
    if(te_add_target_INTERFACE)
        add_library(${te_add_target_NAME} INTERFACE ${ALL_FILES})
    endif()

    if(te_add_target_EXECUTABLE AND te_add_target_CONSOLE_APPLICATION)
        add_executable(${te_add_target_NAME} ${ALL_FILES})
        set(is_library OFF)
    
    elseif(te_add_target_EXECUTABLE)
        add_executable(${te_add_target_NAME} WIN32 ${ALL_FILES})
        set(is_library OFF)
    endif()

    if(te_add_target_INCLUDE_DIRECTORIES)
        #define_property(TARGET ${te_add_target_NAME} PROPERTY te_${te_add_target_NAME}_INCLUDE_DIRS)
        #set_property(TARGET ${te_add_target_NAME} PROPERTY te_${te_add_target_NAME}_INCLUDE_DIRECTORIES ${te_add_target_INCLUDE_DIRECTORIES})
        target_include_directories(${te_add_target_NAME} ${te_add_target_INCLUDE_DIRECTORIES})
    endif()

    if(te_add_target_TARGET_DEFINITIONS)
        add_definitions(${te_add_target_NAME} ${te_add_target_TARGET_DEFINITIONS})
    endif()

    if(te_add_target_COMPILE_DEFINITIONS)
        target_compile_definitions(${te_add_target_NAME} ${te_add_target_COMPILE_DEFINITIONS})
    endif()

    if(te_add_target_BUILD_DEPENDENCIES)
        target_link_libraries(${te_add_target_NAME} ${te_add_target_BUILD_DEPENDENCIES})
    endif()

    if(te_add_target_TARGET_PROPERTIES)
        set_target_properties(${te_add_target_NAME} PROPERTIES ${te_add_target_TARGET_PROPERTIES})
    endif()

    if(te_add_target_NAMESPACE AND is_library)
        add_library(${te_add_target_NAMESPACE}::${te_add_target_NAME} ALIAS ${te_add_target_NAME})
    endif()

    if(NOT is_library AND te_add_target_NAMESPACE)
        message(WARNING "A namespace is given for a Target that is not a library.")
    endif()

    if(te_add_target_SOURCE_GROUP)
        te_source_group("${ALL_FILES}")
    endif()
endfunction()