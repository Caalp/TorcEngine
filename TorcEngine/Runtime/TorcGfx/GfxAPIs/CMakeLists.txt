# Platform/TorcGfx/GfxAPIs/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

if("${gfx_backend_uppercase}" STREQUAL "D3D11")
	#set_target_sources("${TORC_ENGINE_LIB_STATIC}" "${CMAKE_CURRENT_SOURCE_DIR}/GfxAPIs/D3D11")
	
	add_library(GfxD3D11 SHARED)
	add_compile_definitions("GfxD3D11" TORC_DLL_EXPORT=1)
	# set_property(TARGET GfxD3D11 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
	# "${CMAKE_CURRENT_SOURCE_DIR}/D3D11")
	set_target_sources("GfxD3D11" "${CMAKE_CURRENT_SOURCE_DIR}/D3D11")
	#set_target_sources("GfxD3D11" "${CMAKE_CURRENT_SOURCE_DIR}/Common")
	#set_target_sources("GfxD3D11" "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
