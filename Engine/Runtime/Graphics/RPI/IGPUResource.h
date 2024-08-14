#pragma once
#include "RDI/RDIShared/TorcGfxTypes.h"

namespace gfx
{
	class ITorcGfxBackend;
};

class IGPUResource
{
public:
	IGPUResource();
	virtual ~IGPUResource();

	virtual void* GetDesc() const = 0;
	virtual void Bind() = 0;
	void* m_underlyingType;
	uint64 m_resourceID;
	gfx::ITorcGfxBackend* m_gfx;
};


struct ResourceDescID
{
	// reserve 4 bits for the type
	enum ResourceType
	{
		DSS = 0,
		BS,
		RS,
		SS
	};

	typedef decltype(IGPUResource::m_resourceID) IDType;
	struct RDID_DSS
	{
		union
		{
			IDType id;
			struct
			{
				IDType stencilReadMask : 8;
				IDType stencilWriteMask : 8;
				IDType frontFace : 12;
				IDType backFace : 12;

				IDType depthFunc : 3;
				IDType depthWrite : 1;
				IDType stencilEnable : 1;
				IDType depthEnable : 1;
				IDType resourceType : 4;
			};
		};
	};

	struct RDID_BS
	{
		union
		{
			IDType id;

			struct
			{
				IDType	enabled : 1;
				IDType	alphaToCoverageEnabled : 1;
				IDType	independentBlend : 1;
				IDType	src : 5;
				IDType	dst : 5;
				IDType	op : 3;
				IDType	srcAlpha : 5;
				IDType	dstAlpha : 5;
				IDType	opAlpha : 3;
				IDType	colorEnable : 4;
				IDType	padding : 27;
				IDType	resourceType : 4;

			};
		};
	};

	struct RDID_RS
	{
		union
		{
			IDType id;

			struct
			{
				IDType	depthBiasClamp : 17; // float
				IDType	slopeScaledDepthBias : 17; // float
				IDType	depthBias : 17; // int
				IDType	fillMode : 2;
				IDType	cullMode : 2;
				IDType	antialiasedLineEnable : 1;
				IDType	multisampleEnable : 1;
				IDType	scissorEnable : 1;
				IDType	depthClipEnable : 1;
				IDType	frontCCW : 1;
				IDType	resourceType : 4;
			};
		};
	};

	struct RDID_SS
	{
		union
		{
			IDType id;

			struct
			{
				/*float	mipLODBias;
				float	borderColor[4];
				float	minLOD;
				float	maxLOD;
				uint32_t	maxAnisotropy;*/

				IDType	filter : 6;
				IDType	addressU : 3;
				IDType	addressV : 3;
				IDType	addressW : 3;
				IDType	comparisonFunc : 3;
				IDType	padding : 42;
				IDType	resourceType : 4;
			};
		};
	};

	static IDType GetID(const gfx::BlendDesc& bsDesc);
	static IDType GetID(const gfx::DepthStencilDesc& dssDesc);
	static IDType GetID(const gfx::RasterizerDesc& rsDesc);
	static IDType GetID(const gfx::SamplerDesc& ssDesc);
	static ResourceType GetResourceType(const IDType id);
};
