#include "FileIO.h"
#include "Core/Logging/Logger.h"
#include "Core/IO/Path/Path.h"

#include <Windows.h>
#include <fileapi.h>
#include <handleapi.h>
#include <errhandlingapi.h>


namespace Torc
{
	namespace IO
	{
		namespace Windows
		{
			inline uint32 Win32GetDesiredAccess(OpenMode access)
			{
				uint32 win32Access = 0;
				win32Access |= ((uint32)access & (uint32)OpenMode::Read) ? GENERIC_READ : 0u;
				win32Access |= ((uint32)access & (uint32)OpenMode::Write) ? GENERIC_WRITE : 0u;
				return win32Access;
			}

			inline uint32 Win32GetShareMode(ShareMode access)
			{
				uint32 win32Access = 0;
				win32Access |= ((uint32)access & (uint32)ShareMode::Read) ? FILE_SHARE_READ : 0u;
				win32Access |= ((uint32)access & (uint32)ShareMode::Write) ? FILE_SHARE_WRITE : 0u;
				return win32Access;
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

			inline uint32 Win32GetFileCursorPosition(SeekPos cursorPosition)
			{
				switch (cursorPosition)
				{
				case SeekPos::Current:
					return FILE_CURRENT;
				case SeekPos::End:
					return FILE_END;
				default:
					return FILE_BEGIN;
				}
			}

			inline uint32 Win32GetCreationFlag(OpenMode mode)
			{
				uint32 mask = ((uint32)mode & (uint32)OpenMode::Create) | ((uint32)mode & (uint32)OpenMode::Append) | ((uint32)mode & (uint32)OpenMode::CreateIfNotExist);
				switch ((OpenMode)mask)
				{
				case OpenMode::Create:
					return CREATE_ALWAYS;
				case OpenMode::Append:
					return OPEN_EXISTING;
				case OpenMode::CreateIfNotExist:
					return CREATE_NEW;
				default:
					return OPEN_EXISTING;
				}
			}

			Result FileIO::Open(const Path& file, OpenMode mode, FileHandle& handle)
			{
				SECURITY_ATTRIBUTES securityAttributes;
				securityAttributes.bInheritHandle = true;
				securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
				securityAttributes.lpSecurityDescriptor = NULL;

				HANDLE fileHandle = CreateFileA(file.GetView().c_str(),
												Win32GetDesiredAccess(mode),
												Win32GetShareMode(ShareMode::None),
												&securityAttributes,
												Win32GetCreationFlag(mode),
												FILE_ATTRIBUTE_NORMAL,
												NULL);
				Result code;
				if (fileHandle == INVALID_HANDLE_VALUE)
				{
					code.m_resultCode = Result::Failed;
					
					//DWORD error = GetLastError();

					return code;
				}

				code.m_resultCode = Result::Success;
				handle = fileHandle;
				return code;
			}

			SizeType FileIO::Read(FileHandle handle, uint8* buffer, SizeType bytesToRead)
			{
				uint32 actualBytesRead = 0;
				if (!::ReadFile((HANDLE)handle, buffer, bytesToRead, (LPDWORD)&actualBytesRead, NULL))
				{
					return -1;
				}
				return actualBytesRead;
			}

			SizeType FileIO::Write(FileHandle handle, void* buffer, uint32 bytesToWrite)
			{
				uint32 actualBytesWritten = 0;
				if (!::WriteFile((HANDLE)handle, buffer, bytesToWrite, (LPDWORD)&actualBytesWritten, NULL))
				{
					return -1;
				}
				return actualBytesWritten;
			}

			Result FileIO::Close(FileHandle handle)
			{
				Result code{Result::Success};
				bool ret = CloseHandle((HANDLE)handle);
				if (handle == INVALID_HANDLE_VALUE)
				{
					code.Set(Result::InvalidHandle);
				}
				if (!ret)
				{
					code.Set(Result::Failed);
				}
				return code;
			}

			bool FileIO::IsOpen(FileHandle handle)
			{
				return handle != INVALID_HANDLE_VALUE;
			}

			StreamPos FileIO::Tell(FileHandle handle)
			{
				long highPointer = 0;
				uint32 lowPosition = SetFilePointer(handle, 0, &highPointer, FILE_CURRENT);
				return (uint64)highPointer << 32 | lowPosition;
			}

			StreamPos FileIO::Seek(FileHandle handle, StreamOffset offset, SeekPos pos)
			{
				long highPointer = 0;
				uint32 lowPosition = SetFilePointer(handle, offset, &highPointer, Win32GetFileCursorPosition(pos));
				return (uint64)highPointer << 32 | lowPosition;
			}

			bool FileIO::Eof(FileHandle handle)
			{
				uint8 byte;
				const SizeType bytesRead = Peek(handle);
				return bytesRead == -1;
			}

			int FileIO::Peek(FileHandle handle)
			{
				if (handle == INVALID_HANDLE_VALUE)
				{
					return -1;
				}

				uint8 byte;
				const SizeType bytesRead = Read(handle, &byte, 1);
				if (bytesRead != 1)
				{
					return -1;
				}
				
				Seek(handle, -1, SeekPos::Current);
				return byte;
			}

			SizeType FileIO::GetLength(FileHandle handle) const
			{
				return ::GetFileSize(handle, 0);
			}

			Result FileIO::Flush(FileHandle handle)
			{
				Result code{ Result::Success };
				BOOL res = ::FlushFileBuffers(handle);
				if (!res)
				{
					code.Set(Result::Failed);
				}
				return code;
			}

			bool FileIO::SetEof(FileHandle handle)
			{
				return ::SetEndOfFile(handle);
			}
		}

		FileInfo FileIOBase::GetFileInfo(FileHandle handle)
		{
			BY_HANDLE_FILE_INFORMATION info;
			bool validInfo = true;
			if (!GetFileInformationByHandle(handle, &info))
			{
				validInfo = false;
			}
			return { info.dwFileAttributes, info.dwVolumeSerialNumber,
				*reinterpret_cast<uint64*>(&info.ftCreationTime),
				*reinterpret_cast<uint64*>(&info.ftLastAccessTime),
				*reinterpret_cast<uint64*>(&info.ftLastWriteTime),
				((uint64)info.nFileSizeHigh << 32) | info.nFileSizeLow,
				((uint64)info.nFileIndexHigh << 32) | info.nFileIndexLow,
				info.nNumberOfLinks,
				validInfo
			};
		}

		bool FileIOBase::IsDirectory(const Path& path)
		{
			uint32 ret = GetFileAttributesA(path.GetView().c_str());
			if (ret == INVALID_FILE_ATTRIBUTES)
			{
				uint32 err = GetLastError();
				if (err == ERROR_FILE_NOT_FOUND)
				{
					return false;
				}	
			}
			return (ret == FILE_ATTRIBUTE_DIRECTORY);
		}

		bool FileIOBase::IsDirectoryEmpty(const Path& path)
		{		
			return false;
		}

		bool FileIOBase::CreateNewDirectory(const Path& path)
		{
			// second params is null, new directory will inherit security attrib from its parent
			bool ret = CreateDirectoryA(path.GetView().c_str(), NULL);
			if (!ret)
			{
				uint32 err = GetLastError();
				if (err == ERROR_ALREADY_EXISTS)
				{
					TE_TraceInfo("Directory: %s already exists.", pathName);
				}
				else if (err == ERROR_PATH_NOT_FOUND)
				{
					TE_TraceInfo("Directory: %s is not found.", pathName);
				}
			}
			return ret;
		}

		uint64 FileIOBase::GetFileSize(const Path& path)
		{
			WIN32_FIND_DATAA findFileData{};
			TORC_HANDLE handle = FindFirstFileA(
				path.GetView().c_str(),
				&findFileData);
			if (handle == (TORC_HANDLE)((UINT_PTR)-1))
			{
				return -1;
			}
			return ((uint64)findFileData.nFileSizeHigh << 32) | findFileData.nFileSizeLow;
		}

		bool FileIOBase::IsExist(const Path& filepath)
		{
			uint32 ret = GetFileAttributesA(filepath.GetView().c_str());
			if (ret == INVALID_FILE_ATTRIBUTES)
			{
				uint32 err = GetLastError();
				if (err == ERROR_FILE_NOT_FOUND)
				{
					return false;
				}
				// some other thing happened
				return false;
			}

			return (ret != FILE_ATTRIBUTE_DIRECTORY);
		}

		Path GetAbsolutePath(const Path& path)
		{
			Path absPath;
			::GetFullPathNameA(path.GetView().c_str(), Torc::MaxPathLength, absPath.GetView().Data(), NULL);
			return absPath;
		}

		Path GetWorkingDirectory()
		{
			Path absPath;
			::GetCurrentDirectoryA(Torc::MaxPathLength, absPath.GetView().Data());
			return absPath;
		}

		bool SetWorkingDirectory(const Path& directory)
		{
			if (!FileIOBase::IsDirectory(directory))
			{
				return false;
			}
			return SetCurrentDirectoryA(directory.GetView().c_str());
		}

		bool ConvertFileTimeToSystemTime(uint64 fileTime, SystemTime* out)
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
	}
}
