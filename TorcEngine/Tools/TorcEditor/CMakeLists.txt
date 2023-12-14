# TorcEngine/Tools/TorcEditor/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/TorcEngine/Runtime" "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty")

# folder to look for libraries
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB_RECURSE SRCS *.cpp *h)
print_list("${SRCS}")
GROUP_SRC("${SRCS}")

set(EDITOR_PROJECT_NAME "TorcEditor")
set(imgui_src "")
file(GLOB_RECURSE imgui_src "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty/ImGui/*h" "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty/ImGui/*cpp")
add_library("ImGui" ${imgui_src})

# add main entry point to the game
add_executable(${EDITOR_PROJECT_NAME} WIN32 EditorMain.cpp)

target_compile_definitions(${EDITOR_PROJECT_NAME} PRIVATE "TORC_EDITOR")
target_include_directories(${EDITOR_PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/TorcEngine/Runtime")
target_include_directories(${EDITOR_PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty")

# link engine with executable
target_link_libraries(${EDITOR_PROJECT_NAME} PRIVATE TorcEngine)
target_link_libraries(${EDITOR_PROJECT_NAME} PRIVATE ImGui)
add_dependencies(${EDITOR_PROJECT_NAME} TorcEngine GfxD3D11)

# in this case project name and folder names match
set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES FOLDER "Tools/${EDITOR_PROJECT_NAME}")

set_target_sources("${EDITOR_PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}")
add_as_sub_directory("${CMAKE_CURRENT_SOURCE_DIR}")