set(PUBLIC_FILES

	Public/Camera.h
	Public/IGPUResource.h
	Public/Renderer.h
	Public/rrPredefines.h
	
	Public/BlendState.h
	Public/Buffer.h
	Public/DepthStencilBuffer.h
	Public/DepthStencilState.h
	Public/InputLayout.h
	Public/PrimitiveTopology.h
	Public/RasterizerState.h
	Public/RenderTarget.h
	Public/SamplerState.h
	Public/Shader.h
	Public/Texture.h
	Public/TransformationBuffer.h
	
	#RenderGraph folder
	Public/FrameGraph/BindingPass.h
	Public/FrameGraph/Job.h
	Public/FrameGraph/Pass.h
	Public/FrameGraph/PassReflection.h
	Public/FrameGraph/RenderGraph.h
	Public/FrameGraph/RenderQueuePass.h
	Public/FrameGraph/Sink.h
	Public/FrameGraph/Source.h
	Public/FrameGraph/Step.h
	Public/FrameGraph/Technique.h
	
	#RenderPasses folder
	Public/Passes/MarkMirrorPass.h
	Public/Passes/MirrorReflectionPass.h
	Public/Passes/SkyBoxPass.h
)

set(PRIVATE_FILES
	Private/Camera.cpp
	Private/IGPUResource.cpp
	Private/Renderer.cpp
	
	#GPUObjects folder
	Private/BlendState.cpp
	Private/Buffer.cpp
	Private/DepthStencilBuffer.cpp
	Private/DepthStencilState.cpp
	Private/InputLayout.cpp
	Private/PrimitiveTopology.cpp
	Private/RasterizerState.cpp
	Private/RenderTarget.cpp
	Private/SamplerState.cpp
	Private/Shader.cpp
	Private/Texture.cpp
	Private/TransformationBuffer.cpp
	
	#RenderGraph folder
	Private/FrameGraph/BindingPass.cpp
	Private/FrameGraph/Job.cpp
	Private/FrameGraph/Pass.cpp
	Private/FrameGraph/PassReflection.cpp
	Private/FrameGraph/RenderGraph.cpp
	Private/FrameGraph/RenderQueuePass.cpp
	Private/FrameGraph/Sink.cpp
	Private/FrameGraph/Source.cpp
	Private/FrameGraph/Step.cpp
	Private/FrameGraph/Technique.cpp
	
	#RenderPasses folder
	Private/Passes/MarkMirrorPass.cpp
	Private/Passes/MirrorReflectionPass.cpp
	Private/Passes/SkyBoxPass.cpp
)
	