#include "RPI/Passes/SkyBoxPass.h"
#include "RPI/DepthStencilBuffer.h"
#include "RPI/RenderTarget.h"

SkyBoxPass::SkyBoxPass(const PassDescriptor& desc)
	: RasterPass(desc)
{
}

Pass* SkyBoxPass::Create(const PassDescriptor& desc)
{
	return new SkyBoxPass(desc);
}

TEStd::RefCountedPtr<PassTemplate> SkyBoxPass::CreatePassTemplate()
{
	TEStd::RefCountedPtr<PassTemplate> temp = std::make_shared<PassTemplate>();
	temp->m_templateName = "SkyBoxPassTemplate";
	temp->m_passClassName = "SkyBoxPass";

	PassSlot s0;
	s0.m_slotName = "Backbuffer";
	s0.m_slotType = PassSlotType::Output;
	s0.m_slotUsage = PassSlotUsage::RenderTarget;

	PassSlot s1;
	s0.m_slotName = "DepthBuffer";
	s0.m_slotType = PassSlotType::Output;
	s0.m_slotUsage = PassSlotUsage::DepthStencil;

	PassConnection dc;
	PassConnection bc;

	dc.m_localSlotName = "DepthBuffer";
	dc.m_refSlotName = "DepthBuffer";
	dc.m_refPassName = "$";

	bc.m_localSlotName = "Backbuffer";
	bc.m_refSlotName = "$.Backbuffer";
	bc.m_refPassName = "$";

	temp->m_connections.push_back(dc);
	temp->m_connections.push_back(bc);

	temp->m_slots.push_back(s0);
	temp->m_slots.push_back(s1);

	PassSystemInterface::Get()->AddPassTemplate(temp);

	return temp;
}

void SkyBoxPass::Execute()
{
	RenderPass::Execute();
}

void SkyBoxPass::Reset()
{
	RenderPass::Reset();
}