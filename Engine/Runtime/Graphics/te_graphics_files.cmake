set(FILES

	RPI/Camera.h
	RPI/Camera.cpp
	RPI/IGPUResource.h
	RPI/IGPUResource.cpp
	RPI/Renderer.h
	RPI/Renderer.cpp
	RPI/rrPredefines.h
	
	#GPUObjects folder
	RPI/GPUObjects/BlendState.cpp
	RPI/GPUObjects/BlendState.h
	RPI/GPUObjects/Buffer.cpp
	RPI/GPUObjects/Buffer.h
	RPI/GPUObjects/DepthStencilBuffer.cpp
	RPI/GPUObjects/DepthStencilBuffer.h
	RPI/GPUObjects/DepthStencilState.cpp
	RPI/GPUObjects/DepthStencilState.h
	RPI/GPUObjects/InputLayout.cpp
	RPI/GPUObjects/InputLayout.h
	RPI/GPUObjects/PrimitiveTopology.cpp
	RPI/GPUObjects/PrimitiveTopology.h
	RPI/GPUObjects/RasterizerState.cpp
	RPI/GPUObjects/RasterizerState.h
	RPI/GPUObjects/RenderTarget.cpp
	RPI/GPUObjects/RenderTarget.h
	RPI/GPUObjects/SamplerState.cpp
	RPI/GPUObjects/SamplerState.h
	RPI/GPUObjects/Shader.cpp
	RPI/GPUObjects/Shader.h
	RPI/GPUObjects/Texture.cpp
	RPI/GPUObjects/Texture.h
	RPI/GPUObjects/TransformationBuffer.cpp
	RPI/GPUObjects/TransformationBuffer.h
	
	#RenderGraph folder
	RPI/RenderGraph/BindingPass.cpp
	RPI/RenderGraph/BindingPass.h
	RPI/RenderGraph/Job.cpp
	RPI/RenderGraph/Job.h
	RPI/RenderGraph/Pass.cpp
	RPI/RenderGraph/Pass.h
	RPI/RenderGraph/PassReflection.cpp
	RPI/RenderGraph/PassReflection.h
	RPI/RenderGraph/RenderGraph.cpp
	RPI/RenderGraph/RenderGraph.h
	RPI/RenderGraph/RenderQueuePass.cpp
	RPI/RenderGraph/RenderQueuePass.h
	RPI/RenderGraph/Sink.cpp
	RPI/RenderGraph/Sink.h
	RPI/RenderGraph/Source.cpp
	RPI/RenderGraph/Source.h
	RPI/RenderGraph/Step.cpp
	RPI/RenderGraph/Step.h
	RPI/RenderGraph/Technique.cpp
	RPI/RenderGraph/Technique.h
	
	#RenderPasses folder
	RPI/RenderPasses/MarkMirrorPass.cpp
	RPI/RenderPasses/MarkMirrorPass.h
	RPI/RenderPasses/MirrorReflectionPass.cpp
	RPI/RenderPasses/MirrorReflectionPass.h
	RPI/RenderPasses/SkyBoxPass.cpp
	RPI/RenderPasses/SkyBoxPass.h
	)
	