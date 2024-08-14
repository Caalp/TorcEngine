# TorcEngine/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Core)
add_subdirectory(GameCore)
add_subdirectory(Graphics)
add_subdirectory(Asset)
add_subdirectory(Launcher)

# te_add_target(INTERFACE SOURCE_GROUP
#     NAME
#         Runtime.Static
#     NAMESPACE
#         TE
#     TARGET_PROPERTIES 
#         FOLDER Engine/Runtime
#     BUILD_DEPENDENCIES
#         INTERFACE
# 			TE::Core
# 			TE::GameCore
# 			TE::RPI
# 			TE::Asset
# )

# add_custom_command(
#       TARGET "${TORC_ENGINE_LIB_STATIC}"
# 		PRE_BUILD
# 		COMMAND python "${CMAKE_SOURCE_DIR}/Config/Build/CMake/collect_files.py"
# 		COMMENT "Collecting files for this target:"
# )
