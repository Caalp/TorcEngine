#pragma once
#include "D3D11/D3D11TypeConverter.h"
#include "D3D11/D3D11Common.h"

//D3D11_BLEND_OP typeConverter::ConvertTorcGfxType(TORC_GFX_BLEND_OP op)
//{
//	switch (op)
//	{
//	case TORC_GFX_BLEND_OP::ADD:
//		return D3D11_BLEND_OP_ADD;
//	case TORC_GFX_BLEND_OP::SUBTRACT:
//		return D3D11_BLEND_OP_SUBTRACT;
//	case TORC_GFX_BLEND_OP::REV_SUBTRACT:
//		return D3D11_BLEND_OP_REV_SUBTRACT;
//	case TORC_GFX_BLEND_OP::MIN:
//		return D3D11_BLEND_OP_MIN;
//	case TORC_GFX_BLEND_OP::MAX:
//		return D3D11_BLEND_OP_MAX;
//	default:
//		return D3D11_BLEND_OP_ADD;
//	}
//}
//
//D3D11_BLEND typeConverter::ConvertTorcGfxType(TORC_GFX_BLEND op)
//{
//	switch (op)
//	{
//	case TORC_GFX_BLEND::ZERO:
//		return D3D11_BLEND::D3D11_BLEND_ZERO;
//	case TORC_GFX_BLEND::ONE:
//		return D3D11_BLEND::D3D11_BLEND_ONE;
//	case TORC_GFX_BLEND::SRC_COLOR:
//		return D3D11_BLEND::D3D11_BLEND_SRC_COLOR;
//	case TORC_GFX_BLEND::INV_SRC_COLOR:
//		return D3D11_BLEND::D3D11_BLEND_INV_SRC_COLOR;
//	case TORC_GFX_BLEND::SRC_ALPHA:
//		return D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
//	case TORC_GFX_BLEND::INV_SRC_ALPHA:
//		return D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
//	case TORC_GFX_BLEND::DEST_ALPHA:
//		return D3D11_BLEND::D3D11_BLEND_DEST_ALPHA;
//	case TORC_GFX_BLEND::INV_DEST_ALPHA:
//		return D3D11_BLEND::D3D11_BLEND_INV_DEST_ALPHA;
//	case TORC_GFX_BLEND::DEST_COLOR:
//		return D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
//	case TORC_GFX_BLEND::INV_DEST_COLOR:
//		return D3D11_BLEND::D3D11_BLEND_INV_DEST_COLOR;
//	case TORC_GFX_BLEND::SRC_ALPHA_SAT:
//		return D3D11_BLEND::D3D11_BLEND_SRC_ALPHA_SAT;
//	case TORC_GFX_BLEND::BLEND_FACTOR:
//		return D3D11_BLEND::D3D11_BLEND_BLEND_FACTOR;
//	case TORC_GFX_BLEND::INV_BLEND_FACTOR:
//		return D3D11_BLEND::D3D11_BLEND_INV_BLEND_FACTOR;
//	case TORC_GFX_BLEND::SRC1_COLOR:
//		return D3D11_BLEND::D3D11_BLEND_SRC1_COLOR;
//	case TORC_GFX_BLEND::INV_SRC1_COLOR:
//		return D3D11_BLEND::D3D11_BLEND_INV_SRC1_COLOR;
//	case TORC_GFX_BLEND::SRC1_ALPHA:
//		return D3D11_BLEND::D3D11_BLEND_SRC1_ALPHA;
//	case TORC_GFX_BLEND::INV_SRC1_ALPHA:
//		return D3D11_BLEND::D3D11_BLEND_INV_SRC1_ALPHA;	
//	default:
//		return D3D11_BLEND::D3D11_BLEND_ZERO;
//	}
//}
//
//uint32 typeConverter::ConvertTorcGfxType(TORC_GFX_COLOR_ENABLE op)
//{
//	switch (op)
//	{
//	case TORC_GFX_COLOR_ENABLE::NONE:
//		return 0;
//	case TORC_GFX_COLOR_ENABLE::RED:
//		return D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_RED;
//	case TORC_GFX_COLOR_ENABLE::GREEN:
//		return D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_GREEN;
//	case TORC_GFX_COLOR_ENABLE::BLUE:
//		return D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_BLUE;
//	case TORC_GFX_COLOR_ENABLE::ALPHA:
//		return D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALPHA;
//	case TORC_GFX_COLOR_ENABLE::ALL:
//		return D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
//	default:
//		return D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
//	}
//}
//
//D3D11_DEPTH_WRITE_MASK typeConverter::ConvertTorcGfxType(TORC_GFX_DEPTH_WRITE op)
//{
//	switch (op)
//	{
//	case TORC_GFX_DEPTH_WRITE::NONE:
//		return D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
//	case TORC_GFX_DEPTH_WRITE::ALL:
//		return D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
//	default:
//		return D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
//	}
//}
//
//D3D11_COMPARISON_FUNC typeConverter::ConvertTorcGfxType(TORC_GFX_COMPARISON_FUNC op)
//{
//	switch (op)
//	{
//	case TORC_GFX_COMPARISON_FUNC::NEVER:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
//	case TORC_GFX_COMPARISON_FUNC::LESS:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
//	case TORC_GFX_COMPARISON_FUNC::EQUAL:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_EQUAL;
//	case TORC_GFX_COMPARISON_FUNC::LESS_EQUAL:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
//	case TORC_GFX_COMPARISON_FUNC::GREATER:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
//	case TORC_GFX_COMPARISON_FUNC::NOT_EQUAL:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NOT_EQUAL;
//	case TORC_GFX_COMPARISON_FUNC::GREATER_EQUAL:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER_EQUAL;
//	case TORC_GFX_COMPARISON_FUNC::ALWAYS:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
//	default:
//		return D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
//	}
//}
//
//D3D11_STENCIL_OP typeConverter::ConvertTorcGfxType(TORC_GFX_STENCIL_OP op)
//{
//	switch (op)
//	{
//	case TORC_GFX_STENCIL_OP::KEEP:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
//	case TORC_GFX_STENCIL_OP::ZERO:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_ZERO;
//	case TORC_GFX_STENCIL_OP::REPLACE:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_REPLACE;
//	case TORC_GFX_STENCIL_OP::INCR_SAT:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_INCR_SAT;
//	case TORC_GFX_STENCIL_OP::DECR_SAT:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_DECR_SAT;
//	case TORC_GFX_STENCIL_OP::INVERT:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_INVERT;
//	case TORC_GFX_STENCIL_OP::INCR:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_INCR;
//	case TORC_GFX_STENCIL_OP::DECR:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_DECR;
//	default:
//		return D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
//	}
//}
//
//D3D11_FILL_MODE typeConverter::ConvertTorcGfxType(TORC_GFX_FILL_MODE op)
//{
//	switch (op)
//	{
//	case TORC_GFX_FILL_MODE::WIREFRAME:
//		return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
//	case TORC_GFX_FILL_MODE::SOLID:
//		return D3D11_FILL_MODE::D3D11_FILL_SOLID;
//	default:
//		return D3D11_FILL_MODE::D3D11_FILL_SOLID;
//	}
//}
//
//D3D11_CULL_MODE typeConverter::ConvertTorcGfxType(TORC_GFX_CULL_MODE op)
//{
//	switch (op)
//	{
//	case TORC_GFX_CULL_MODE::NONE:
//		return D3D11_CULL_MODE::D3D11_CULL_NONE;
//	case TORC_GFX_CULL_MODE::FRONT:
//		return D3D11_CULL_MODE::D3D11_CULL_FRONT;
//	case TORC_GFX_CULL_MODE::BACK:
//		return D3D11_CULL_MODE::D3D11_CULL_BACK;
//	default:
//		return D3D11_CULL_MODE::D3D11_CULL_BACK;
//	}
//}
//
//D3D11_USAGE typeConverter::ConvertTorcGfxType(TORC_GFX_RESOURCE_USAGE op)
//{
//	switch (op)
//	{
//	case TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ_AND_WRITE:
//		return D3D11_USAGE::D3D11_USAGE_DEFAULT;
//	case TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ:
//		return D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
//	case TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ_CPU_WRITE:
//		return D3D11_USAGE::D3D11_USAGE_DYNAMIC;
//	case TORC_GFX_RESOURCE_USAGE::USAGE_GPU_CPU_READ_WRITE:
//		return D3D11_USAGE::D3D11_USAGE_STAGING;
//	default:
//		return D3D11_USAGE::D3D11_USAGE_DEFAULT;
//	}
//}
//
//uint32 typeConverter::ConvertTorcGfxType(uint32 op)
//{
//	uint32 bindFlag = 0;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_VERTEX_BUFFER) ? D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_INDEX_BUFFER) ? D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_CONSTANT_BUFFER) ? D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_SHADER_RESOURCE) ? D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_STREAM_OUTPUT) ? D3D11_BIND_FLAG::D3D11_BIND_STREAM_OUTPUT : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_RENDER_TARGET) ? D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_DEPTH_STENCIL) ? D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_UNORDERED_ACCESS) ? D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_DECODER) ? D3D11_BIND_FLAG::D3D11_BIND_DECODER : 0u;
//	bindFlag |= (op & TORC_GFX_RESOURCE_BIND_FLAG::BIND_VIDEO_ENCODER) ? D3D11_BIND_FLAG::D3D11_BIND_VIDEO_ENCODER : 0u;
//
//	return bindFlag;
//}
//
////NOTE(cagri): Flags can be combined
//uint32 typeConverter::ConvertTorcGfxType(gfx::TORC_GFX_CPU_ACCESS_FLAG op)
//{
//	uint32 flag = 0;
//	flag |= (op & TORC_GFX_CPU_ACCESS_FLAG::CPU_ACCESS_WRITE) ? D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE : 0u;
//	flag |= (op & TORC_GFX_CPU_ACCESS_FLAG::CPU_ACCESS_READ) ? D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ : 0u;
//	return flag;
//}
//
////NOTE(cagri): Flags can be combined
//D3D11_RESOURCE_MISC_FLAG typeConverter::ConvertTorcGfxType(TORC_GFX_RESOURCE_MISC_FLAG op)
//{
//	uint32 flag = 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_GENERATE_MIPS) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_SHARED) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_SHARED : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_TEXTURECUBE) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_TEXTURECUBE : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_DRAWINDIRECT_ARGS) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_BUFFER_STRUCTURED) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_SHARED_KEYEDMUTEX) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_GDI_COMPATIBLE) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_GDI_COMPATIBLE : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_SHARED_NTHANDLE) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_SHARED_NTHANDLE : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_RESTRICTED_CONTENT) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_RESTRICTED_CONTENT : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_RESTRICT_SHARED_RESOURCE) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_GUARDED) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_GUARDED : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_TILE_POOL) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_TILE_POOL : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_TILED) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_TILED : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_HW_PROTECTED) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_HW_PROTECTED : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_SHARED_DISPLAYABLE) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_SHARED_DISPLAYABLE : 0;
//	flag |= (op == TORC_GFX_RESOURCE_MISC_FLAG::RESOURCE_MISC_SHARED_EXCLUSIVE_WRITER) ? D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_SHARED_EXCLUSIVE_WRITER : 0;
//	return (D3D11_RESOURCE_MISC_FLAG)flag;
//}
//
//DXGI_FORMAT typeConverter::ConvertTorcGfxType(Format op)
//{
//	
//}
//
//D3D11_FILTER typeConverter::ConvertTorcGfxType(TORC_GFX_FILTER op)
//{
//	switch (op)
//	{
//	case TORC_GFX_FILTER::FILTER_MIN_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MIN_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MIN_POINT_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MIN_LINEAR_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MIN_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MIN_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_ANISOTROPIC:
//		return D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_MIN_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_COMPARISON_ANISOTROPIC:
//		return D3D11_FILTER::D3D11_FILTER_COMPARISON_ANISOTROPIC;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_MIN_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MINIMUM_ANISOTROPIC:
//		return D3D11_FILTER::D3D11_FILTER_MINIMUM_ANISOTROPIC;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
//	case TORC_GFX_FILTER::FILTER_MAXIMUM_ANISOTROPIC:
//		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_ANISOTROPIC;
//	default:
//		return D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
//	}
//}
//
//D3D11_TEXTURE_ADDRESS_MODE typeConverter::ConvertTorcGfxType(TORC_GFX_TEXTURE_ADDRESS_MODE op)
//{
//	switch (op)
//	{
//	case TORC_GFX_TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP:
//		return D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
//	case TORC_GFX_TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MIRROR:
//		return D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR;
//	case TORC_GFX_TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_CLAMP:
//		return D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
//	case TORC_GFX_TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_BORDER:
//		return D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER;
//	case TORC_GFX_TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MIRROR_ONCE:
//		return D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
//	default:
//		return D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
//	}
//}
//
//D3D_PRIMITIVE_TOPOLOGY typeConverter::ConvertTorcGfxType(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY op)
//{
//	switch (op)
//	{
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_UNDEFINED:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_POINTLIST:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_LINELIST:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_LINESTRIP:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLELIST:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;
//	case TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;
//	default:
//		return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	}
//}

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			uint32_t ConvertType(EResourceFormat op)
			{
				switch (op)
				{
				case EResourceFormat::FORMAT_UNKNOWN:
				return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
				case EResourceFormat::FORMAT_R32G32B32A32_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_TYPELESS;
				case EResourceFormat::FORMAT_R32G32B32A32_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				case EResourceFormat::FORMAT_R32G32B32A32_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
				case EResourceFormat::FORMAT_R32G32B32A32_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
				case EResourceFormat::FORMAT_R32G32B32_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_TYPELESS;
				case EResourceFormat::FORMAT_R32G32B32_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				case EResourceFormat::FORMAT_R32G32B32_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
				case EResourceFormat::FORMAT_R32G32B32_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
				case EResourceFormat::FORMAT_R16G16B16A16_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_TYPELESS;
				case EResourceFormat::FORMAT_R16G16B16A16_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT;
				case EResourceFormat::FORMAT_R16G16B16A16_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UNORM;
				case EResourceFormat::FORMAT_R16G16B16A16_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UINT;
				case EResourceFormat::FORMAT_R16G16B16A16_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_SNORM;
				case EResourceFormat::FORMAT_R16G16B16A16_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_SINT;
				case EResourceFormat::FORMAT_R32G32_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32_TYPELESS;
				case EResourceFormat::FORMAT_R32G32_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				case EResourceFormat::FORMAT_R32G32_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
				case EResourceFormat::FORMAT_R32G32_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
				case EResourceFormat::FORMAT_R32G8X24_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R32G8X24_TYPELESS;
				case EResourceFormat::FORMAT_D32_FLOAT_S8X24_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
				case EResourceFormat::FORMAT_R32_FLOAT_X8X24_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
				case EResourceFormat::FORMAT_X32_TYPELESS_G8X24_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
				case EResourceFormat::FORMAT_R10G10B10A2_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_TYPELESS;
				case EResourceFormat::FORMAT_R10G10B10A2_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_UNORM;
				case EResourceFormat::FORMAT_R10G10B10A2_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_UINT;
				case EResourceFormat::FORMAT_R11G11B10_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R11G11B10_FLOAT;
				case EResourceFormat::FORMAT_R8G8B8A8_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_TYPELESS;
				case EResourceFormat::FORMAT_R8G8B8A8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
				case EResourceFormat::FORMAT_R8G8B8A8_UNORM_SRGB:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				case EResourceFormat::FORMAT_R8G8B8A8_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT;
				case EResourceFormat::FORMAT_R8G8B8A8_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_SNORM;
				case EResourceFormat::FORMAT_R8G8B8A8_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_SINT;
				case EResourceFormat::FORMAT_R16G16_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16_TYPELESS;
				case EResourceFormat::FORMAT_R16G16_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16_FLOAT;
				case EResourceFormat::FORMAT_R16G16_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16_UNORM;
				case EResourceFormat::FORMAT_R16G16_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16_UINT;
				case EResourceFormat::FORMAT_R16G16_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16_SNORM;
				case EResourceFormat::FORMAT_R16G16_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R16G16_SINT;
				case EResourceFormat::FORMAT_R32_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
				case EResourceFormat::FORMAT_D32_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
				case EResourceFormat::FORMAT_R32_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				case EResourceFormat::FORMAT_R32_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
				case EResourceFormat::FORMAT_R32_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
				case EResourceFormat::FORMAT_R24G8_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R24G8_TYPELESS;
				case EResourceFormat::FORMAT_D24_UNORM_S8_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
				case EResourceFormat::FORMAT_R24_UNORM_X8_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
				case EResourceFormat::FORMAT_X24_TYPELESS_G8_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_X24_TYPELESS_G8_UINT;
				case EResourceFormat::FORMAT_R8G8_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8_TYPELESS;
				case EResourceFormat::FORMAT_R8G8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
				case EResourceFormat::FORMAT_R8G8_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8_UINT;
				case EResourceFormat::FORMAT_R8G8_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8_SNORM;
				case EResourceFormat::FORMAT_R8G8_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8_SINT;
				case EResourceFormat::FORMAT_R16_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R16_TYPELESS;
				case EResourceFormat::FORMAT_R16_FLOAT:
				return DXGI_FORMAT::DXGI_FORMAT_R16_FLOAT;
				case EResourceFormat::FORMAT_D16_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_D16_UNORM;
				case EResourceFormat::FORMAT_R16_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R16_UNORM;
				case EResourceFormat::FORMAT_R16_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R16_UINT;
				case EResourceFormat::FORMAT_R16_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R16_SNORM;
				case EResourceFormat::FORMAT_R16_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R16_SINT;
				case EResourceFormat::FORMAT_R8_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_R8_TYPELESS;
				case EResourceFormat::FORMAT_R8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
				case EResourceFormat::FORMAT_R8_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_R8_UINT;
				case EResourceFormat::FORMAT_R8_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R8_SNORM;
				case EResourceFormat::FORMAT_R8_SINT:
				return DXGI_FORMAT::DXGI_FORMAT_R8_SINT;
				case EResourceFormat::FORMAT_A8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_A8_UNORM;
				case EResourceFormat::FORMAT_R1_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R1_UNORM;
				case EResourceFormat::FORMAT_R9G9B9E5_SHAREDEXP:
				return DXGI_FORMAT::DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
				case EResourceFormat::FORMAT_R8G8_B8G8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R8G8_B8G8_UNORM;
				case EResourceFormat::FORMAT_G8R8_G8B8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_G8R8_G8B8_UNORM;
				case EResourceFormat::FORMAT_BC1_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_BC1_TYPELESS;
				case EResourceFormat::FORMAT_BC1_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
				case EResourceFormat::FORMAT_BC1_UNORM_SRGB:
				return DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM_SRGB;
				case EResourceFormat::FORMAT_BC2_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_BC2_TYPELESS;
				case EResourceFormat::FORMAT_BC2_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC2_UNORM;
				case EResourceFormat::FORMAT_BC2_UNORM_SRGB:
				return DXGI_FORMAT::DXGI_FORMAT_BC2_UNORM_SRGB;
				case EResourceFormat::FORMAT_BC3_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_BC3_TYPELESS;
				case EResourceFormat::FORMAT_BC3_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM;
				case EResourceFormat::FORMAT_BC3_UNORM_SRGB:
				return DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM_SRGB;
				case EResourceFormat::FORMAT_BC4_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_BC4_TYPELESS;
				case EResourceFormat::FORMAT_BC4_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM;
				case EResourceFormat::FORMAT_BC4_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC4_SNORM;
				case EResourceFormat::FORMAT_BC5_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_BC5_TYPELESS;
				case EResourceFormat::FORMAT_BC5_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM;
				case EResourceFormat::FORMAT_BC5_SNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC5_SNORM;
				case EResourceFormat::FORMAT_B5G6R5_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_B5G6R5_UNORM;
				case EResourceFormat::FORMAT_B5G5R5A1_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_B5G5R5A1_UNORM;
				case EResourceFormat::FORMAT_B8G8R8A8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
				case EResourceFormat::FORMAT_B8G8R8X8_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_B8G8R8X8_UNORM;
				case EResourceFormat::FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
				case EResourceFormat::FORMAT_B8G8R8A8_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_TYPELESS;
				case EResourceFormat::FORMAT_B8G8R8A8_UNORM_SRGB:
				return DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
				case EResourceFormat::FORMAT_B8G8R8X8_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_B8G8R8X8_TYPELESS;
				case EResourceFormat::FORMAT_B8G8R8X8_UNORM_SRGB:
				return DXGI_FORMAT::DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
				case EResourceFormat::FORMAT_BC6H_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_BC6H_TYPELESS;
				case EResourceFormat::FORMAT_BC6H_UF16:
				return DXGI_FORMAT::DXGI_FORMAT_BC6H_UF16;
				case EResourceFormat::FORMAT_BC6H_SF16:
				return DXGI_FORMAT::DXGI_FORMAT_BC6H_SF16;
				case EResourceFormat::FORMAT_BC7_TYPELESS:
				return DXGI_FORMAT::DXGI_FORMAT_BC7_TYPELESS;
				case EResourceFormat::FORMAT_BC7_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_BC7_UNORM;
				case EResourceFormat::FORMAT_BC7_UNORM_SRGB:
				return DXGI_FORMAT::DXGI_FORMAT_BC7_UNORM_SRGB;
				case EResourceFormat::FORMAT_AYUV:
				return DXGI_FORMAT::DXGI_FORMAT_AYUV;
				case EResourceFormat::FORMAT_Y410:
				return DXGI_FORMAT::DXGI_FORMAT_Y410;
				case EResourceFormat::FORMAT_Y416:
				return DXGI_FORMAT::DXGI_FORMAT_Y416;
				case EResourceFormat::FORMAT_NV12:
				return DXGI_FORMAT::DXGI_FORMAT_NV12;
				case EResourceFormat::FORMAT_P010:
				return DXGI_FORMAT::DXGI_FORMAT_P010;
				case EResourceFormat::FORMAT_P016:
				return DXGI_FORMAT::DXGI_FORMAT_P016;
				case EResourceFormat::FORMAT_420_OPAQUE:
				return DXGI_FORMAT::DXGI_FORMAT_420_OPAQUE;
				case EResourceFormat::FORMAT_YUY2:
				return DXGI_FORMAT::DXGI_FORMAT_YUY2;
				case EResourceFormat::FORMAT_Y210:
				return DXGI_FORMAT::DXGI_FORMAT_Y210;
				case EResourceFormat::FORMAT_Y216:
				return DXGI_FORMAT::DXGI_FORMAT_Y216;
				case EResourceFormat::FORMAT_NV11:
				return DXGI_FORMAT::DXGI_FORMAT_NV11;
				case EResourceFormat::FORMAT_AI44:
				return DXGI_FORMAT::DXGI_FORMAT_AI44;
				case EResourceFormat::FORMAT_IA44:
				return DXGI_FORMAT::DXGI_FORMAT_IA44;
				case EResourceFormat::FORMAT_P8:
				return DXGI_FORMAT::DXGI_FORMAT_P8;
				case EResourceFormat::FORMAT_A8P8:
				return DXGI_FORMAT::DXGI_FORMAT_A8P8;
				case EResourceFormat::FORMAT_B4G4R4A4_UNORM:
				return DXGI_FORMAT::DXGI_FORMAT_B4G4R4A4_UNORM;
				case EResourceFormat::FORMAT_P208:
				return DXGI_FORMAT::DXGI_FORMAT_P208;
				case EResourceFormat::FORMAT_V208:
				return DXGI_FORMAT::DXGI_FORMAT_V208;
				case EResourceFormat::FORMAT_V408:
				return DXGI_FORMAT::DXGI_FORMAT_V408;
				case EResourceFormat::FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
				return DXGI_FORMAT::DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE;
				case EResourceFormat::FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
				return DXGI_FORMAT::DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE;
				case EResourceFormat::FORMAT_FORCE_UINT:
				return DXGI_FORMAT::DXGI_FORMAT_FORCE_UINT;
				default:
				return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
				}
			}
		}
	}
}


