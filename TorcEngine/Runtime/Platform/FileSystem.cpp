#include "pch.h"
#include "Platform/FileSystem.h"

using namespace Torc;

FileSystem::FileSystem(const char* path)
{
	m_path = path;
}

const char* FileSystem::GetAbsolutePath()
{
	return (const char*)std::filesystem::absolute(m_path).c_str();
}

const char* FileSystem::GetCurrentPath() const
{
	return (const char*)m_path.c_str();
}

void FileSystem::SetCurrentPath(const char* path)
{
	m_path = path;
}

bool FileSystem::IsExist(const char* path)
{
	return std::filesystem::exists(path);
}

unsigned long long FileSystem::GetFileSize(const char* path)
{
	return std::filesystem::file_size(path);
}

bool FileSystem::IsDirectory(const char* path)
{
	return std::filesystem::is_directory(path);
}

bool FileSystem::IsEmpty(const char* path)
{
	return std::filesystem::is_empty(path);
}

bool FileSystem::IsFile(const char* path)
{
	return std::filesystem::is_regular_file(path);
}

FileSystem::SpaceInfo FileSystem::GetSpaceInfo(const char* path)
{
	std::filesystem::space_info temp = std::filesystem::space(path);
	return SpaceInfo{ temp.capacity, temp.free, temp.available };
}