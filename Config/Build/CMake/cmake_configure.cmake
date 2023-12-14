find_program(CMAKE_EXISTS "cmake")
if(CMAKE_EXISTS)
	message(STATUS "CMake Path: ${CMAKE_EXISTS}")
else()
	message(FATAL_ERROR "CMake is not found please install CMake version higher than 3.6.2")
endif()

if(NOT DEFINED PROJECT_DIR)
	set(PROJECT_DIR "${CMAKE_SOURCE_DIR}")
endif()
set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS Debug)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if(WIN32  AND CMAKE_SIZEOF_VOID_P EQUAL 8)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/Win64")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/Win64")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/Win64")
endif()

set (GAME_PROJECT_NAME TestGame CACHE STRING "Game project name" FORCE)
set(TORC_ENGINE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/TorcEngine" CACHE STRING "Engine Directory" FORCE)
set(TORC_PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}" CACHE STRING "Root Directory" FORCE)
file(TO_NATIVE_PATH ${TORC_PROJECT_ROOT_DIR} TORC_PROJECT_ROOT_DIR_NATIVE_OS)
set(TORC_PROJECT_ROOT_DIR_NATIVE_OS "${TORC_PROJECT_ROOT_DIR_NATIVE_OS}" CACHE STRING "Torc Source root path os specific backslashes")
set (TORC_PROJECT_ROOT_DIR_NATIVE_OS_STR "${TORC_PROJECT_ROOT_DIR_NATIVE_OS_STR}" CACHE STRING "")
string(REPLACE "\\" "\\\\" TORC_PROJECT_ROOT_DIR_NATIVE_OS_STR ${TORC_PROJECT_ROOT_DIR_NATIVE_OS})

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "" FORCE)

set(TORC_ENGINE_LIB_STATIC TorcEngine CACHE STRING "Main TorcEngine Static Library" FORCE)
set(TORC_ENGINE_LIB_DYNAMIC TorcEngine CACHE STRING "Main TorcEngine Dynamic Library" FORCE)

# set target platform win32, win64, linux, etc
# currenly only win64 is supported
set (TARGET_PLATFORM WIN64 CACHE STRING "Target platform to compile win32, win64, linux etc. (Only win64 supported currently)" FORCE)
string(TOUPPER "${TARGET_PLATFORM}" target_platform_uppercase)
# check and set appropriate compile flag
if("${target_platform_uppercase}" STREQUAL "WIN64")
	message(STATUS "TARGET_PLATFORM is set to ${target_platform_uppercase}")
	add_compile_definitions(${TORC_ENGINE_LIB_STATIC} TORC_PLATFORM_WIN64=1)

elseif("${gfx_backend_lowercase}" STREQUAL "LINUX")
	message(STATUS "Compiling with ${gfx_backend_uppercase}")
	add_compile_definitions(${TORC_ENGINE_LIB_STATIC} TORC_PLATFORM_WIN64=0)
endif()



