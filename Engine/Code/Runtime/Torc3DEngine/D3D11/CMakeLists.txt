message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(SHARED SOURCE_GROUP
    NAME
        D3D11
    NAMESPACE
        TE
    FILES_CMAKE
        te_d3d11_files.cmake
    COMPILE_DEFINITIONS
        PUBLIC
            TORC_DLL_EXPORT=1
    TARGET_PROPERTIES
        FOLDER Engine/Code/Runtime/Torc3DEngine/D3D11
        LINKER_LANGUAGE CXX
    INCLUDE_DIRECTORIES
        PUBLIC
            Public
    BUILD_DEPENDENCIES
        PRIVATE
            TE::Core
            TE::RHI.Public
)
