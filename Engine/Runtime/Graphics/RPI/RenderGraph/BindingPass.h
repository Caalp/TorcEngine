#pragma once
#include "Pass.h"

class RenderTarget;
class DepthStencilBuffer;

class BindingPass : public Pass
{
public:
	BindingPass(const char* passName);
	//void AddBind(std::unique_ptr<Bindable> bind);
	void BindAll();
protected:
	std::shared_ptr<RenderTarget> renderTarget;
	std::shared_ptr<DepthStencilBuffer> depthStencil;

private:
	void BindBufferResources();
private:
//	std::vector<std::unique_ptr<Bindable>> binds;
};