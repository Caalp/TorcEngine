#pragma once

namespace Torc
{
	namespace RHI
	{
		/*class RootSignature: public DeviceChild
		{
		public:
		};*/

		//typedef struct SO_DECLARATION_ENTRY
		//{
		//	UINT Stream;
		//	LPCSTR SemanticName;
		//	UINT SemanticIndex;
		//	BYTE StartComponent;
		//	BYTE ComponentCount;
		//	BYTE OutputSlot;
		//} 	SO_DECLARATION_ENTRY;

		//typedef struct StreamOutputDesc
		//{
		//	_Field_size_full_(NumEntries)  const D3D12_SO_DECLARATION_ENTRY* pSODeclaration;
		//	UINT NumEntries;
		//	_Field_size_full_(NumStrides)  const UINT* pBufferStrides;
		//	UINT NumStrides;
		//	UINT RasterizedStream;
		//} 	D3D12_STREAM_OUTPUT_DESC;

		//typedef struct PipelineStateDesc
		//{
		//	//RootSignature* pRootSignature;
		//	ShaderByteCode VS;
		//	ShaderByteCode PS;
		//	ShaderByteCode DS;
		//	ShaderByteCode HS;
		//	ShaderByteCode GS;
		//	StreamOutputDesc StreamOutput;
		//	BlendDescription BlendState;
		//	uint32_t SampleMask;
		//	RasterizerDescription RasterizerState;
		//	DepthStencilDescription DepthStencilState;
		//	//D3D12_INPUT_LAYOUT_DESC InputLayout;
		//	//D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue;
		//	EPrimitiveTopology PrimitiveTopologyType;
		//	uint32_t NumRenderTargets;
		//	EResourceFormat RTVFormats[8];
		//	EResourceFormat DSVFormat;
		//	SampleDescription SampleDesc;
		//	EResourceFormat NodeMask;
		//	//D3D12_CACHED_PIPELINE_STATE CachedPSO;
		//	//D3D12_PIPELINE_STATE_FLAGS Flags;
		//} PSO;
	}
}
