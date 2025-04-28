message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(STATIC SOURCE_GROUP
    NAME
        RPI
    NAMESPACE
        TE
    FILES_CMAKE
        te_rpi_files.cmake
    TARGET_PROPERTIES
        FOLDER Engine/Code/Runtime/Torc3DEngine/RPI
    INCLUDE_DIRECTORIES
        PUBLIC
            ./Public/RPI
    BUILD_DEPENDENCIES
        PUBLIC
            TE::Core
        PRIVATE
            3rdParty::DirectXMath
)
