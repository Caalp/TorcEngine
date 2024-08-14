te_add_target(EXECUTABLE SOURCE_GROUP
	NAME TestGame
		
	FILES_CMAKE
        testgame_files.cmake
    TARGET_PROPERTIES
        FOLDER TestGame
    INCLUDE_DIRECTORIES
        PUBLIC
            .
    BUILD_DEPENDENCIES
        PUBLIC
            #TE::Runtime.Static  # TE::Core, TE::Asset, TE::GameCore, TE::RPI
            TE::Core
            TE::Asset
            TE::GameCore
            TE::RPI
)