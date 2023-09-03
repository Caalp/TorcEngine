# Common/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}")
add_as_sub_directory("${CMAKE_CURRENT_SOURCE_DIR}")