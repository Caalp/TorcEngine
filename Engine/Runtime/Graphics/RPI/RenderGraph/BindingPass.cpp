#include "BindingPass.h"

BindingPass::BindingPass(const char* passName) 
	: Pass(passName)
{}

//void BindingPass::AddBind(std::unique_ptr<Bindable> bind)
//{
//	binds.push_back(std::move(bind));
//}

void BindingPass::BindAll()
{
	//// Bind buffers first either depth or renderTarget
	//BindBufferResources(gfx);
	//for (const auto& binding : binds)
	//{
	//	binding->Bind(gfx);
	//}
}

void BindingPass::BindBufferResources()
{
	//// If renderTarget is not 
	//if (renderTarget)
	//{
	//	renderTarget->BindAsBuffer(gfx, &(*depthStencil));
	//}
	//else
	//{
	//	// only set the depth-stencil itself
	//	depthStencil->BindAsBuffer(gfx);
	//}
}
