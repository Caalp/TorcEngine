#include "Core/IO/FileStream.h"
#include "Core/IO/Path/Path.h"

namespace Torc
{
	namespace IO
	{
		EStatus StreamBase::GetStatus() const
		{
			return m_status;
		}

		Result FileStream::Open(const Path& path, OpenMode mode)
		{
			FileIOBase& instance = FileIOBase::GetInstance();
			Result r = instance.Open(path, mode, m_handle);
			if (r.m_resultCode == Result::Success)
			{
				m_status = EStatus::Open;
			}
			return r;
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
			m_status = EStatus::Closed;
		}

		SizeType FileStream::GetLength() const
		{
			FileIOBase& instance = FileIOBase::GetInstance();
			return instance.GetLength(m_handle);
		}
	}
}
