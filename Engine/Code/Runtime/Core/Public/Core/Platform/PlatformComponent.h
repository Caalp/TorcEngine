#pragma once
#include "Core/System/SystemComponent.h"

namespace Torc
{
	namespace IO
	{
		class FileIOBase;
	}

	class PlatformComponent : public SystemComponent
	{
		friend class System;
	private:
		static PlatformComponent* Create();
	protected:
		IO::FileIOBase* m_fileIO;
	};
}

