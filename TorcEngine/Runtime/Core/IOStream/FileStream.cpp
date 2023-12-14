#include "pch.h"
#include "FileStream.h"
#include "Platform/FileSystem.h"

File::File()
	: m_fileHandle((TORC_HANDLE)((UINT_PTR)-1))
{}

File::File(TORC_HANDLE handle)
	: m_fileHandle(handle)
{}

bool File::IsValid() const
{
	return m_fileHandle != (TORC_HANDLE)((UINT_PTR) - 1);
}

TORC_HANDLE File::GetHandle() const
{
	return m_fileHandle;
}

File FileStream::OpenToRead(const char* filePath)
{
	void* handle = fs::OpenFile(filePath, FileAccessMode::Access_Read, FileShareMode::Share_None, FileCreationFlag::Open_Existing);
	return File{ (TORC_HANDLE)handle };
}

File FileStream::OpenToWrite(const char* filePath)
{
	void* handle = fs::OpenFile(filePath, FileAccessMode::Access_Write, FileShareMode::Share_Read, FileCreationFlag::Open_Existing);
	return File();
}

File FileStream::OpenToReadWrite(const char* filepath)
{
	return File();
}

File FileStream::OpenToAppend(const char* filepath)
{
	return File();
}

uint32 FileStream::Read(File* file, uint8* buff, uint32 size)
{
	return fs::ReadFile(file->GetHandle(), (void*)buff, size);
}

uint32 FileStream::Write(File* file, uint8* buff, uint32 size)
{
	return uint32();
}

void FileStream::Close(File* file)
{
	fs::CloseFile(file->GetHandle());
}

FILEHANDLE FileManager::OpenForRead(const char* file)
{
	return FILEHANDLE();
}

FILEHANDLE FileManager::OpenForWrite(const char* file)
{
	return FILEHANDLE();
}

FILEHANDLE FileManager::OpenNewWrite(const char* file)
{
	return FILEHANDLE();
}

void FileManager::CloseFile(FILEHANDLE handle)
{
}

File* FileManager::GetFile(FILEHANDLE handle)
{
	return nullptr;
}