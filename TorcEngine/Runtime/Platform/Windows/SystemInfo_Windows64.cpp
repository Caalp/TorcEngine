#include "pch.h"

#include "Platform/SystemInfo.h"
#include <sysinfoapi.h>

using namespace Torc;

enum class CPUArchitecture
{
	INTEL_x86	= 0x0,
	ARM			= 0x5,
	IA64		= 0x6,
	AMD64		= 0x9,
	ARM64		= 0xc,
	Unknown		= 0xfffff,
};

enum class RAMType
{
	Unknown	= 0x00,
	Other	= 0x01,
	DRAM	= 0x02,
	VRAM	= 0x07,
	SDRAM	= 0x11,
	DDR		= 0x14,
	DDR2	= 0x15,
	DDR3	= 0x19,
	DDR4	= 0x1a
};

namespace
{
	uint32_t GetSetBitCount(ULONG_PTR value)
	{
		ULONG_PTR mask = ((ULONG_PTR)1 << (sizeof(ULONG_PTR) * 8 - 1));
		uint32_t setBitCount = 0;
		while (mask)
		{
			setBitCount += (value & mask) ? 1 : 0;
			mask /= 2;
		}
		return setBitCount;
	}
}

void SystemInfo::QueryCPUInfo(CPUInfo& info)
{
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = nullptr;
	DWORD length = 0;
	bool queried = false;
	uint32_t processorCount = 0;
	while (!queried)
	{
		bool result = GetLogicalProcessorInformation(buffer, &length);
		DWORD err = GetLastError();
		if (result == false)
		{
			if (err == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer != nullptr)
				{
					free(buffer);
				}

				buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(length);

				if (buffer == nullptr)
				{
					// failed 
					return;
				}
			}
			else
			{
				/// If error is something else still log it
				return;
			}
		}
		else
		{
			queried = true;
		}
	}
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = buffer;
	DWORD offset = 0;
	while ((offset + sizeof(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)) <= length)
	{
		switch (ptr->Relationship)
		{

		case RelationProcessorCore:
			info.cpuPhysicalCoreCount += 1;
			info.cpuLogicalCoreCount += GetSetBitCount(ptr->ProcessorMask);
			info.hasThreads = (info.cpuPhysicalCoreCount == info.cpuLogicalCoreCount) ? false : true;
			break;
		default:
			break;
		}

		offset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		ptr++;
	}

	free(buffer);

	SYSTEM_INFO sysInfo;
	GetNativeSystemInfo(&sysInfo);
	info.cpuArchitecture = (CPUArchitecture)sysInfo.wProcessorArchitecture;
	info.cpuType = sysInfo.dwProcessorType;
}

void SystemInfo::QueryMemoryInfo(MemoryInfo& info)
{
	// Memory info
	MEMORYSTATUSEX memoryInfo;
	memoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
	if (GlobalMemoryStatusEx(&memoryInfo) == false)
	{
		// failed 
	}
	// if not collect the data
	//uint32_t memUsageInPercentageScale = memoryInfo.dwMemoryLoad;
	info.totalMemInBytes = memoryInfo.ullTotalPhys;
	info.availMemInBytes = memoryInfo.ullAvailPhys;
	info.totalVirtualMem = memoryInfo.ullTotalVirtual;
	info.availVirtualMem = memoryInfo.ullAvailVirtual;

	//uint32_t totalMemInGB = (uint32_t)round(totalMemInBytes / float(1024 * 1024 * 1024));
	//uint32_t availMemInGB = (uint32_t)round(availMemInBytes / float(1024 * 1024 * 1024));
}

void SystemInfo::QueryStorageInfo(StorageInfo& info)
{}

void SystemInfo::QueryGPUInfo(GPUInfo& info)
{}

void SystemInfo::QueryMonitorInfo(MonitorInfo& info)
{}

void SystemInfo::QueryInputDeviceInfo(InputDeviceInfo& info)
{}