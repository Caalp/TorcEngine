#pragma once
#include "Core/Base.h"
#include "Core/IO/FileIOBase.h"

namespace Torc
{
	class Path;
	namespace IO
	{	
		//! Generic base class for stream types
		class StreamBase
		{
		public:
			virtual ~StreamBase() = default;
			virtual Result Open(const Torc::Path& path, OpenMode mode) = 0;
			virtual SizeType Read(uint8* dest, uint64 size) = 0;
			virtual SizeType Write(uint8* buff, uint32 size) = 0;
			virtual void Close() = 0;
		};

		class FileStream : public StreamBase
		{
		public:
			FileStream() = default;
			Result Open(const Torc::Path& path, OpenMode mode) override;
			SizeType Read(uint8* dest, uint64 size) override;
			SizeType Write(uint8* buff, uint32 size) override;
			void Close() override;
		private:
			FileHandle m_handle;
		};
	}
}
