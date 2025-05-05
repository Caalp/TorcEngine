#pragma once
#include "Core/Base.h"

namespace Torc
{
	class Path;
	namespace IO
	{
		typedef uint64 SizeType;
		typedef uint64 StreamPos;
		typedef int64 StreamOffset;

		enum class OpenMode : uint32
		{
			Read = (1 << 0), //! Opens specified file readable.
			Write = (1 << 1), //! Opens specified file writable.
			ReadWrite = (Read | Write), //! Opens specified file as readable and writable.
			Binary = (1 << 2), //! Opens specified file as binary stream.
			Append = (1 << 3), //! Opens an existing file and appends to it.
			Create = (1 << 4), //! Creates a new file, if a file is already exists truncates it.
			CreateIfNotExist = (1 << 5), //! Creates a new file, if specified file is not exists.
		};

		enum class SeekPos
		{
			Begin,
			Current,
			End
		};

		enum class ShareMode : uint32
		{
			None = 0,
			Read = (1 << 0),
			Write = (1 << 1),
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
			uint32 m_fileAttributes;
			uint32 m_volumeSerialNumber;
			uint64 m_creationTime;
			uint64 m_lastAccessTime;
			uint64 m_lastWriteTime;
			uint64 m_fileSize;
			uint64 m_fileIndex;
			uint32 m_numberOfLinks;
			bool m_isInfoValid;
		};

		//! Result for IO operations
		struct Result
		{
			enum Code
			{
				Success,
				NotExists,
				InvalidHandle,
				Failed
			};

			Result() = default;
			Result(Code code)
				: m_resultCode(code)
			{}

			void Set(Code code)
			{
				m_resultCode = code;
			}

			Code m_resultCode;

			bool operator == (const Result::Code& rhs)
			{
				return this->m_resultCode == rhs;
			}

			bool operator != (const Result::Code& rhs)
			{
				return this->m_resultCode != rhs;
			}
		};

		//! Platform specific implementation, definations in platfrom folder
		class FileIOBase
		{
		public:
			static FileIOBase& GetInstance();
			static void SetInstance(FileIOBase* instance);

			virtual Result Open(const Path& file, OpenMode mode, FileHandle& handle) = 0;
			virtual SizeType Read(FileHandle handle, uint8* buffer, SizeType bytesToRead) = 0;
			virtual SizeType Write(FileHandle handle, void* buffer, uint32 bytesToWrite) = 0;
			virtual Result Close(FileHandle handle) = 0;
			virtual bool IsOpen(FileHandle handle) = 0;
			virtual StreamPos Tell(FileHandle handle) = 0;
			virtual StreamPos Seek(FileHandle handle, StreamOffset offset, SeekPos pos) = 0;
			virtual bool Eof(FileHandle handle) = 0;
			virtual int Peek(FileHandle handle) = 0;
			virtual SizeType GetLength(FileHandle handle) const = 0;
			virtual Result Flush(FileHandle handle) = 0;
			virtual bool SetEof(FileHandle handle) = 0;

			static FileInfo GetFileInfo(FileHandle handle);
			static bool IsDirectory(const Path& path);
			static bool IsDirectoryEmpty(const Path& path);
			static bool CreateNewDirectory(const Path& pathName);
			static uint64 GetFileSize(const Path& pathName);
			static bool IsExist(const Path& filepath);

			static Path GetAbsolutePath(const Path& path);
			static Path GetWorkingDirectory();
			static bool SetWorkingDirectory(const Path& directory);
			static bool ConvertFileTimeToSystemTime(uint64 fileTime, SystemTime* out);

		private:
			static FileIOBase* m_instance;
		};

		OpenMode operator|(OpenMode lhs, OpenMode rhs);
	}
}
