#pragma once
#include "Component/Component.h"

namespace Torc
{
	class ApplicationComponent : public Component
	{
	public:

		void Activate() override {}
		void Deactivate() override {}
	private:
	};
}