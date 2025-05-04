#pragma once

namespace Torc
{
	namespace RHI
	{
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
	}
}
