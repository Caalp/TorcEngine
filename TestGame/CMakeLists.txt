
# include folders in TorcEngine folder
include_directories(${CMAKE_SOURCE_DIR}/TorcEngine/Runtime)

# folder to look for libraries
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# reset game project name
set(GAME_PROJECT_NAME "TestGame")

# add main entry point to the game
add_executable(${GAME_PROJECT_NAME} WIN32 main.cpp)

# link engine with executable
target_link_libraries(${GAME_PROJECT_NAME} PRIVATE TorcEngine)

add_dependencies(${GAME_PROJECT_NAME} TorcEngine GfxD3D11)

# in this case project name and folder names match
set_target_properties(${GAME_PROJECT_NAME} PROPERTIES FOLDER ${GAME_PROJECT_NAME})

