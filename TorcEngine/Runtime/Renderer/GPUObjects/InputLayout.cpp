#include "pch.h"
#include "InputLayout.h"

void* InputLayout::GetDesc() const
{
	return NULL;
}

void InputLayout::Bind()
{
	LOG_INFO(LogChannel::LC_Renderer, "InputLayout::Bind");
}