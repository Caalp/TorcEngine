# Platform/TorcGfx/GfxAPIs/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(STATIC SOURCE_GROUP
    NAME
        RHI.Public
    NAMESPACE
        TE
    FILES_CMAKE
        rhi_files.cmake   
    TARGET_PROPERTIES
        FOLDER Engine/Runtime/Graphics/RHI
        LINKER_LANGUAGE CXX
    INCLUDE_DIRECTORIES
        PUBLIC
            ../
	BUILD_DEPENDENCIES
        PUBLIC
            TE::Core
)

add_subdirectory(DX11)