#pragma once
#include "Core/Component/Component.h"

namespace Torc
{
	//! SystemComponent is responsible with initialization of all core systems
	class SystemComponent : public Component
	{
	public:
		// {E7D3F93C-C712-42C4-8881-71D93D7CF885}
		TORC_COMPONENT(SystemComponent)
		~SystemComponent() = default;

		void Activate() override {};
		void Deactivate() override {};
	
	protected:
		
	};

	/*
	* Ther will be an ApplicationComponent which will be extended by specific type of application
	* that we might support Game and Editor. This will serve as an central point for application specific
	* behaviour and possibly can activate and deactive related components for type of use required by component itself.
	*/
}