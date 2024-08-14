#include "FileStream.h"
#include "Core/IO/Path/Path.h"

namespace Torc
{
	namespace IO
	{
		Result FileStream::Open(const Path& path, OpenMode mode)
		{
			FileIOBase& instance = FileIOBase::GetInstance();
			return instance.Open(path, mode, m_handle);
		}

		SizeType FileStream::Read(uint8* dest, uint64 size)
		{
			FileIOBase& instance = FileIOBase::GetInstance();
			return instance.Read(m_handle, dest, size);
		}

		SizeType FileStream::Write(uint8* buff, uint32 size)
		{
			FileIOBase& instance = FileIOBase::GetInstance();
			return instance.Write(m_handle, buff, size);
		}

		void FileStream::Close()
		{
			FileIOBase& instance = FileIOBase::GetInstance();
			instance.Close(m_handle);
		}
	}
}
