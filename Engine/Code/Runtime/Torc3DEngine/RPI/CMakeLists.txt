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
            Public
        PRIVATE
            Public/RPI
    BUILD_DEPENDENCIES
        PUBLIC
            TE::Core
            TE::RHI.Public
        PRIVATE
            3rdParty::DirectXMath
)
