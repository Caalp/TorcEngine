# GameCore/CMakeLists.txt

te_add_target(STATIC SOURCE_GROUP
    NAME
        GameCore
    NAMESPACE
        TE
    FILES_CMAKE
        te_gamecore_files.cmake
    TARGET_PROPERTIES 
        FOLDER Engine/Runtime/GameCore
    BUILD_DEPENDENCIES
        PRIVATE
            TE::Core
)