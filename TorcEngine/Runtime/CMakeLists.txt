# TorcEngine/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty")

file(GLOB_RECURSE SRCS *.cpp *h)
print_list("${SRCS}")

# in orde to capture entire folder tree in visual studio
GROUP_SRC("${SRCS}")

# entire engine build as static library
add_library("${TORC_ENGINE_LIB_STATIC}" STATIC)

set_target_properties("${TORC_ENGINE_LIB_STATIC}" PROPERTIES FOLDER "${TORC_ENGINE_LIB_STATIC}")
add_compile_definitions("${TORC_ENGINE_LIB_STATIC}" ENGINE_ROOT_DIR="${TORC_PROJECT_ROOT_DIR_NATIVE_OS_STR}")
add_compile_definitions("${TORC_ENGINE_LIB_STATIC}" ENGINE_SOURCE_DIR="${TORC_ENGINE_SOURCE_DIR}")

set_property(TARGET "${TORC_ENGINE_LIB_STATIC}" APPEND PROPERTY COMPILE_FLAGS "/Yupch.h")
set_property(SOURCE "pch.cpp" APPEND PROPERTY COMPILE_FLAGS "/Ycpch.h")

# finds sub-folders of starting from current directory and adds folders as subdirectory if they have CMakeLists.txt 
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}")
add_as_sub_directory("${CMAKE_CURRENT_SOURCE_DIR}")