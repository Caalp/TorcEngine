#pragma once
#include <cstdint>

namespace Torc
{
	namespace RHI
	{
		enum
		{
			MAX_RENDER_TARGET = 8
		};

		/* Blend */
		enum class EBlendOp : uint8_t
		{
			ADD = 1,
			SUBTRACT = 2,
			REV_SUBTRACT = 3,
			MIN = 4,
			MAX = 5
		};

		enum class EBlend : uint8_t
		{
			ZERO = 1,
			ONE = 2,
			SRC_COLOR = 3,
			INV_SRC_COLOR = 4,
			SRC_ALPHA = 5,
			INV_SRC_ALPHA = 6,
			DEST_ALPHA = 7,
			INV_DEST_ALPHA = 8,
			DEST_COLOR = 9,
			INV_DEST_COLOR = 10,
			SRC_ALPHA_SAT = 11,
			BLEND_FACTOR = 14,
			INV_BLEND_FACTOR = 15,
			SRC1_COLOR = 16,
			INV_SRC1_COLOR = 17,
			SRC1_ALPHA = 18,
			INV_SRC1_ALPHA = 19
		};

		enum class EColorChannel : uint8_t
		{
			NONE = 0,
			RED = 1,
			GREEN = 2,
			BLUE = 4,
			ALPHA = 8,
			ALL = (((RED | GREEN) | BLUE) | ALPHA)
		};

		/* Depth */
		enum class EDepthWrite : uint8_t
		{
			NONE,
			ALL
		};

		enum class EComparisonFunc : uint8_t
		{
			NEVER = 0,
			LESS = 1,
			EQUAL = 2,
			LESS_EQUAL = 3,
			GREATER = 4,
			NOT_EQUAL = 5,
			GREATER_EQUAL = 6,
			ALWAYS = 7
		};

		enum class EStencilOp : uint8_t
		{
			KEEP = 0,
			ZERO = 1,
			REPLACE = 2,
			INCR_SAT = 3,
			DECR_SAT = 4,
			INVERT = 5,
			INCR = 6,
			DECR = 7
		};

		/* Rasterizer */
		enum class EFillMode : uint8_t
		{
			WIREFRAME = 0,
			SOLID,
			COUNT
		};

		enum class ECullMode : uint8_t
		{
			NONE = 0,
			FRONT,
			BACK,
			COUNT
		};

		/* Texture */
		enum class EResourceFormat : uint16_t
		{
			FORMAT_UNKNOWN = 0,
			FORMAT_R32G32B32A32_TYPELESS = 1,
			FORMAT_R32G32B32A32_FLOAT = 2,
			FORMAT_R32G32B32A32_UINT = 3,
			FORMAT_R32G32B32A32_SINT = 4,
			FORMAT_R32G32B32_TYPELESS = 5,
			FORMAT_R32G32B32_FLOAT = 6,
			FORMAT_R32G32B32_UINT = 7,
			FORMAT_R32G32B32_SINT = 8,
			FORMAT_R16G16B16A16_TYPELESS = 9,
			FORMAT_R16G16B16A16_FLOAT = 10,
			FORMAT_R16G16B16A16_UNORM = 11,
			FORMAT_R16G16B16A16_UINT = 12,
			FORMAT_R16G16B16A16_SNORM = 13,
			FORMAT_R16G16B16A16_SINT = 14,
			FORMAT_R32G32_TYPELESS = 15,
			FORMAT_R32G32_FLOAT = 16,
			FORMAT_R32G32_UINT = 17,
			FORMAT_R32G32_SINT = 18,
			FORMAT_R32G8X24_TYPELESS = 19,
			FORMAT_D32_FLOAT_S8X24_UINT = 20,
			FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
			FORMAT_X32_TYPELESS_G8X24_UINT = 22,
			FORMAT_R10G10B10A2_TYPELESS = 23,
			FORMAT_R10G10B10A2_UNORM = 24,
			FORMAT_R10G10B10A2_UINT = 25,
			FORMAT_R11G11B10_FLOAT = 26,
			FORMAT_R8G8B8A8_TYPELESS = 27,
			FORMAT_R8G8B8A8_UNORM = 28,
			FORMAT_R8G8B8A8_UNORM_SRGB = 29,
			FORMAT_R8G8B8A8_UINT = 30,
			FORMAT_R8G8B8A8_SNORM = 31,
			FORMAT_R8G8B8A8_SINT = 32,
			FORMAT_R16G16_TYPELESS = 33,
			FORMAT_R16G16_FLOAT = 34,
			FORMAT_R16G16_UNORM = 35,
			FORMAT_R16G16_UINT = 36,
			FORMAT_R16G16_SNORM = 37,
			FORMAT_R16G16_SINT = 38,
			FORMAT_R32_TYPELESS = 39,
			FORMAT_D32_FLOAT = 40,
			FORMAT_R32_FLOAT = 41,
			FORMAT_R32_UINT = 42,
			FORMAT_R32_SINT = 43,
			FORMAT_R24G8_TYPELESS = 44,
			FORMAT_D24_UNORM_S8_UINT = 45,
			FORMAT_R24_UNORM_X8_TYPELESS = 46,
			FORMAT_X24_TYPELESS_G8_UINT = 47,
			FORMAT_R8G8_TYPELESS = 48,
			FORMAT_R8G8_UNORM = 49,
			FORMAT_R8G8_UINT = 50,
			FORMAT_R8G8_SNORM = 51,
			FORMAT_R8G8_SINT = 52,
			FORMAT_R16_TYPELESS = 53,
			FORMAT_R16_FLOAT = 54,
			FORMAT_D16_UNORM = 55,
			FORMAT_R16_UNORM = 56,
			FORMAT_R16_UINT = 57,
			FORMAT_R16_SNORM = 58,
			FORMAT_R16_SINT = 59,
			FORMAT_R8_TYPELESS = 60,
			FORMAT_R8_UNORM = 61,
			FORMAT_R8_UINT = 62,
			FORMAT_R8_SNORM = 63,
			FORMAT_R8_SINT = 64,
			FORMAT_A8_UNORM = 65,
			FORMAT_R1_UNORM = 66,
			FORMAT_R9G9B9E5_SHAREDEXP = 67,
			FORMAT_R8G8_B8G8_UNORM = 68,
			FORMAT_G8R8_G8B8_UNORM = 69,
			FORMAT_BC1_TYPELESS = 70,
			FORMAT_BC1_UNORM = 71,
			FORMAT_BC1_UNORM_SRGB = 72,
			FORMAT_BC2_TYPELESS = 73,
			FORMAT_BC2_UNORM = 74,
			FORMAT_BC2_UNORM_SRGB = 75,
			FORMAT_BC3_TYPELESS = 76,
			FORMAT_BC3_UNORM = 77,
			FORMAT_BC3_UNORM_SRGB = 78,
			FORMAT_BC4_TYPELESS = 79,
			FORMAT_BC4_UNORM = 80,
			FORMAT_BC4_SNORM = 81,
			FORMAT_BC5_TYPELESS = 82,
			FORMAT_BC5_UNORM = 83,
			FORMAT_BC5_SNORM = 84,
			FORMAT_B5G6R5_UNORM = 85,
			FORMAT_B5G5R5A1_UNORM = 86,
			FORMAT_B8G8R8A8_UNORM = 87,
			FORMAT_B8G8R8X8_UNORM = 88,
			FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
			FORMAT_B8G8R8A8_TYPELESS = 90,
			FORMAT_B8G8R8A8_UNORM_SRGB = 91,
			FORMAT_B8G8R8X8_TYPELESS = 92,
			FORMAT_B8G8R8X8_UNORM_SRGB = 93,
			FORMAT_BC6H_TYPELESS = 94,
			FORMAT_BC6H_UF16 = 95,
			FORMAT_BC6H_SF16 = 96,
			FORMAT_BC7_TYPELESS = 97,
			FORMAT_BC7_UNORM = 98,
			FORMAT_BC7_UNORM_SRGB = 99,
			FORMAT_AYUV = 100,
			FORMAT_Y410 = 101,
			FORMAT_Y416 = 102,
			FORMAT_NV12 = 103,
			FORMAT_P010 = 104,
			FORMAT_P016 = 105,
			FORMAT_420_OPAQUE = 106,
			FORMAT_YUY2 = 107,
			FORMAT_Y210 = 108,
			FORMAT_Y216 = 109,
			FORMAT_NV11 = 110,
			FORMAT_AI44 = 111,
			FORMAT_IA44 = 112,
			FORMAT_P8 = 113,
			FORMAT_A8P8 = 114,
			FORMAT_B4G4R4A4_UNORM = 115,
			FORMAT_P208 = 130,
			FORMAT_V208 = 131,
			FORMAT_V408 = 132,
			FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
			FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
			FORMAT_FORCE_UINT = 0xffff
		};

		enum class EResourceAccess : uint8_t
		{
			USAGE_GPU_READ_AND_WRITE = 0,
			USAGE_GPU_READ = 1,
			USAGE_GPU_READ_CPU_WRITE = 2,
			USAGE_GPU_CPU_READ_WRITE = 3
		};

		typedef enum EResourceUsage : uint16_t
		{
			BIND_VERTEX_BUFFER = (1 << 0),
			BIND_INDEX_BUFFER = (1 << 1),
			BIND_SHADER_RESOURCE = (1 << 2),
			BIND_STREAM_OUTPUT = (1 << 3),
			BIND_RENDER_TARGET = (1 << 4),
			BIND_DEPTH_STENCIL = (1 << 5),
			BIND_UNORDERED_ACCESS = (1 << 6),
			BIND_DECODER = (1 << 7),
			BIND_VIDEO_ENCODER = (1 << 8),
			BIND_CONSTANT_BUFFER = (1 << 9)
		} TORC_GFX_RESOURCE_BIND_FLAG;

		enum ECPUAccessFlag : uint8_t
		{
			NO_ACCESS = 0,
			CPU_ACCESS_WRITE = 1 << 0,
			CPU_ACCESS_READ = 1 << 1
		};

		enum class EResourceMiscFlags
		{
			RESOURCE_MISC_NOT_USED = 0,
			RESOURCE_MISC_GENERATE_MIPS = 0x1L,
			RESOURCE_MISC_SHARED = 0x2L,
			RESOURCE_MISC_TEXTURECUBE = 0x4L,
			RESOURCE_MISC_DRAWINDIRECT_ARGS = 0x10L,
			RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS = 0x20L,
			RESOURCE_MISC_BUFFER_STRUCTURED = 0x40L,
			RESOURCE_MISC_RESOURCE_CLAMP = 0x80L,
			RESOURCE_MISC_SHARED_KEYEDMUTEX = 0x100L,
			RESOURCE_MISC_GDI_COMPATIBLE = 0x200L,
			RESOURCE_MISC_SHARED_NTHANDLE = 0x800L,
			RESOURCE_MISC_RESTRICTED_CONTENT = 0x1000L,
			RESOURCE_MISC_RESTRICT_SHARED_RESOURCE = 0x2000L,
			RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER = 0x4000L,
			RESOURCE_MISC_GUARDED = 0x8000L,
			RESOURCE_MISC_TILE_POOL = 0x20000L,
			RESOURCE_MISC_TILED = 0x40000L,
			RESOURCE_MISC_HW_PROTECTED = 0x80000L,
			RESOURCE_MISC_SHARED_DISPLAYABLE,
			RESOURCE_MISC_SHARED_EXCLUSIVE_WRITER
		};

		enum class EFilter
		{
			FILTER_MIN_MAG_MIP_POINT = 0,
			FILTER_MIN_MAG_POINT_MIP_LINEAR,
			FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
			FILTER_MIN_POINT_MAG_MIP_LINEAR,
			FILTER_MIN_LINEAR_MAG_MIP_POINT,
			FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			FILTER_MIN_MAG_LINEAR_MIP_POINT,
			FILTER_MIN_MAG_MIP_LINEAR,
			FILTER_ANISOTROPIC,
			FILTER_COMPARISON_MIN_MAG_MIP_POINT,
			FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
			FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
			FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
			FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
			FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
			FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
			FILTER_COMPARISON_ANISOTROPIC,
			FILTER_MINIMUM_MIN_MAG_MIP_POINT,
			FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
			FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
			FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
			FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
			FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
			FILTER_MINIMUM_MIN_MAG_MIP_LINEAR,
			FILTER_MINIMUM_ANISOTROPIC,
			FILTER_MAXIMUM_MIN_MAG_MIP_POINT,
			FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
			FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
			FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
			FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
			FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
			FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR,
			FILTER_MAXIMUM_ANISOTROPIC
		};

		enum class ETextureAddressMode : uint8_t
		{
			TEXTURE_ADDRESS_WRAP = 0,
			TEXTURE_ADDRESS_MIRROR,
			TEXTURE_ADDRESS_CLAMP,
			TEXTURE_ADDRESS_BORDER,
			TEXTURE_ADDRESS_MIRROR_ONCE
		};

		enum class EPrimitiveTopology : uint8_t
		{
			PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
			PRIMITIVE_TOPOLOGY_POINTLIST,
			PRIMITIVE_TOPOLOGY_LINELIST,
			PRIMITIVE_TOPOLOGY_LINESTRIP,
			PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
			PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
			PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
			PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
		};

		enum class EImageDimension : uint8_t
		{
			DIMENSION_UNKNOWN = 0,
			DIMENSION_BUFFER = 1,
			DIMENSION_TEXTURE1D = 2,
			DIMENSION_TEXTURE1DARRAY = 3,
			DIMENSION_TEXTURE2D = 4,
			DIMENSION_TEXTURE2DARRAY = 5,
			DIMENSION_TEXTURE2DMS = 6,
			DIMENSION_TEXTURE2DMSARRAY = 7,
			DIMENSION_TEXTURE3D = 8
		};

		/* Parameters */
		struct SampleDescription
		{
			uint32_t m_count;
			uint32_t m_quality;
		};

		struct SamplerDescription
		{
			EFilter					m_filter;
			ETextureAddressMode		m_addressU;
			ETextureAddressMode		m_addressV;
			ETextureAddressMode		m_addressW;
			float					m_mipLODBias;
			uint32_t		    	m_maxAnisotropy;
			EComparisonFunc			m_comparisonFunc;
			float					m_borderColor[4];
			float					m_minLOD;
			float					m_maxLOD;
		};

		struct StencilDescription
		{
			EStencilOp		m_stencilFailOp;
			EStencilOp		m_stencilDepthFailOp;
			EStencilOp		m_stencilPassOp;
			EComparisonFunc	m_stencilFunc;
		};

		struct DepthStencilDescription
		{
			bool				m_depthEnable;
			bool				m_stencilEnable;
			uint8_t				m_stencilReadMask;
			uint8_t				m_stencilWriteMask;
			StencilDescription	m_frontFace;
			StencilDescription	m_backFace;
			EDepthWrite			m_depthWrite;
			EComparisonFunc		m_depthFunc;
		};

		struct BlendDescription
		{
			bool			m_blendEnable;
			bool			m_alphaToCoverageEnable;
			bool			m_independentBlendEnable;
			EBlend			m_srcBlend;
			EBlend			m_destBlend;
			EBlendOp		m_blendOp;
			EBlend			m_srcBlendAlpha;
			EBlend			m_destBlendAlpha;
			EBlendOp		m_blendOpAlpha;
			EColorChannel	m_rtWriteMask;
		};

		struct RasterizerDescription
		{
			int			m_depthBias;
			float		m_depthBiasClamp;
			float		m_slopeScaledDepthBias;
			bool		m_depthClipEnable;
			bool		m_scissorEnable;
			bool		m_multisampleEnable;
			bool		m_antialiasedLineEnable;
			bool		m_frontCCW;
			EFillMode	m_fillMode;
			EFillMode	m_cullMode;
		};

		struct ImageDescription
		{
			uint32_t			m_width;
			uint32_t			m_height;
			uint32_t			m_mipLevels;
			uint32_t			m_arraySize;
			EResourceFormat		m_format;
			SampleDescription	m_sampleDesc;
			EResourceUsage		m_usage;
			uint32_t			m_bindFlags;
			uint32_t			m_cpuAccessFlags;
			uint32_t			m_miscFlags;
		};

		struct ViewportDescription
		{
			float m_topLeftX;
			float m_topLeftY;
			float m_width;
			float m_height;
			float m_minDepth;
			float m_maxDepth;
		};

		enum class EResourceDimension
		{
			RESOURCE_DIMENSION_UNKNOWN = 0,
			RESOURCE_DIMENSION_BUFFER = 1,
			RESOURCE_DIMENSION_TEXTURE1D = 2,
			RESOURCE_DIMENSION_TEXTURE2D = 3,
			RESOURCE_DIMENSION_TEXTURE3D = 4
		};

		enum class EImageLayout {
			TEXTURE_LAYOUT_UNKNOWN = 0,
			TEXTURE_LAYOUT_ROW_MAJOR = 1,
			TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE = 2,
			TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE = 3
		};

		enum EClearFlags
		{
			CLEAR_FLAG_DEPTH = 0x1,
			CLEAR_FLAG_STENCIL = 0x2
		};

		//	struct RenderTargetDesc
		//	{
		//		bool createMatchingDepthView;
		//		TORC_GFX_RESOURCE_DATA_FORMAT format;
		//		TORC_GFX_RTV_DIMENSION viewDimension;
		//		TextureDesc textureDesc;
		//	};
		//

		//	struct GfxBackendParams
		//	{
		//		SwapChainDescription SwapChainDesc;
		//		const char* backendDLLName; // name of the dll that will be imported
		//		const void* targetWindow; // instance of the target window that swapchain and device will be created for
		//		bool isForEditorLoad;
		//	};

		//	struct SubResourceData
		//	{
		//		const void* sysMem;
		//		uint32_t    sysMemPitch;
		//		uint32_t    sysMemSlicePitch;

		//		uint32_t byteWidth;
		//		uint32_t structureByteStride;

		//		SubResourceData()
		//			: byteWidth(0)
		//			, structureByteStride(0)
		//			, sysMemPitch(0)
		//			, sysMemSlicePitch(0)
		//			, sysMem(nullptr)
		//		{}
		//	};

		//	struct BufferDescription
		//	{
		//		enum ConstantBufferType : uint8_t
		//		{
		//			PS,
		//			VS,
		//			GS,
		//			HS,
		//			DS
		//		};

		//		uint32_t byteWidth;
		//		uint32_t structureByteStride;
		//		TORC_GFX_RESOURCE_MISC_FLAG	miscFlags;
		//		TORC_GFX_RESOURCE_DATA_FORMAT format;
		//		TORC_GFX_RESOURCE_BIND_FLAG bindFlags;

		//		uint32_t startSlot;
		//		uint32_t numBuffers;
		//		uint32_t stride;
		//		uint32_t offset;

		//		ConstantBufferType cbType;
		//		TORC_GFX_RESOURCE_USAGE usage;
		//		TORC_GFX_CPU_ACCESS_FLAG cpuAccessFlags;
		//		SubResourceData data;
		//	};
		//}
	}
}
