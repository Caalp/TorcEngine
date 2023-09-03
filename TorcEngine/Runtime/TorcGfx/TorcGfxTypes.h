#pragma once

namespace gfx
{
	enum
	{
		MAX_RENDER_TARGET = 8
	};

	/* Blend */
	enum class TORC_GFX_BLEND_OP
	{
        ADD = 1,
        SUBTRACT = 2,
        REV_SUBTRACT = 3,
        MIN = 4,
        MAX = 5
	};
	
	enum class TORC_GFX_BLEND
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

    enum class TORC_GFX_COLOR_ENABLE
    {
        RED = 1,
        GREEN = 2,
        BLUE = 4,
        ALPHA = 8,
        ALL = (((RED | GREEN) | BLUE) | ALPHA)
    };

    /* Depth */
	enum class TORC_GFX_DEPTH_WRITE
	{
		NONE,
		ALL
	};

	enum class TORC_GFX_COMPARISON_FUNC
	{
		NEVER = 1,
		LESS = 2,
		EQUAL = 3,
		LESS_EQUAL = 4,
		GREATER = 5,
		NOT_EQUAL = 6,
		GREATER_EQUAL = 7,
		ALWAYS = 8
	};

	enum class TORC_GFX_STENCIL_OP
	{
		KEEP = 1,
		ZERO = 2,
		REPLACE = 3,
		INCR_SAT = 4,
		DECR_SAT = 5,
		INVERT = 6,
		INCR = 7,
		DECR = 8
	};

	/* Rasterizer */
	enum class TORC_GFX_FILL_MODE
	{
		WIREFRAME = 0,
		SOLID,
		COUNT
	};

	enum class TORC_GFX_CULL_MODE
	{
		NONE = 0,
		FRONT,
		BACK,
		COUNT
	};

	/* Texture */
	enum class TORC_GFX_RESOURCE_DATA_FORMAT : uint32_t
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
		FORMAT_FORCE_UINT = 0xffffffff
	};

	enum class TORC_GFX_RESOURCE_USAGE
	{
		USAGE_GPU_READ_AND_WRITE = 0,
		USAGE_GPU_READ = 1,
		USAGE_GPU_READ_CPU_WRITE = 2,
		USAGE_GPU_CPU_READ_WRITE = 3
	};

	enum class TORC_GFX_RESOURCE_BIND_FLAG
	{
		BIND_VERTEX_BUFFER = 0x1L,
		BIND_INDEX_BUFFER = 0x2L,
		BIND_CONSTANT_BUFFER = 0x4L,
		BIND_SHADER_RESOURCE = 0x8L,
		BIND_STREAM_OUTPUT = 0x10L,
		BIND_RENDER_TARGET = 0x20L,
		BIND_DEPTH_STENCIL = 0x40L,
		BIND_UNORDERED_ACCESS = 0x80L,
		BIND_DECODER = 0x200L,
		BIND_VIDEO_ENCODER = 0x400L
	};

	enum class TORC_GFX_CPU_ACCESS_FLAG
	{
		CPU_ACCESS_WRITE = 0x10000L,
		CPU_ACCESS_READ = 0x20000L
	};

	enum class TORC_GFX_RESOURCE_MISC_FLAG
	{
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

	enum class TORC_GFX_FILTER
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

	enum class TORC_GFX_TEXTURE_ADDRESS_MODE
	{
		TEXTURE_ADDRESS_WRAP = 0,
		TEXTURE_ADDRESS_MIRROR,
		TEXTURE_ADDRESS_CLAMP,
		TEXTURE_ADDRESS_BORDER,
		TEXTURE_ADDRESS_MIRROR_ONCE
	};

	/* Parameters */
	struct SampleDesc
	{
		uint32_t count;
		uint32_t quality;
	};

	struct SamplerDesc
	{
		TORC_GFX_FILTER					filter;
		TORC_GFX_TEXTURE_ADDRESS_MODE	addressU;
		TORC_GFX_TEXTURE_ADDRESS_MODE	addressV;
		TORC_GFX_TEXTURE_ADDRESS_MODE	addressW;
		float							mipLODBias;
		uint32_t						maxAnisotropy;
		TORC_GFX_COMPARISON_FUNC		comparisonFunc;
		float							borderColor[4];
		float							minLOD;
		float							maxLOD;
	};

	struct StencilDesc
	{
		TORC_GFX_STENCIL_OP stencilFailOp;
		TORC_GFX_STENCIL_OP stencilDepthFailOp;
		TORC_GFX_STENCIL_OP stencilPassOp;
		TORC_GFX_COMPARISON_FUNC stencilFunc;
	};

	struct DepthStencilDesc
	{
		bool depthEnable;
		TORC_GFX_DEPTH_WRITE depthWrite;
		TORC_GFX_COMPARISON_FUNC depthFunc;
		bool stencilEnable;
		uint8_t stencilReadMask;
		uint8_t stencilWriteMask;
		StencilDesc frontFace;
		StencilDesc backFace;
	};

	struct BlendDesc
	{
		bool blendEnable;
		bool alphaToCoverageEnable;
		bool independentBlendEnable;
		TORC_GFX_BLEND srcBlend;
		TORC_GFX_BLEND destBlend;
		TORC_GFX_BLEND_OP blendOp;
		TORC_GFX_BLEND srcBlendAlpha;
		TORC_GFX_BLEND destBlendAlpha;
		TORC_GFX_BLEND_OP blendOpAlpha;
		TORC_GFX_COLOR_ENABLE rtWriteMask;
	};

	struct RasterizerDesc
	{
		TORC_GFX_FILL_MODE fillMode;
		TORC_GFX_CULL_MODE cullMode;
		bool frontCCW;
		int depthBias;
		float depthBiasClamp;
		float slopeScaledDepthBias;
		bool depthClipEnable;
		bool scissorEnable;
		bool multisampleEnable;
		bool antialiasedLineEnable;
	};
	struct TextureDesc
	{
		uint32_t width;
		uint32_t height;
		uint32_t mipLevels;
		uint32_t arraySize;
		TORC_GFX_RESOURCE_DATA_FORMAT format;
		SampleDesc sampleDesc;
		TORC_GFX_RESOURCE_USAGE usage;
		uint32_t bindFlags;
		uint32_t cpuAccessFlags;
		uint32_t miscFlags;
	};

	struct SwapChainDesc
	{
		uint32_t width; // zero width means to use default width of the window 
		uint32_t height; // zero height means to use default height of the window
		uint32_t refreshRateNumerator;
		uint32_t refreshRateDenominator;
		gfx::TORC_GFX_RESOURCE_DATA_FORMAT format;
		gfx::SampleDesc samplingParams;
		
	};

	struct RenderTargetDesc
	{

	};

	struct ViewPortDesc
	{
		float topLeftX;
		float topLeftY;
		float width;
		float height;
		float minDepth;
		float maxDepth;
	};

	struct GfxBackendParams
	{
		SwapChainDesc SwapChainDesc;
		const char* backendDLLName; // name of the dll that will be imported
		const void* targetWindow; // instance of the target window that swapchain and device will be created for
		class IGfxDevice** gfxDevice;
		class IGfxContext** gfxContext;
		class IGfxSwapChain** gfxSwapChain;
	};
}