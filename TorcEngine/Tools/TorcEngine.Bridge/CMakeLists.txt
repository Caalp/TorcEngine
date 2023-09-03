file(GLOB_RECURSE bridge_headers CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

file(GLOB_RECURSE bridge_sources CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(TorcEngine.Bridge SHARED ${bridge_sources} ${bridge_headers})
set_target_properties(TorcEngine.Bridge PROPERTIES FOLDER "Tools")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${bridge_headers} ${bridge_sources} )