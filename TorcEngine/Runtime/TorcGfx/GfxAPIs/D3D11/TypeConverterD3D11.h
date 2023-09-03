#pragma once
#include "TorcGfx/TorcGfxTypes.h"

// converts torc gfx types to target gfx backend types

namespace typeConverter
{
	D3D11_BLEND_OP ConvertTorcGfxType(gfx::TORC_GFX_BLEND_OP op);
	D3D11_BLEND ConvertTorcGfxType(gfx::TORC_GFX_BLEND op);
	D3D11_COLOR_WRITE_ENABLE ConvertTorcGfxType(gfx::TORC_GFX_COLOR_ENABLE op);
	D3D11_DEPTH_WRITE_MASK ConvertTorcGfxType(gfx::TORC_GFX_DEPTH_WRITE op);
	D3D11_COMPARISON_FUNC ConvertTorcGfxType(gfx::TORC_GFX_COMPARISON_FUNC op);
	D3D11_STENCIL_OP ConvertTorcGfxType(gfx::TORC_GFX_STENCIL_OP op);
	D3D11_FILL_MODE ConvertTorcGfxType(gfx::TORC_GFX_FILL_MODE op);
	D3D11_CULL_MODE ConvertTorcGfxType(gfx::TORC_GFX_CULL_MODE op);
	D3D11_USAGE ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_USAGE op);
	D3D11_BIND_FLAG ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_BIND_FLAG op);
	D3D11_CPU_ACCESS_FLAG ConvertTorcGfxType(gfx::TORC_GFX_CPU_ACCESS_FLAG op);
	D3D11_RESOURCE_MISC_FLAG ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_MISC_FLAG op);
	DXGI_FORMAT ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_DATA_FORMAT op);
	D3D11_FILTER ConvertTorcGfxType(gfx::TORC_GFX_FILTER op);
	D3D11_TEXTURE_ADDRESS_MODE ConvertTorcGfxType(gfx::TORC_GFX_TEXTURE_ADDRESS_MODE op);
};