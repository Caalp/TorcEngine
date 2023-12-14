#pragma once

namespace TorcPlatform::Utils
{
	uint64_t ByteToMb(uint64_t sizeInBytes);
	uint64_t byteToGb(uint64_t sizeInBytes);
}

enum class CPUArchitecture;
enum class RAMType;

namespace Torc
{
	struct CPUInfo
	{
		uint32_t cpuPhysicalCoreCount;
		uint32_t cpuType;
		uint32_t cpuLogicalCoreCount;
		CPUArchitecture cpuArchitecture;
		bool hasThreads;
	};

	struct MemoryInfo
	{
		uint64_t totalMemInBytes;
		uint64_t availMemInBytes;
		uint64_t totalVirtualMem;
		uint64_t availVirtualMem;
		//uint32_t clockSpeed;
		//uint32_t voltage;
		//uint16_t dataWidth;
		//uint16_t memoryType;
		//uint32_t speed; ///< memory speed in nanoseconds
	};

	struct StorageInfo
	{
		std::string deviceID;
		std::string interfaceType;
		std::string mediaType; ///< external hdd, removable, fixed etc.
		std::string status;
		std::string compressionMethod;

		uint64_t size;
		uint64_t defaultBlockSize;
		uint64_t totalCylinders;
		uint64_t minBlockSize; ///< in bytes
		uint64_t maxBlockSize; ///< max block size in bytes
		uint64_t maxMediaSize; ///< in kb
		uint64_t totalSectors;
		uint64_t totalTracks;
		uint32_t totalHeads;
		uint32_t bytesPerSector;
		uint32_t sectorsPerTrack;
		uint32_t tracksPerCylinder;
		uint32_t index;  ///< physical drive number of the drive
		uint16_t availability;
	};

	struct GPUInfo
	{};

	struct MonitorInfo
	{};

	struct InputDeviceInfo
	{};

	struct SystemHardwareInfo
	{
		CPUInfo cpuInfo;
		MemoryInfo memoryInfo;
		StorageInfo storageInfo;
		GPUInfo gpuInfo;
		MonitorInfo monitorInfo;
		InputDeviceInfo inputDeviceInfo;
	};

	class SystemInfo
	{
	public:
		void QuerySystemInfo(SystemHardwareInfo& outSystemInfo);

	public:
		void QueryCPUInfo(CPUInfo& info);
		void QueryMemoryInfo(MemoryInfo& info);
		void QueryStorageInfo(StorageInfo& info);
		void QueryGPUInfo(GPUInfo& info);
		void QueryMonitorInfo(MonitorInfo& info);
		void QueryInputDeviceInfo(InputDeviceInfo& info);
	private:
		SystemHardwareInfo m_systemHwInfo;
	};
}