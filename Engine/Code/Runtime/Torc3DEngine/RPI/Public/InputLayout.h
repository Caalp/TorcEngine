#pragma once
#include "RPI/IGPUResource.h"

class InputLayout : public IGPUResource
{
public:
	virtual void* GetDesc() const override;
	virtual void Bind() override;
};