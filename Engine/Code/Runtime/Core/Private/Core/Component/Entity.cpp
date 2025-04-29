#include "Component/Entity.h"
#include "Application.h"
#include "Component/Component.h"
#include "Component/ECManager.h"
#include "Logging/Logger.h"

namespace Torc
{

	static Std::atomic<EntityId> s_entityId{1};

	EntityId Entity::GenerateId()
	{
		EntityId newId = s_entityId++;
		return newId;
	}

	bool Entity::HasComponent(const Component* component)
	{
		Std::scoped_lock lock{ m_mutex };
		for (Component* comp : m_components)
		{
			if (comp->IsSameAs(*component))
			{
				return true;
			}
		}
		return false;
	}

	EntityId Entity::GetId() const
	{
		return m_id;
	}
}
