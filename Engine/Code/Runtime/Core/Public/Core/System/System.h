#pragma once

namespace Torc
{

	class SystemComponent;

	class System
	{
	public:
		void Initialize();
		void Shutdown();

		void Activate();
		void Deactivate();
	
	private:

		SystemComponent* m_platformComponent;
	};
}
