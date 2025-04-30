#pragma once
#include "Core/Component/Entity.h"

class SystemGlobalEnvironment;

namespace Torc
{
	template<typename, typename>
	class ECRegistry;

	// EntityComponent manager
	class ECManager final
	{
	public:
		static bool StartUp();
		static void Shutdown();
		static ECManager* GetInstance();

		Entity* Create();
		void Destroy(Entity* entity);
		Entity* GetEntity(Entity* entity);
		bool IsExist(Entity* entity);

	protected:
		ECManager(SystemGlobalEnvironment* gEnv);
		~ECManager();
	private:
		ECRegistry<EntityId, void>* m_registry;
		static ECManager* m_instance;
	};
}
