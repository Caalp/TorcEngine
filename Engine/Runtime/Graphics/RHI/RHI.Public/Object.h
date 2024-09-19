#pragma once
#include <Core/Std/Threading/atomic.h>

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

		struct ShaderByteCode
		{
			const void* pShaderBytecode;
			size_t BytecodeLength;
		};
		
		struct ShaderResourceGroup
		{

		};


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

