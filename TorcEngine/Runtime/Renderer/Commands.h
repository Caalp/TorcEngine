#pragma once

#include "Renderer/Renderer.h"
#include "TorcGfx/ITorcGfxBackend.h"

typedef void(*BackendDispatchFunction)(const void*);

namespace command
{
	struct Draw
	{
		static const BackendDispatchFunction backendDispatchFunc;
		uint32_t startIndex;
		uint32_t indexCount;
	};

	struct DrawIndexed
	{
		static const BackendDispatchFunction backendDispatchFunc;
		uint32_t startIndex;
		uint32_t indexCount;
	};

	struct CopyVertexBuffer
	{
		static const BackendDispatchFunction backendDispatchFunc;
		// VertexBufferHandle;
		// void* data;
	};

	struct SetStates
	{
		RasterizerStateHandle rasterizerStateHandle;
		DepthStencilStateHandle depthStencilStateHandle;

		BlendStateHandle blendStateHandle;
		float blendFactor[4];
		uint32_t blendMask;
	};
}


namespace backendDispatch
{
	void Draw(const void* data)
	{
		const command::Draw* realData = reinterpret_cast<const command::Draw*>(data);
		// rr::SetVertexBuffer
		// rr::SetMaterial
		// rr::SetSamplerState
		// rr::SetRasterizerState
		// rr::Draw(startIndex, indexCount);
	}
	void DrawIndexed(const void* data)
	{

	}

	void CopyVertexBuffer(const void* data)
	{

	}
	
	void SetStates(const void* data)
	{
		const command::SetStates* ptr = reinterpret_cast<const command::SetStates*>(data);
		Torc::Renderer* rr = Torc::Renderer::GetInstance();
		if (IsValid(ptr->blendStateHandle))
		{
			rr->SetBlendState(ptr->blendStateHandle, ptr->blendFactor, ptr->blendMask);
		}
		/*if (IsValid(ptr->depthStencilStateHandle))
		{
			
		}*/
	}
}


const BackendDispatchFunction command::DrawIndexed::backendDispatchFunc = &(backendDispatch::DrawIndexed);
const BackendDispatchFunction command::Draw::backendDispatchFunc = &(backendDispatch::Draw);
const BackendDispatchFunction command::CopyVertexBuffer::backendDispatchFunc = &(backendDispatch::CopyVertexBuffer);
