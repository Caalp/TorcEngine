# Renderer/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(STATIC SOURCE_GROUP
    NAME
        RPI
    NAMESPACE
        TE
    FILES_CMAKE
        te_graphics_files.cmake
    TARGET_PROPERTIES
        FOLDER Engine/Runtime/Graphics/RPI
    INCLUDE_DIRECTORIES
        PUBLIC
            .
    BUILD_DEPENDENCIES
        PUBLIC
            TE::Core
        PRIVATE
            3rdParty::DirectXMath
)
add_subdirectory(RHI)
