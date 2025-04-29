set(PUBLIC_FILES

	Public/RPI/Camera.h
	Public/RPI/IGPUResource.h
	Public/RPI/Renderer.h
	Public/RPI/rrPredefines.h
	
	Public/RPI/BlendState.h
	Public/RPI/Buffer.h
	Public/RPI/DepthStencilBuffer.h
	Public/RPI/DepthStencilState.h
	Public/RPI/InputLayout.h
	Public/RPI/PrimitiveTopology.h
	Public/RPI/RasterizerState.h
	Public/RPI/RenderTarget.h
	Public/RPI/SamplerState.h
	Public/RPI/Shader.h
	Public/RPI/Texture.h
	Public/RPI/TransformationBuffer.h
	
	#RenderGraph folder
	Public/RPI/FrameGraph/BindingPass.h
	Public/RPI/FrameGraph/Job.h
	Public/RPI/FrameGraph/Pass.h
	Public/RPI/FrameGraph/PassReflection.h
	Public/RPI/FrameGraph/RenderGraph.h
	Public/RPI/FrameGraph/RenderQueuePass.h
	Public/RPI/FrameGraph/Sink.h
	Public/RPI/FrameGraph/Source.h
	Public/RPI/FrameGraph/Step.h
	Public/RPI/FrameGraph/Technique.h
	
	#RenderPasses folder
	Public/RPI/Passes/MarkMirrorPass.h
	Public/RPI/Passes/MirrorReflectionPass.h
	Public/RPI/Passes/SkyBoxPass.h
)

set(PRIVATE_FILES
	Private/RPI/Camera.cpp
	Private/RPI/IGPUResource.cpp
	Private/RPI/Renderer.cpp
	
	#GPUObjects folder
	Private/RPI/BlendState.cpp
	Private/RPI/Buffer.cpp
	Private/RPI/DepthStencilBuffer.cpp
	Private/RPI/DepthStencilState.cpp
	Private/RPI/InputLayout.cpp
	Private/RPI/PrimitiveTopology.cpp
	Private/RPI/RasterizerState.cpp
	Private/RPI/RenderTarget.cpp
	Private/RPI/SamplerState.cpp
	Private/RPI/Shader.cpp
	Private/RPI/Texture.cpp
	Private/RPI/TransformationBuffer.cpp
	
	#RenderGraph folder
	Private/RPI/FrameGraph/BindingPass.cpp
	Private/RPI/FrameGraph/Job.cpp
	Private/RPI/FrameGraph/Pass.cpp
	Private/RPI/FrameGraph/PassReflection.cpp
	Private/RPI/FrameGraph/RenderGraph.cpp
	Private/RPI/FrameGraph/RenderQueuePass.cpp
	Private/RPI/FrameGraph/Sink.cpp
	Private/RPI/FrameGraph/Source.cpp
	Private/RPI/FrameGraph/Step.cpp
	Private/RPI/FrameGraph/Technique.cpp
	
	#RenderPasses folder
	Private/RPI/Passes/MarkMirrorPass.cpp
	Private/RPI/Passes/MirrorReflectionPass.cpp
	Private/RPI/Passes/SkyBoxPass.cpp
)
	