#pragma once
#include <Core/Base.h>
#include "RHIEnumTypes.h"

namespace Torc
{
	namespace RHI
	{
		typedef struct BufferRTV
		{
			union
			{
				uint32_t FirstElement;
				uint32_t ElementOffset;
			};
			union
			{
				uint32_t NumElements;
				uint32_t ElementWidth;
			};
		} 	BufferRTV;

		typedef struct Image1DRTV
		{
			uint32_t MipSlice;
		} 	Image1DRTV;

		typedef struct Image1DArrayRTV
		{
			uint32_t MipSlice;
			uint32_t FirstArraySlice;
			uint32_t ArraySize;
		} 	Image1DArrayRTV;

		typedef struct Image2DRTV
		{
			uint32_t MipSlice;
		} 	Image2DRTV;

		typedef struct Image2DMSRTV
		{
			uint32_t UnusedField_NothingToDefine;
		} 	Image2DMSRTV;

		typedef struct Image2DArrayRTV
		{
			uint32_t MipSlice;
			uint32_t FirstArraySlice;
			uint32_t ArraySize;
		} 	Image2DArrayRTV;

		typedef struct Tex2DMSArrayRTV
		{
			uint32_t FirstArraySlice;
			uint32_t ArraySize;
		} 	Tex2DMSArrayRTV;

		typedef struct Image3DRTV
		{
			uint32_t MipSlice;
			uint32_t FirstWSlice;
			uint32_t WSize;
		} 	Image3DRTV;

		struct ImageViewDesc
		{
			EResourceFormat Format;
			EImageDimension ViewDimension;
			union
			{
				BufferRTV Buffer;
				Image1DRTV Texture1D;
				Image1DArrayRTV Texture1DArray;
				Image2DRTV Texture2D;
				Image2DMSRTV Texture2DArray;
				Image2DArrayRTV Texture2DMS;
				Tex2DMSArrayRTV Texture2DMSArray;
				Image3DRTV Texture3D;
			};
		};

		typedef struct ResourceDesc {
			EResourceDimension		 m_dimension;
			uint64_t                 m_alignment;
			uint64_t                 m_width;
			uint32_t                 m_height;
			uint16_t                 m_depthOrArraySize;
			uint16_t                 m_mipLevels;
			EResourceFormat          m_format;
			SampleDescription        m_sampleDesc;
			EImageLayout			 m_layout;
			EResourceUsage			 m_flags;
		} ResourceDesc;
	}
}
