#pragma once
#include "Core/Component/Component.h"

namespace Torc
{
	class ApplicationComponent : public Component
	{
	public:
		TORC_RTTI(ApplicationComponent, "{F599FFA0-8B6C-4C93-A746-5C29D523CCC9}", Component);
		TORC_CLASS_ALLOCATOR(ApplicationComponent, DefaultSystemAllocator);
		void Activate() override {}
		void Deactivate() override {}
	};
}