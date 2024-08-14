# GameCore/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(STATIC SOURCE_GROUP
    NAME
        Asset
    NAMESPACE
        TE
    FILES_CMAKE
        te_asset_files.cmake
    TARGET_PROPERTIES 
        FOLDER Engine/Runtime/Asset
    BUILD_DEPENDENCIES
        PRIVATE
            TE::Core
        PUBLIC
            3rdParty::FreeImage
)
