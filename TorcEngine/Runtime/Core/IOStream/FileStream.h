#pragma once

static size_t Hash(std::string str)
{
	return std::hash<std::string>{}(str);
}

typedef size_t FILEHANDLE;

class File
{
public:
	File();
	File(TORC_HANDLE handle);
	bool IsValid() const;
	TORC_HANDLE GetHandle() const;
private:
	TORC_HANDLE m_fileHandle;
	uint8* m_buffer;
};

class FileStream
{
public:
	FileStream() = default;
	File OpenToRead(const char* filepath);
	File OpenToWrite(const char* filepath);
	File OpenToReadWrite(const char* filepath);
	File OpenToAppend(const char* filepath);

	uint32 Read(File* file, uint8* buff, uint32 size);
	uint32 Write(File* file, uint8* buff, uint32 size);
	void Close(File* file);
};

class FileManager
{
public:
	FILEHANDLE OpenForRead(const char* file);
	FILEHANDLE OpenForWrite(const char* file);
	FILEHANDLE OpenNewWrite(const char* file);

	void CloseFile(FILEHANDLE handle);
	File* GetFile(FILEHANDLE handle);

private:
	std::map<FILEHANDLE, File> m_fileMap;
};