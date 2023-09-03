# Core/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/Memory")
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/Memory/Allocators")
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/Threading")
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/Plugins")
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/Logging")
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/Containers")
set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/IOStream")