
# set a cached variable 
set(GFX_BACKEND "Cached variable for gfx backend options" CACHE STRING "gfx backend description")

# convert string to both lower and upper case, no matter what mentioned during compilation
# user lowercase while doing string comparison
string(TOUPPER "${GFX_BACKEND}" gfx_backend_uppercase)

# check and set appropriate compile flag
if("${gfx_backend_uppercase}" STREQUAL "D3D11")
	message(STATUS "Compiling with ${gfx_backend_uppercase}")
	add_compile_definitions(GAME_PROJECT_NAME USE_D3D11_GFX_BACKEND=1)
elseif("${gfx_backend_uppercase}" STREQUAL "D3D12")
	message(STATUS "Compiling with ${gfx_backend_uppercase}")
	add_compile_definitions(GAME_PROJECT_NAME USE_D3D12_GFX_BACKEND=1)
endif()


