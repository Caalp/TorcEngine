#pragma once
#include "Core/Platform/PlatformComponent.h"

namespace Torc
{
	namespace IO
	{
		class FileIOBase;
	}

	class WindowsPlatformComponent : public PlatformComponent
	{
	public:

		WindowsPlatformComponent();
		~WindowsPlatformComponent() override;


		TORC_CLASS_ALLOCATOR(WindowsPlatformComponent, DefaultSystemAllocator);
		void Activate() override;
		void Deactivate() override;
	};
}
