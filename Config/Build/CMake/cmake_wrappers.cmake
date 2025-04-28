# Function for adding a build target it can be static library, dll or an interface.
# If no FILES_CMAKE specified, will look for Public and Private folders and add them to target, and expose Public folder as
# includes.
    
function(te_add_target)

    set(options STATIC SHARED INTERFACE EXECUTABLE SOURCE_GROUP CONSOLE_APPLICATION)
    set(oneValueArgs NAME NAMESPACE CMAKE_LOOKUP_MODULE_PATH)
    set(multiValueArgs FILES_CMAKE INCLUDE_DIRECTORIES BUILD_DEPENDENCIES TARGET_PROPERTIES TARGET_DEFINITIONS TARGET_PLATFORM_FILES_CMAKE COMPILE_DEFINITIONS FILES_SOURCE)

    cmake_parse_arguments(te_add_target "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(PLATFORM_FILES "")
    set(ALL_FILES "")

    set(PUBLIC_INCLUDES "")
    set(PRIVATE_INCLUDES "")

    if(te_add_target_CMAKE_LOOKUP_MODULE_PATH)
        list(APPEND CMAKE_MODULE_PATH "${te_add_target_CMAKE_LOOKUP_MODULE_PATH}")
        message(STATUS " hellooo  ${CMAKE_CURRENT_SOURCE_DIR}")
    endif()

    if(NOT te_add_target_NAME)
        message(FATAL_ERROR "Target name is missing.")
    endif()

    if(te_add_target_FILES_CMAKE)

        file(GLOB_RECURSE INCLUDE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/*${te_add_target_FILES_CMAKE}")  

        # get relative path to .cmake file is specified
        file(RELATIVE_PATH RELATIVE_FILE "${CMAKE_CURRENT_SOURCE_DIR}" "${INCLUDE_FILE}")

        # include that cmake file
        include(${RELATIVE_FILE})

        # get relative directory of that file
        get_filename_component(RELATIVE_DIR "${RELATIVE_FILE}" DIRECTORY)
       
        # add cmake file itself to all files 
        list(APPEND ALL_FILES ${RELATIVE_FILE})

        # add all files in Files list that defined in .cmake include to ALL_FILES list and
        # prefix it with relative path
        # [NOTE] We might need to check entries before prefixing relative directory, in case if they already have it
        # or current directory is already same as relative one. Currently assuming current cmake directory is different than
        # where .cmake is placed (in a child directory).
        if (${RELATIVE_DIR} NOT STREQUAL "/")
            foreach(item IN LISTS FILES)
                list(APPEND ALL_FILES "${RELATIVE_DIR}/${item}")
            endforeach()

            foreach(item IN LISTS PUBLIC_FILES)
                list(APPEND ALL_FILES "${RELATIVE_DIR}/${item}")
            endforeach()

            foreach(item IN LISTS PRIVATE_FILES)
                list(APPEND ALL_FILES "${RELATIVE_DIR}/${item}")
            endforeach()
        else()
            # Currently we support FILES, PUBLIC_FILES and PRIVATE_FILES. Later, we can pass these as parameter as well.
            list(APPEND ALL_FILES "${FILES}" "${PUBLIC_FILES}" "${PRIVATE_FILES}")
        endif()

    else()

        # [NOTE] for now only handle public and private later on we can add others if exists.
        file(GLOB_RECURSE PUBLIC_INCLUDES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Public/*")
        file(GLOB_RECURSE PRIVATE_INCLUDES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Private/*")

        list(APPEND ALL_FILES ${PUBLIC_INCLUDES} ${PRIVATE_INCLUDES})

    endif()

    if(te_add_target_TARGET_PLATFORM_FILES_CMAKE)
        include(${te_add_target_TARGET_PLATFORM_FILES_CMAKE})
        set(PLATFORM_FILES ${PLATFORM_FILES})
        list(APPEND ALL_FILES ${te_add_target_TARGET_PLATFORM_FILES_CMAKE})
    endif()

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

    # public folder is added as include directory by default if exists
    # [Warning] on windows this is fine but on linux paths are case sensitive.
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Public" AND NOT te_add_target_FILES_CMAKE)
        target_include_directories(${te_add_target_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Public)
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