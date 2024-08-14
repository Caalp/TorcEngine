# GfxAPIs/D3D11/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")
# include("../te_rdi_files.cmake")
te_add_target(INTERFACE SOURCE_GROUP
    NAME
        RDICommon
    NAMESPACE
        TE
    FILES_CMAKE
        te_rdi_files.cmake   
    TARGET_PROPERTIES
        FOLDER Engine/Runtime/Graphics/RDI
        LINKER_LANGUAGE CXX
    INCLUDE_DIRECTORIES
        INTERFACE
            ../
)
