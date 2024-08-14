# Launcher/CMakeLists.txt

te_add_target(STATIC SOURCE_GROUP
    NAME
        Launcher
    NAMESPACE
        TE
    FILES_CMAKE
        te_launcher_files.cmake
    TARGET_PROPERTIES 
        FOLDER Engine/Runtime/Launcher
    BUILD_DEPENDENCIES
        PRIVATE
            TE::Core
            
)
