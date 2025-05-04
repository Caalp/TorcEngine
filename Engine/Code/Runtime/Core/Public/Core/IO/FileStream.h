#pragma once
#include "Core/Base.h"
#include "Core/IO/FileIOBase.h"

namespace Torc
{
	class Path;
	namespace IO
	{	
		enum class EStatus
		{
			Open,
			Closed,
			Uninitialized,
		};

		//! Generic base class for stream types
		class StreamBase
		{
		public:
			virtual ~StreamBase() = default;
			virtual Result Open(const Torc::Path& path, OpenMode mode) = 0;
			virtual SizeType Read(uint8* dest, uint64 size) = 0;
			virtual SizeType Write(uint8* buff, uint32 size) = 0;
			virtual void Close() = 0;
			virtual SizeType GetLength() const = 0;
			EStatus GetStatus() const;
		protected:
			EStatus m_status;
		};

		class FileStream : public StreamBase
		{
		public:
			FileStream() = default;
			Result Open(const Torc::Path& path, OpenMode mode) override;
			SizeType Read(uint8* dest, uint64 size) override;
			SizeType Write(uint8* buff, uint32 size) override;
			void Close() override;
			SizeType GetLength() const override;
		private:
			FileHandle m_handle;
		};
	}
}
