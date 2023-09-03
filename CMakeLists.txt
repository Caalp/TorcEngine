cmake_minimum_required(VERSION 3.6.2)
project(TorcEngine)
include(Config/Build/CMake/cmake_configure.cmake)
include(Config/Build/CMake/cmake_gfx_configure.cmake)
include(Config/Build/CMake/cmake_utilities.cmake)


#Check for visual studio version
#get_filename_component(vs_version  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\14.0\\VC\\Runtimes\\debug\\x64;Version]" ABSOLUTE CACHE)
#message( "vs_version = ${vs_version}" )

add_subdirectory(TorcEngine)
add_subdirectory(TestGame)

