#include "Passes/MarkMirrorPass.h"

MarkMirrorPass::MarkMirrorPass(const char* passName) 
	: RenderQueuePass(passName)
{
	//RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
	/*RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	AddBind(std::make_unique<BlendState>(gfx, true,BlendState::BlendType::NoRenderTargetWrite));
	AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::Mirror));
	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::Default));*/
}

void MarkMirrorPass::Execute()
{
	RenderQueuePass::Execute();
}

void MarkMirrorPass::Reset()
{
	RenderQueuePass::Reset();
}