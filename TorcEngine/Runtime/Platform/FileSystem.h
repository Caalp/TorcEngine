#pragma once

/* wrapper around std::filesystem */

namespace Torc
{
	class FileSystem
	{
	public:
		struct SpaceInfo
		{
			std::uintmax_t capacity;
			std::uintmax_t free;
			std::uintmax_t available;
		};

		FileSystem() = default;
		FileSystem(const char* path);
		const char* GetAbsolutePath();

		const char* GetCurrentPath() const;
		void SetCurrentPath(const char* path);

		static bool IsExist(const char* path);
		static unsigned long long GetFileSize(const char* path);
		static bool IsDirectory(const char* path);
		static bool IsEmpty(const char* path);
		static bool IsFile(const char* path);

		static SpaceInfo GetSpaceInfo(const char* path);

	private:
		std::filesystem::path m_path;
	};
}
