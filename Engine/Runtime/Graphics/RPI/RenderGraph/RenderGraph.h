#pragma once
#include "Pass.h"

#include <vector>
#include <memory>

class RenderQueuePass;
class Source;
class Sink;
class Pass;

class RenderTarget;
class DepthStencilBuffer;

class RenderGraph
{
public:
	RenderGraph();
	RenderQueuePass* GetRenderQueuePass(const char* passName);
	void AddGlobalSource(std::unique_ptr<Source> source);
	void AddGlobalSink(std::unique_ptr<Sink> sink);
	//std::vector<std::unique_ptr<Sink>>& GetSink(Pass& p) const;
	Pass* GetPassByName(const char* passName) const;
	void AppendPass(std::unique_ptr<Pass> pass);
	void Execute();
	void Reset();
private:
	std::shared_ptr<RenderTarget> m_backBuffer;
	std::shared_ptr<DepthStencilBuffer> m_depthBuffer;
private:
	std::vector<std::unique_ptr<Pass>> m_passes;
	std::vector<std::unique_ptr<Sink>> m_globalSinks;
	std::vector<std::unique_ptr<Source>> m_globalSources;
};