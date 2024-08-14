#include "RPI/IGPUResource.h"
#include "Renderer.h"

IGPUResource::IGPUResource() 
	: m_underlyingType(nullptr)
	, m_gfx(gEnv->gfx)
{
}

IGPUResource::~IGPUResource()
{
	gEnv->rr->GetGFXBackend()->ReleaseResource(this);
}

ResourceDescID::IDType ResourceDescID::GetID(const gfx::BlendDesc& bsDesc)
{
	ResourceDescID::RDID_BS idBS{ 0 };
	idBS.resourceType = ResourceDescID::ResourceType::BS;
	idBS.enabled = bsDesc.blendEnable;
	idBS.alphaToCoverageEnabled = bsDesc.alphaToCoverageEnable;
	idBS.independentBlend = bsDesc.independentBlendEnable;
	idBS.src = (ResourceDescID::IDType)bsDesc.srcBlend;
	idBS.dst = (ResourceDescID::IDType)bsDesc.destBlend;
	idBS.op = (ResourceDescID::IDType)bsDesc.blendOp;
	idBS.srcAlpha = (ResourceDescID::IDType)bsDesc.srcBlendAlpha;
	idBS.dstAlpha = (ResourceDescID::IDType)bsDesc.destBlendAlpha;
	idBS.opAlpha = (ResourceDescID::IDType)bsDesc.blendOpAlpha;
	idBS.colorEnable = (ResourceDescID::IDType)bsDesc.rtWriteMask;

	return idBS.id;
}

ResourceDescID::IDType ResourceDescID::GetID(const gfx::DepthStencilDesc& dssDesc)
{
	ResourceDescID::RDID_DSS idDSS{ 0 };
	idDSS.resourceType = ResourceDescID::ResourceType::DSS;
	idDSS.depthEnable = (ResourceDescID::IDType)dssDesc.depthEnable;
	idDSS.depthWrite = (ResourceDescID::IDType)dssDesc.depthWrite;
	idDSS.depthFunc = (ResourceDescID::IDType)dssDesc.depthFunc;
	idDSS.stencilEnable = (ResourceDescID::IDType)dssDesc.stencilEnable;
	idDSS.stencilReadMask = (ResourceDescID::IDType)dssDesc.stencilReadMask;
	idDSS.stencilWriteMask = (ResourceDescID::IDType)dssDesc.stencilWriteMask;
	idDSS.frontFace = (ResourceDescID::IDType)((uint16)dssDesc.frontFace.stencilFailOp |
											   (uint16)dssDesc.frontFace.stencilDepthFailOp << 3 |
											   (uint16)dssDesc.frontFace.stencilPassOp << 6 |
											   (uint16)dssDesc.frontFace.stencilFunc << 9);
	idDSS.backFace = (ResourceDescID::IDType)((uint16)dssDesc.backFace.stencilFailOp |
											  (uint16)dssDesc.backFace.stencilDepthFailOp << 3 |
											  (uint16)dssDesc.backFace.stencilPassOp << 6 |
											  (uint16)dssDesc.backFace.stencilFunc << 9);

	return idDSS.id;
}

ResourceDescID::IDType ResourceDescID::GetID(const gfx::RasterizerDesc& rsDesc)
{
	ResourceDescID::RDID_RS idRS{ 0 };
	idRS.resourceType = ResourceDescID::ResourceType::RS;
	idRS.cullMode = (ResourceDescID::IDType)rsDesc.cullMode;
	idRS.fillMode = (ResourceDescID::IDType)rsDesc.fillMode;
	idRS.frontCCW = (ResourceDescID::IDType)rsDesc.frontCCW;
	idRS.depthClipEnable = (ResourceDescID::IDType)rsDesc.depthClipEnable;
	idRS.scissorEnable = (ResourceDescID::IDType)rsDesc.scissorEnable;
	idRS.multisampleEnable = (ResourceDescID::IDType)rsDesc.multisampleEnable;
	idRS.antialiasedLineEnable = (ResourceDescID::IDType)rsDesc.antialiasedLineEnable;

	return idRS.id;
}

ResourceDescID::IDType ResourceDescID::GetID(const gfx::SamplerDesc& ssDesc)
{
	ResourceDescID::RDID_SS idSS{ 0 };
	idSS.resourceType = ResourceDescID::ResourceType::SS;
	idSS.filter = (ResourceDescID::IDType)ssDesc.filter;
	idSS.addressU = (ResourceDescID::IDType)ssDesc.addressU;
	idSS.addressV = (ResourceDescID::IDType)ssDesc.addressV;
	idSS.addressW = (ResourceDescID::IDType)ssDesc.addressW;
	idSS.comparisonFunc = (ResourceDescID::IDType)ssDesc.comparisonFunc;
	return idSS.id;
}

ResourceDescID::ResourceType ResourceDescID::GetResourceType(const IDType id)
{
	return (ResourceDescID::ResourceType)((((ResourceDescID::IDType)0xf << 60) & id) >> 60);
}