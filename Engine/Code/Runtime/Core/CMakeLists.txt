# Core/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(STATIC SOURCE_GROUP
    NAME
        Core
    NAMESPACE
        TE
    TARGET_PROPERTIES
        FOLDER Engine/Code/Runtime/Core
    INCLUDE_DIRECTORIES
        PUBLIC
            ./Private/Platform/${TARGET_PLATFORM}
    BUILD_DEPENDENCIES
        PUBLIC
            3rdParty::DirectXMath
            3rdParty::RapidJSON
            3rdParty::CityHash
            3rdParty::FreeImage
)
