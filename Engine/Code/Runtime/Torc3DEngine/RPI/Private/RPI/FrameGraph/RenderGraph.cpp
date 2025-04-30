#include "RPI/FrameGraph/RenderGraph.h"
//#include "RenderQueuePass.h"
//#include "RPI/GPUObjects/DepthStencilBuffer.h"
//#include "RDI/RDIShared/ITorcGfxBackend.h"
//
//#include <Core/Std/String/string_utils.h>
//
//RenderGraph::RenderGraph() 
//	: m_backBuffer(gEnv->gfx->GetMainRT())
//	, m_depthBuffer(std::make_shared<OutputOnlyDepthBuffer>(gEnv->gfx->GetMainDepthBuffer()))
//{
//	AddGlobalSink(DirectBufferSink<RenderTarget>::Make("backbuffer", m_backBuffer));
//	AddGlobalSource(DirectBufferSource<RenderTarget>::Make("backbuffer", m_backBuffer));
//
//	AddGlobalSource(DirectBufferSource<DepthStencilBuffer>::Make("depthbuffer", m_depthBuffer));
//	AddGlobalSink(DirectBufferSink<DepthStencilBuffer>::Make("depthbuffer", m_depthBuffer));
//}
//
//RenderQueuePass* RenderGraph::GetRenderQueuePass(const char* passName)
//{
//	try
//	{
//		for (const auto& renderPass : m_passes)
//		{
//			if (string::utils::Equal(renderPass->GetName().c_str(), passName))
//			{
//				return dynamic_cast<RenderQueuePass*>(renderPass.get());
//			}
//		}
//	}
//	catch (std::bad_cast& e)
//	{
//		throw(e.what());
//	}
//	return nullptr;
//}
//
//void RenderGraph::AddGlobalSource(std::unique_ptr<Source> source)
//{
//	m_globalSources.emplace_back(std::move(source));
//}
//
//void RenderGraph::AddGlobalSink(std::unique_ptr<Sink> sink)
//{
//	m_globalSinks.emplace_back(std::move(sink));
//}
//
//Pass* RenderGraph::GetPassByName(const char* passName) const
//{
//	return nullptr;
//}
//
//void RenderGraph::AppendPass(std::unique_ptr<Pass> pass)
//{
//
//	
//}
//
//void RenderGraph::Execute()
//{
//	for (const auto& pass : m_passes)
//	{
//		pass->Execute();
//	}
//}
//
//void RenderGraph::Reset()
//{
//	for (const auto& p : m_passes)
//	{
//		p->Reset();
//	}
//}