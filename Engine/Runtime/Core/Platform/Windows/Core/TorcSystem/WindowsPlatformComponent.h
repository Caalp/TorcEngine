#pragma once
#include "Core/TorcSystem/SystemComponent.h"

namespace Torc
{
	/*namespace IO
	{
		class FileIOBase;
	}*/

	class WindowsPlatformComponent : public SystemComponent
	{
	public:
		TORC_COMPONENT(WindowsPlatformComponent)
		void Activate() override;
		void Deactivate() override;
	private:
		//IO::FileIOBase* m_fileIO;
	};
}
