set(PUBLIC_FILES
    Public/Common/RHICommon.h
    Public/Common/Base.h

    Public/Object.h	
    Public/Factory.h

    Public/SwapChain.h
    Public/Device.h
    Public/HandleRegistry.h
    Public/ITorcGfxBackend.h
    Public/DeviceContext.h
    Public/RHIContext.h
    Public/Image.h
    Public/Resource.h
    Public/Pageable.h
    Public/DeviceChild.h
    Public/ResourceView.h
    Public/PipelineStateObject.h
    Public/RHITypeDesc.h
    Public/Descriptor.h
    Public/RHIEnumTypes.h
)

set(PRIVATE_FILES
    Private/Factory.cpp
    Private/SwapChain.cpp
    Private/Device.cpp

    Private/RHIContext.cpp
    Private/DeviceContext.cpp

    Private/Image.cpp
    Private/Resource.cpp
)