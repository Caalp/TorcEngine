# Launcher/CMakeLists.txt

te_add_target(STATIC SOURCE_GROUP
    NAME
        Launcher
    NAMESPACE
        TE
    TARGET_PROPERTIES 
        FOLDER Engine/Code/Launcher
    BUILD_DEPENDENCIES
        PRIVATE
            TE::Core            
)
