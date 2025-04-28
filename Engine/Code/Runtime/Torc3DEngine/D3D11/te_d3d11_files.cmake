set(PUBLIC_FILES

	# Public folder
	Public/base.h
	Public/D3D11Common.h
	Public/ShaderD3D11.h
	Public/DX11Module.h
	Public/GfxBackendD3D11.h
	Public/SwapChain_DX11.h
	Public/Factory_DX11.h
	Public/Device_DX11.h
	Public/RHITypeConverter.h
	Public/DeviceContext_DX11.h
	Public/Image_DX11.h
	Public/SystemComponent.h
	
)

set (PRIVATE_FILES
	
	# Private folder
	Private/SwapChain_DX11.cpp
	Private/Factory_DX11.cpp
	Private/Device_DX11.cpp
	Private/RHITypeConverter.cpp
	Private/DeviceContext_DX11.cpp
	Private/Image_DX11.cpp
	Private/GfxBackendD3D11.cpp
	Private/ShaderD3D11.cpp
	Private/DX11Module.cpp
	Private/SystemComponent.cpp
)