# UnitTests/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_LIST_DIR}")

te_add_target(EXECUTABLE CONSOLE_APPLICATION SOURCE_GROUP
    NAME
        UnitTests
    FILES_CMAKE
        te_unittests_files.cmake
    TARGET_PROPERTIES 
        FOLDER Engine/Runtime/UnitTests
    BUILD_DEPENDENCIES
        PRIVATE
            TE::Core
			3rdParty::Catch2
)