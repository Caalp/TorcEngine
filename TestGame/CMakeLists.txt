# include folders in TorcEngine folder

# folder to look for libraries
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# reset game project name
set(GAME_PROJECT_NAME "TestGame")

# add main entry point to the game
add_executable(${GAME_PROJECT_NAME} WIN32 main.cpp)

target_include_directories(${GAME_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/TorcEngine/Runtime)
target_include_directories(${GAME_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty)

# link engine with executable
target_link_libraries(${GAME_PROJECT_NAME} PRIVATE TorcEngine)

add_dependencies(${GAME_PROJECT_NAME} TorcEngine GfxD3D11)

# in this case project name and folder names match
set_target_properties(${GAME_PROJECT_NAME} PROPERTIES FOLDER ${GAME_PROJECT_NAME})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tests)