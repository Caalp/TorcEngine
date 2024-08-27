#include "Entity.h"
#include "Core/Application.h"
#include "Core/Component/Component.h"
#include "Core/Component/ECManager.h"
#include "Core/Logging/Logger.h"

namespace Torc
{

	static core::Atomic<EntityId> s_entityId{1};

	EntityId Entity::GenerateId()
	{
		EntityId newId = s_entityId++;
		return newId;
	}

	bool Entity::HasComponent(const Component* component)
	{
		core::ScopedLock lock{ m_mutex };
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
