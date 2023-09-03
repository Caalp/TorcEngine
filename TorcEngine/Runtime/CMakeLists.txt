# TorcEngine/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SRCS *.cpp *h)
print_list("${SRCS}")

# in orde to capture entire folder tree in visual studio
GROUP_SRC("${SRCS}")

# entire engine build as static library
add_library("${TORC_ENGINE_LIB_STATIC}" STATIC)

# set(ENGINE_CORE_LIB_STATIC "Core")
# set(ENGINE_PLATFORM_LIB_STATIC "Platform")
# set(ENGINE_RENDERER_LIB_STATIC "Renderer")
# set(TORC_GFX_LIB "") # currently this is dll



set_target_properties("${TORC_ENGINE_LIB_STATIC}" PROPERTIES FOLDER "${TORC_ENGINE_LIB_STATIC}")
# target_link_libraries("${TORC_ENGINE_LIB_STATIC}" PUBLIC "${ENGINE_CORE_LIB_STATIC}" "${ENGINE_PLATFORM_LIB_STATIC}" "${ENGINE_RENDERER_LIB_STATIC}")

set_property(TARGET "${TORC_ENGINE_LIB_STATIC}" APPEND PROPERTY COMPILE_FLAGS "/Yupch.h")
set_property(SOURCE "pch.cpp" APPEND PROPERTY COMPILE_FLAGS "/Ycpch.h")


# finds sub-folders of starting from current directory and adds folders as subdirectory if they have CMakeLists.txt 
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}")
add_as_sub_directory("${CMAKE_CURRENT_SOURCE_DIR}")


