#include "FileIOBase.h"
#include "Core/Logging/Logger.h"

namespace Torc
{
	namespace IO
	{
		FileIOBase* FileIOBase::m_instance = nullptr;

		FileIOBase& FileIOBase::GetInstance()
		{
			//TE_Assert(instance != nullptr, "FileIOBase is null");
			return *m_instance;
		}

		void FileIOBase::SetInstance(FileIOBase* instance)
		{
			//TE_Assert(instance != nullptr, "Passed FileIOInstance is null");
			m_instance = instance;
		}

		OpenMode operator|(OpenMode lhs, OpenMode rhs)
		{
			return (OpenMode)((uint32)lhs | (uint32)rhs);
		}
	}
}
