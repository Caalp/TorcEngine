#include "pch.h"
#include "IGPUResource.h"
#include "Renderer/Renderer.h"

IGPUResource::IGPUResource() 
	: m_underlyingType(nullptr)
{
}

IGPUResource::~IGPUResource()
{
	gEnv->rr->GetGFXBackend()->ReleaseResource(this);
}