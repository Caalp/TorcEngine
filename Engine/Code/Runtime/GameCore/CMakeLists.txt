te_add_target(STATIC SOURCE_GROUP
    NAME
        GameCore
    NAMESPACE
        TE
    TARGET_PROPERTIES 
        FOLDER Engine/Code/Runtime/GameCore
    BUILD_DEPENDENCIES
       PRIVATE
           TE::Core
)