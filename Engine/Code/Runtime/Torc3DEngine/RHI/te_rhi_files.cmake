set(PUBLIC_FILES

    Public/RHI/RHIBase.h
    Public/RHI/RHIObject.h	
    Public/RHI/Factory.h

    Public/RHI/SwapChain.h
    Public/RHI/Device.h
    Public/RHI/HandleRegistry.h
    Public/RHI/ITorcGfxBackend.h
    Public/RHI/DeviceContext.h
    Public/RHI/RHIContext.h
    Public/RHI/Image.h
    Public/RHI/Resource.h
    Public/RHI/Pageable.h
    Public/RHI/DeviceChild.h
    Public/RHI/ResourceView.h
    Public/RHI/PipelineStateObject.h
    Public/RHI/RHITypeDesc.h
    Public/RHI/Descriptor.h
    Public/RHI/RHIEnumTypes.h
)

set(PRIVATE_FILES
    Private/RHI/Factory.cpp
    Private/RHI/SwapChain.cpp
    Private/RHI/Device.cpp

    Private/RHI/RHIContext.cpp
    Private/RHI/DeviceContext.cpp

    Private/RHI/Image.cpp
    Private/RHI/Resource.cpp
)