#pragma once
#include "TorcGfx/TorcGfxTypes.h"

class IGPUResource
{
public:
	IGPUResource();
	virtual ~IGPUResource();

	virtual void* GetDesc() const = 0;
	virtual void Bind() = 0;
	void* m_underlyingType;
};