# GfxAPIs/D3D11/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")
# include("../te_rdi_files.cmake")
te_add_target(SHARED SOURCE_GROUP
    NAME
        DX11
    NAMESPACE
        TE
    FILES_CMAKE
        te_d3d11_files.cmake
    COMPILE_DEFINITIONS
        PUBLIC
            TORC_DLL_EXPORT=1
    TARGET_PROPERTIES
        FOLDER Engine/Runtime/Graphics/RHI
        LINKER_LANGUAGE CXX
    INCLUDE_DIRECTORIES
        PUBLIC
            .
    BUILD_DEPENDENCIES
        PUBLIC
            TE::Core
            TE::RHI.Public
)
