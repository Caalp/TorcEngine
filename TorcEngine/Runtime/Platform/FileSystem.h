#pragma once

#ifdef _WIN64
static const char defaultPathSeparator = '\\';
#else
static const char defaultPathSeparator = '/';
#endif

enum class FileAccessMode : uint32
{
	Access_Read = (1 << 0),
	Access_Write = (1 << 1),
	Access_ReadWrite = (Access_Read | Access_Write),
};

enum class FileShareMode : uint32
{
	Share_None = 0,
	Share_Read	= (1 << 0),
	Share_Write = (1 << 1),
};

enum class FileCreationFlag : uint32
{
	Create_Always = (1 << 0),
	Create_New = (1 << 1),
	Open_Always = (1 << 2),
	Open_Existing = (1 << 3),
	Truncate_Existing = (1 << 4)
};

enum FileAttribute : uint32
{
	File_Attribute_ReadOnly = (1 << 0),
	File_Attribute_Hidden = (1 << 1),
	File_Attribute_System = (1 << 2),
	File_Attribute_Directory = (1 << 3),
	File_Attribute_Archive = (1 << 4),
	File_Attribute_Device = (1 << 5),
	File_Attribute_Normal = (1 << 6),
	File_Attribute_Temporary = (1 << 7),
	File_Attribute_Sparse_File = (1 << 8),
	File_Attribute_Reparse_Point = (1 << 9),
	File_Attribute_Compressed = (1 << 10),
	File_Attribute_Offline = (1 << 11),
	File_Attribute_Not_Content_Indexed = (1 << 12),
	File_Attribute_Encrypted = (1 << 13),
	File_Attribute_Integrity_Stream = (1 << 14),
	File_Attribute_Virtual = (1 << 15),
	File_Attribute_No_Scrub_Data = (1 << 16),
	File_Attribute_EA = (1 << 17),
	File_Attribute_Pinned = (1 << 18),
	File_Attribute_Unpinned = (1 << 19),
	File_Attribute_Recall_On_Open = (1 << 20),
	File_Attribute_Recall_On_Data_Access = (1 << 21)
};

struct FileInfo
{
	uint32 fileAttributes;
	uint32 volumeSerialNumber;
	uint64 creationTime;
	uint64 lastAccessTime;
	uint64 lastWriteTime;
	uint64 fileSize;
	uint64 fileIndex;
	uint32 numberOfLinks;
};

enum FileCursorPosition
{
	File_Begin = (1 << 0),
	File_Current = (1 << 1),
	File_End = (1 << 2)
};

namespace fs
{
	std::string GetAbsolutePath(const char* path);
	std::string GetWorkingDirectory();
	bool SetWorkingDirectory(const char* directory);
	bool IsFileExist(const char* path);

	// Returns file size in bytes
	uint64 GetFileSize(const char* path);
	bool IsDirectory(const char* path);
	bool IsDirectoryEmpty(const char* path);
	std::string GetExtension(const char* path);
	std::string GetDirectory(const char* path);
	std::string GetParentDirectory(const char* path);
	std::string GetFilenameWithoutExtension(const char* path);
	std::string GetFilename(const char* path);
	std::string ConvertPathSeparator(const char* path);
	std::string ConvertPathSeparator(const char* path, const char targetSeparator);

	void* OpenFile(const char* fileName, FileAccessMode desiredAccess, 
				   FileShareMode shareMode, FileCreationFlag creationFlag);
    bool CloseFile(TORC_HANDLE handle);
	uint32 ReadFile(TORC_HANDLE handle, void* buffer, uint32 sizeInBytesToRead);
	uint32 WriteFile(TORC_HANDLE handle, void* buffer, uint32 sizeInBytesToWrite);
	bool CreateNewDirectory(const char* pathName);
	FileInfo GetFileInfoByHandle(TORC_HANDLE handle);
	bool ConvertFileTimeToSystemTime(uint64 fileTime, SystemTime* out);
	uint64 GetFileCursorPosition(TORC_HANDLE handle);
	uint64 SetFileCursorPosition(TORC_HANDLE handle, int64 position, 
								 FileCursorPosition relativePosition = FileCursorPosition::File_Current);
	uint64 GetCharCount(TORC_HANDLE fileHandle);
	bool SetEndOfFile(TORC_HANDLE fileHandle);
}