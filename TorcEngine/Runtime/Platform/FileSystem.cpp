#include "pch.h"
#include "Platform/FileSystem.h"
#include "Core/Common/StringUtils.h"

#include <shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

inline uint32 Win32GetDesiredAccess(FileAccessMode access)
{
	uint32 win32Access = 0;
	win32Access |= ((uint32)access & (uint32)FileAccessMode::Access_Read) ? GENERIC_READ : 0u;
	win32Access |= ((uint32)access & (uint32)FileAccessMode::Access_Write) ? GENERIC_WRITE : 0u;
	return win32Access;
}

inline uint32 Win32GetShareMode(FileShareMode access)
{
	uint32 win32Access = 0;
	win32Access |= ((uint32)access & (uint32)FileShareMode::Share_Read) ? FILE_SHARE_READ : 0u;
	win32Access |= ((uint32)access & (uint32)FileShareMode::Share_Write) ?  FILE_SHARE_WRITE : 0u;
	return win32Access;
}

inline uint32 Win32GetCreationFlag(FileCreationFlag access)
{
	switch (access)
	{
	case FileCreationFlag::Create_Always:
		return CREATE_ALWAYS;
	case FileCreationFlag::Create_New:
		return CREATE_NEW;
	case FileCreationFlag::Open_Always:
		return OPEN_ALWAYS;
	case FileCreationFlag::Open_Existing:
		return OPEN_EXISTING;
	case FileCreationFlag::Truncate_Existing:
		return TRUNCATE_EXISTING;
	default:
		return CREATE_NEW;
	}
}

inline uint32 Win32GetFileAttribute(uint32 attr)
{
	uint32 fileAttr = 0;
	fileAttr |= (attr & FileAttribute::File_Attribute_ReadOnly) ? FILE_ATTRIBUTE_READONLY : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Hidden) ? FILE_ATTRIBUTE_HIDDEN : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_System) ? FILE_ATTRIBUTE_SYSTEM : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Directory) ? FILE_ATTRIBUTE_DIRECTORY : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Archive) ? FILE_ATTRIBUTE_ARCHIVE : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Device) ? FILE_ATTRIBUTE_DEVICE : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Normal) ? FILE_ATTRIBUTE_NORMAL : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Temporary) ? FILE_ATTRIBUTE_TEMPORARY : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Sparse_File) ? FILE_ATTRIBUTE_SPARSE_FILE : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Reparse_Point) ? FILE_ATTRIBUTE_REPARSE_POINT : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Compressed) ? FILE_ATTRIBUTE_COMPRESSED : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Offline) ? FILE_ATTRIBUTE_OFFLINE : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Not_Content_Indexed) ? FILE_ATTRIBUTE_NOT_CONTENT_INDEXED : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Encrypted) ? FILE_ATTRIBUTE_ENCRYPTED : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Integrity_Stream) ? FILE_ATTRIBUTE_INTEGRITY_STREAM : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Virtual) ? FILE_ATTRIBUTE_VIRTUAL : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_No_Scrub_Data) ? FILE_ATTRIBUTE_NO_SCRUB_DATA : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_EA) ? FILE_ATTRIBUTE_EA : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Pinned) ? FILE_ATTRIBUTE_PINNED : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Unpinned) ? FILE_ATTRIBUTE_UNPINNED : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Recall_On_Open) ? FILE_ATTRIBUTE_RECALL_ON_OPEN : 0u;
	fileAttr |= (attr & FileAttribute::File_Attribute_Recall_On_Data_Access) ? FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS : 0u;
	return fileAttr;
}

inline uint32 Win32GetFileCursorPosition(FileCursorPosition cursorPosition)
{
	switch (cursorPosition)
	{
	case FileCursorPosition::File_Current:
		return FILE_CURRENT;
	case FileCursorPosition::File_End:
		return FILE_END;
	default:
		return FILE_BEGIN;
	}
}

std::string fs::GetAbsolutePath(const char* path)
{
	constexpr uint32 pathBufferLength = 256;
	char absPath[pathBufferLength];
	GetFullPathNameA(path, pathBufferLength, absPath, NULL);
	return std::string{ absPath };
}

std::string fs::GetWorkingDirectory()
{
	constexpr uint32 bufferLength = 256;
	char currDir[bufferLength];
	GetCurrentDirectoryA(bufferLength, currDir);
	return std::string{ currDir };
}

bool fs::SetWorkingDirectory(const char* directory)
{
	return SetCurrentDirectoryA(directory);
}

bool fs::IsFileExist(const char* path)
{
	uint32 ret = GetFileAttributesA(path);
	if (ret == INVALID_FILE_ATTRIBUTES)
	{
		uint32 err = GetLastError();
		if (err == ERROR_FILE_NOT_FOUND)
		{
			return false;
		}
		// some other thing happened
		LOG_ERROR(LogChannel::LC_Platform, "IsFileExist failed with unhandled error code\n");
	}

	return (ret != FILE_ATTRIBUTE_DIRECTORY);
}

uint64 fs::GetFileSize(const char* filePath)
{
	WIN32_FIND_DATAA findFileData{};
	TORC_HANDLE handle = FindFirstFileA(
		filePath,
		&findFileData);
	if (handle == (TORC_HANDLE)((UINT_PTR)-1))
	{
		return -1;
	}
	return ((uint64)findFileData.nFileSizeHigh << 32) | findFileData.nFileSizeLow;
}

bool fs::IsDirectory(const char* path)
{
	uint32 ret = GetFileAttributesA(path);
	if (ret == INVALID_FILE_ATTRIBUTES)
	{
		uint32 err = GetLastError();
		if (err == ERROR_FILE_NOT_FOUND)
		{
			return false;
		}
		// some other thing happened
		LOG_ERROR(LogChannel::LC_Platform, "IsFileExist failed with unhandled error code\n");
	}

	return (ret == FILE_ATTRIBUTE_DIRECTORY);
}

bool fs::IsDirectoryEmpty(const char* path)
{
	return PathIsDirectoryEmptyA(path);
}

std::string fs::GetExtension(const char* path)
{
	int len = (int)strlen(path);
	for (int i = len - 1; i > -1; --i)
	{
		if (path[i] == '.')
		{
			return path + i + 1;
		}
	}
	return {};
}

std::string fs::GetDirectory(const char* path)
{
	int len = (int)strlen(path);
	for (int i = len - 1; i > -1; --i)
	{
		if (path[i] == defaultPathSeparator)
		{
			return std::string(path, i);
		}
	}
	return path;
}

std::string fs::GetParentDirectory(const char* path)
{
	int len = (int)strlen(path);
	for (int i = len - 1; i > -1; --i)
	{
		const char c = path[i];
		if (path[i] == defaultPathSeparator && i != len - 1)
		{
			return std::string(path, i);
		}
	}

	return path;
}

std::string fs::GetFilenameWithoutExtension(const char* path)
{
	int len = (int)strlen(path);
	int dotPos = 0;
	int separatorPos = 0;

	for (int i = len - 1; i > -1; --i)
	{
		if (path[i] == '.')
		{
			dotPos = i;
		}
		else if (path[i] == defaultPathSeparator)
		{
			separatorPos = i;
			break;
		}
	}

	if (separatorPos > dotPos)
	{
		return {};
	}

	return std::string(path + separatorPos + 1, dotPos - separatorPos - 1);
}

std::string fs::GetFilename(const char* path)
{
	int len = (int)strlen(path);
	int dotPos = 0;
	int separatorPos = 0;
	for (int i = len - 1; i > -1; --i)
	{
		if (path[i] == '.')
		{
			dotPos = i;
		}
		else if (path[i] == defaultPathSeparator)
		{
			separatorPos = i;
			break;
		}
	}

	if (separatorPos > dotPos || dotPos == 0)
	{
		return {};
	}

	return std::string(path + separatorPos + 1, len - separatorPos - 1);
}

std::string fs::ConvertPathSeparator(const char* path)
{
	int len = (int)strlen(path);

	std::string newStr;
	newStr.resize(len);

	for (int i = len - 1; i > -1; --i)
	{
		if ((path[i] == '\\' || path[i] == '/'))
		{
			newStr[i] = defaultPathSeparator;
		}
		else
		{
			newStr[i] = path[i];
		}
	}
	return newStr;
}

std::string fs::ConvertPathSeparator(const char* path, const char targetSeparator)
{
	int len = (int)strlen(path);

	std::string newStr;
	newStr.resize(len);

	for (int i = len - 1; i > -1; --i)
	{
		if ((path[i] == '\\' || path[i] == '/'))
		{
			newStr[i] = targetSeparator;
		}
		else
		{
			newStr[i] = path[i];
		}
	}
	return newStr;
}

void* fs::OpenFile(const char* fileName, FileAccessMode desiredAccess, FileShareMode shareMode, FileCreationFlag creationFlag)
{
	SECURITY_ATTRIBUTES securityAttributes;
	securityAttributes.bInheritHandle = true;
	securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	securityAttributes.lpSecurityDescriptor = NULL;

	HANDLE fileHandle = CreateFileA(fileName,
		Win32GetDesiredAccess(desiredAccess),
		Win32GetShareMode(shareMode),
		&securityAttributes,
		Win32GetCreationFlag(creationFlag),
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		// log
		uint32 err = GetLastError();
		LOG_ERROR(LogChannel::LC_Platform, "CreateFile failed. Error Code: %lu\n", err);
		return nullptr;
	}
	return fileHandle;
}

bool fs::CloseFile(TORC_HANDLE handle)
{
    bool ret = CloseHandle((HANDLE)handle);
    if (!ret)
    {
        uint32 lastError = GetLastError();
        OutputDebugStringA("Closing file handle failed.\n");
    }
    return ret;
}

uint32 fs::ReadFile(TORC_HANDLE handle, void* buffer, uint32 sizeInBytesToRead)
{
	uint32 actualBytesRead = 0;
	if (!::ReadFile((HANDLE)handle, buffer, sizeInBytesToRead, (LPDWORD)&actualBytesRead, NULL))
	{
		uint32 err = GetLastError();
		LOG_ERROR(LogChannel::LC_Platform, "ReadFile exited with ErrorCode: %lu", err);
		return -1;
	}
	return actualBytesRead;
}

uint32 fs::WriteFile(TORC_HANDLE handle, void* buffer, uint32 sizeInBytesToWrite)
{
	uint32 actualBytesWritten = 0;
	if (!::WriteFile((HANDLE)handle, buffer, sizeInBytesToWrite, (LPDWORD)&actualBytesWritten, NULL))
	{
		uint32 err = GetLastError();
		LOG_ERROR(LogChannel::LC_Platform, "WriteFile exited with ErrorCode: %lu", err);
		return -1;
	}
	uint32 err = GetLastError();
	return actualBytesWritten;
}

bool fs::CreateNewDirectory(const char* pathName)
{
    // second params is null, new directory will inherit security attrib from its parent
    bool ret = CreateDirectoryA(pathName, NULL);
    if (!ret)
    {
       uint32 err = GetLastError();
       if (err == ERROR_ALREADY_EXISTS)
       {
		   LOG_TRACE_INFO("Directory: %s already exists.", pathName);
       }
       else if (err == ERROR_PATH_NOT_FOUND)
       {
		   LOG_TRACE_INFO("Directory: %s is not found.", pathName);
       }
    }
    return ret;
}

FileInfo fs::GetFileInfoByHandle(TORC_HANDLE handle)
{
	BY_HANDLE_FILE_INFORMATION info;
	if (!GetFileInformationByHandle(handle, &info))
	{
		LOG_WARN(LogChannel::LC_Platform, "Retrieving file: %lu information has failed", handle);
	}
	return {info.dwFileAttributes, info.dwVolumeSerialNumber,
		*reinterpret_cast<uint64*>(&info.ftCreationTime),
		*reinterpret_cast<uint64*>(&info.ftLastAccessTime),
		* reinterpret_cast<uint64*>(&info.ftLastWriteTime),
		((uint64)info.nFileSizeHigh << 32) | info.nFileSizeLow,
		((uint64)info.nFileIndexHigh << 32) | info.nFileIndexLow,
		info.nNumberOfLinks
		};
}

bool fs::ConvertFileTimeToSystemTime(uint64 fileTime, SystemTime* out)
{
	FILETIME* ft = (FILETIME*)&fileTime;
	SYSTEMTIME sysTime;
	bool ret = FileTimeToSystemTime(ft, &sysTime);
	if (!ret)
	{
		uint32 err = GetLastError();
		//log
		return false;
	}
	SystemTime& t = *out;
	t = { sysTime.wYear, sysTime.wMonth, sysTime.wDayOfWeek, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds };

	return true;
}

uint64 fs::GetFileCursorPosition(TORC_HANDLE handle)
{
	long highPointer = 0;
	uint32 lowPosition = SetFilePointer(handle, 0, &highPointer, FILE_CURRENT);
	return (uint64)highPointer << 32 | lowPosition;
}

uint64 fs::SetFileCursorPosition(TORC_HANDLE handle, int64 position, FileCursorPosition relativePosition)
{
	long highPointer = 0;
	uint32 lowPosition = SetFilePointer(handle, position, &highPointer, Win32GetFileCursorPosition(relativePosition));
	return (uint64)highPointer << 32 | lowPosition;
}

uint64 fs::GetCharCount(TORC_HANDLE fileHandle)
{
	uint64 currPos = GetFileCursorPosition(fileHandle);
	uint64 newPosBegin = SetFileCursorPosition(fileHandle, 0, FileCursorPosition::File_Begin);
	uint64 newPosEnd = SetFileCursorPosition(fileHandle, 0, FileCursorPosition::File_End);
	uint64 charCount = newPosEnd - newPosBegin;

	// set back initial position
	uint64 posInitial = SetFileCursorPosition(fileHandle, currPos, FileCursorPosition::File_Begin);
	return charCount;
}

bool fs::SetEndOfFile(TORC_HANDLE fileHandle)
{
	bool hasSet = ::SetEndOfFile(fileHandle);
	ASSERT(hasSet == true, "Committing to file has failed");
	return hasSet;
}