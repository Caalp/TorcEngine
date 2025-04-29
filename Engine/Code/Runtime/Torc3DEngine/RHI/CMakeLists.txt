message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

te_add_target(STATIC SOURCE_GROUP
    NAME
        RHI.Public
    NAMESPACE
        TE
    FILES_CMAKE
        te_rhi_files.cmake   
    TARGET_PROPERTIES
        FOLDER Engine/Code/Runtime/Torc3DEngine/RHI
        LINKER_LANGUAGE CXX
    INCLUDE_DIRECTORIES
        PUBLIC
            Public
        PRIVATE
            Public/RHI
	BUILD_DEPENDENCIES
        PUBLIC
            TE::Core
)
