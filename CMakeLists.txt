cmake_minimum_required(VERSION 3.19)

if(POLICY CMP0079 )
  cmake_policy(SET CMP0079 NEW)
endif()

project(TorcEngine)
include(Config/Build/CMake/cmake_configure.cmake)
include(Config/Build/CMake/cmake_gfx_configure.cmake)
include(Config/Build/CMake/cmake_utilities.cmake)
include(Config/Build/CMake/cmake_wrappers.cmake)

#<copy_destination>@<copy_target> and entries are separated by semicolon
define_property(GLOBAL PROPERTY COPY_TARGET_DEPENDENCY_LIST)

# check https://cmake.org/cmake/help/v3.20/prop_tgt/OPTIMIZE_DEPENDENCIES.html#prop_tgt:OPTIMIZE_DEPENDENCIES
#set(CMAKE_OPTIMIZE_DEPENDENCIES 1)

add_subdirectory(3rdParty)
add_subdirectory(Engine)
add_subdirectory(TestGame)

get_property(test_var GLOBAL PROPERTY COPY_TARGET_DEPENDENCY_LIST)
write_file(${CMAKE_CURRENT_BINARY_DIR}/dependecy_list "${test_var}")

execute_process(COMMAND python Config/Build/copy_dependency_list.py ${CMAKE_CURRENT_BINARY_DIR}/dependecy_list)