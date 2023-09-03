#pragma once
#include "TorcGfx/TorcgfxTypes.h"
#include "TorcGfx/HandleRegistry.h"

#define MAX_HANDLE_COUNT_BLEND_STATE 100
#define MAX_HANDLE_COUNT_RASTERIZER_STATE 100
#define MAX_HANDLE_COUNT_SAMPLER_STATE 100
#define MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE 100
#define MAX_HANDLE_COUNT_RENDER_TARGET 8

namespace gfx
{
	class ITorcGfxBackend;

	struct BlendDesc;
	struct TextureDesc;
}

namespace Torc
{
	class Renderer
	{
		friend class ITorcgfxBackend;

		Renderer(gfx::GfxBackendParams& params);
		~Renderer();
	public:

		/**
		 * Takes parameters which are used to create and initialize swapchain and gfx backend.
		 * Function also internally creates and initalized pointers for device and context as well as loading the dll
		 * that contains specified backend.
		 * 
		 * @param params which contains necessary values that will be used for initializing rendering backend.
		 */
		static bool Initialize(gfx::GfxBackendParams& params);
		static Renderer* GetInstance();
		static void Release();

		BlendStateHandle CreateBlendState(const gfx::BlendDesc& params);
		RasterizerStateHandle CreateRasterizerState(const gfx::RasterizerDesc& params);
		SamplerStateHandle CreateSamplerState(const gfx::SamplerDesc& params);
		DepthStencilStateHandle CreateDepthStencilState(const gfx::DepthStencilDesc& params);

		void SetBlendState(BlendStateHandle handle, const float blendFactor[4], uint32_t blendMask);

	private:
		bool m_isInitialized;
		gfx::ITorcGfxBackend* m_gfxBackend;
		
		HandleRegistry<MAX_HANDLE_COUNT_BLEND_STATE> m_blendStateHandles;
		HandleRegistry<MAX_HANDLE_COUNT_RASTERIZER_STATE> m_rasterizerStateHandles;
		HandleRegistry<MAX_HANDLE_COUNT_SAMPLER_STATE> m_samplerStateHandles;
		HandleRegistry<MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE> m_depthStencilStateHandles;
	};
}