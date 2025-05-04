#pragma once
#include "Core/IO/FileIOBase.h"

namespace Torc
{
	namespace IO
	{
		namespace Windows
		{
			class FileIO : public FileIOBase
			{
			public:
				Result Open(const Path& file, OpenMode mode, FileHandle& handle) override;
				SizeType Read(FileHandle handle, uint8* buffer, SizeType bytesToRead) override;
				SizeType Write(FileHandle handle, void* buffer, uint32 bytesToWrite) override;
				Result Close(FileHandle handle) override;
				bool IsOpen(FileHandle handle) override;
				StreamPos Tell(FileHandle handle) override;
				StreamPos Seek(FileHandle handle, StreamOffset offset, SeekPos pos) override;
				bool Eof(FileHandle handle) override;
				int Peek(FileHandle handle) override;
				SizeType GetLength(FileHandle handle) const override;
				Result Flush(FileHandle handle) override;
				bool SetEof(FileHandle handle) override;
			};
		}
	}
}
