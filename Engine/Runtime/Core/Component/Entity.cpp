#include "Entity.h"
#include "Core/Application.h"
#include "Core/Component/Component.h"
#include "Core/Component/ECManager.h"
#include "Core/Logging/Logger.h"

namespace Torc
{
	Entity* Entity::Create()
	{
		ECManager* ecFactory = gEnv->application->GetECManager();
		if (!ecFactory)
		{
			TE_Warning(LogChannel::LC_Core, "ECManager is not initialized, cannot create entity.");
			return nullptr;
		}
		return ecFactory->Create();
	}

	bool Entity::HasComponent(uint64 componentId)
	{
		core::ScopedLock lock{ m_mutex };
		for (ComponentBase* comp : m_components)
		{
			/*if (comp->GetId().m_id == componentId)
			{
				return comp;
			}*/
		}
		return false;
	}

	EntityId Entity::GetId() const
	{
		return m_id;
	}
}
