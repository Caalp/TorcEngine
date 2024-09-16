#pragma once
#include <Core/Std/Threading/atomic.h>
#include "RHI/RHI.Public/RHITypes.h"
#include <d3d12.h>

namespace Torc
{
	namespace RHI
	{
		typedef uint64_t GPUVirtualAddress;

		enum class EResult
		{
			Success,
			Failure
		};


		typedef struct CPUDescriptorHandle
		{
			size_t m_ptr;
		} CPUDescriptorHandle;

		typedef struct GPUDescriptorHandle
		{
			size_t m_ptr;
		} GPUDescriptorHandle;

		struct DescriptorHandles
		{
			CPUDescriptorHandle m_cpuHandle;
			GPUDescriptorHandle m_gpuHandle;
		};

		typedef enum EClearFlags
		{
			CLEAR_FLAG_DEPTH = 0x1,
			CLEAR_FLAG_STENCIL = 0x2
		};


		typedef struct Rect {
			long m_left;
			long m_top;
			long m_right;
			long m_bottom;
		} Rect, * Rect, * Rect, * Rect;

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

		typedef struct Box
		{
			uint32_t left;
			uint32_t top;
			uint32_t front;
			uint32_t right;
			uint32_t bottom;
			uint32_t back;
		} RHIBox;


		typedef struct Range
		{
			size_t m_begin;
			size_t m_end;
		};

		typedef struct ShaderByteCode
		{
			const void* pShaderBytecode;
			size_t BytecodeLength;
		};
		
		class RootSignature: public DeviceChild
		{
		public:
		};

		typedef struct SO_DECLARATION_ENTRY
		{
			UINT Stream;
			LPCSTR SemanticName;
			UINT SemanticIndex;
			BYTE StartComponent;
			BYTE ComponentCount;
			BYTE OutputSlot;
		} 	SO_DECLARATION_ENTRY;

		typedef struct StreamOutputDesc
		{
			_Field_size_full_(NumEntries)  const D3D12_SO_DECLARATION_ENTRY* pSODeclaration;
			UINT NumEntries;
			_Field_size_full_(NumStrides)  const UINT* pBufferStrides;
			UINT NumStrides;
			UINT RasterizedStream;
		} 	D3D12_STREAM_OUTPUT_DESC;

		typedef struct PipelineStateDesc
		{
			RootSignature* pRootSignature;
			ShaderByteCode VS;
			ShaderByteCode PS;
			ShaderByteCode DS;
			ShaderByteCode HS;
			ShaderByteCode GS;
			StreamOutputDesc StreamOutput;
			BlendDescription BlendState;
			uint32_t SampleMask;
			RasterizerDescription RasterizerState;
			DepthStencilDescription DepthStencilState;
			//D3D12_INPUT_LAYOUT_DESC InputLayout;
			//D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue;
			EPrimitiveTopology PrimitiveTopologyType;
			uint32_t NumRenderTargets;
			EResourceFormat RTVFormats[8];
			EResourceFormat DSVFormat;
			SampleDescription SampleDesc;
			EResourceFormat NodeMask;
			//D3D12_CACHED_PIPELINE_STATE CachedPSO;
			//D3D12_PIPELINE_STATE_FLAGS Flags;
		} PSO;



		class Object;	

		/*class Buffer : public Resource
		{

		};*/

		template<typename T>
		using RefCountedPtr = intrusive_ptr<T>;
		//! Base class for all RHI classes, which provides ref counting.
		class Object
		{
		public:
			virtual ~Object() = default;
			void SetName(wchar_t* name) { m_name = name; }

		private:

			virtual void add_ref() {};
			virtual void release() {};


			const wchar_t* m_name;
			Std::atomic<int32_t> m_refCount;
		};
	}
}

