set(FILES
	
	D3D11Common.h
	GfxBackendD3D11.h
	GfxBackendD3D11.cpp
	ShaderD3D11.h
	ShaderD3D11.cpp
	DX11Module.h
	DX11Module.cpp
	SystemComponent.h
	SystemComponent.cpp

	# Include folder
	Include/base.h
 
	# Public folder
	Public/SwapChain_DX11.h
	Public/Factory_DX11.h
	Public/Device_DX11.h
	Public/RHITypeConverter.h
	Public/DeviceContext_DX11.h

	# Source folder
	Source/SwapChain_DX11.cpp
	Source/Factory_DX11.cpp
	Source/Device_DX11.cpp
	Source/RHITypeConverter.cpp
	Source/DeviceContext_DX11.cpp
)