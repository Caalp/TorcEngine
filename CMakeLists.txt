cmake_minimum_required(VERSION 3.13)

if(POLICY CMP0079 )
  cmake_policy(SET CMP0079 NEW)
endif()

project(TorcEngine)
include(Config/Build/CMake/cmake_configure.cmake)
include(Config/Build/CMake/cmake_gfx_configure.cmake)
include(Config/Build/CMake/cmake_utilities.cmake)
#set(CMAKE_OPTIMIZE_DEPENDENCIES 1)

#Check for visual studio version
#get_filename_component(vs_version  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\14.0\\VC\\Runtimes\\debug\\x64;Version]" ABSOLUTE CACHE)
#message( "vs_version = ${vs_version}" )

# set_target_properties(
#     TorcEngine PROPERTIES
#     VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/TorcEngine")


# set_target_properties(
    # TorcEngine PROPERTIES
    # ENGINE_HOME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(TorcEngine)
add_subdirectory(TestGame)

