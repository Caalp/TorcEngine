# Core/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(STATIC SOURCE_GROUP
    NAME
        Core
    NAMESPACE
        TE
    FILES_CMAKE
        te_core_files.cmake
    TARGET_PLATFORM_FILES_CMAKE
        # inside the platform specific .cmake file, give abs path to sources, because we add sources
        # directly without going into subdir. If we give relative path, cmake can't locate them.
        # This can be fixed in the future if needed in te_add_target function.
        Platform/${TARGET_PLATFORM}/te_platform_${TARGET_PLATFORM_LOWERCASE}_files.cmake
    TARGET_PROPERTIES
        FOLDER Engine/Runtime/Core
    INCLUDE_DIRECTORIES
        PUBLIC
            ../
            Platform/${TARGET_PLATFORM}
    BUILD_DEPENDENCIES
        PUBLIC
            3rdParty::DirectXMath
            3rdParty::RapidJSON
            3rdParty::CityHash
)
