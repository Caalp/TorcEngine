#pragma once
#include "Core/Base.h"
#include "Core/Threading/Mutex.h"

#include <vector>

typedef uint64 EntityId;
typedef uint64 ComponentId;

template<typename Type>
struct HashType
{
	static const size_t Hash()
	{
		return std::hash<std::string_view>{}(typeid(Type).name());
	}
};

namespace Torc
{
	class Component;

	class Entity
	{
	public:

		static const EntityId InvalidEntityId = 0;

		Entity()
			: m_id(GenerateId())
			, m_allowDuplicateComponents(false)
		{}

		Entity(bool allowDuplicateComponents)
			: m_id(GenerateId())
			, m_allowDuplicateComponents(allowDuplicateComponents)
		{}

		//! Assigns given component to entity, memory of component should be persist
		//! outside of scope of this function. Function only stores pointer to passed component.
		//! Function will return true if same type of component is not exists and passed one is assigned
		//! otherwise, false.
		template<typename T>
		bool AssignComponent(T& component)
		{
			core::ScopedLock lock{ m_mutex };
			if (!m_allowDuplicateComponents)
			{
				for (Component* comp : m_components)
				{
					if (comp->IsSameAs(*comp))
					{
						return false;
					}
				}
			}
			component.SetEntity(this);
			m_components.push_back(&component);
			return true;
		}

		template<typename T>
		T* RemoveComponent()
		{
			core::ScopedLock lock{ m_mutex };
			for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
			{
				if ((*iter)->IsSameAs(*(*iter)))
				{
					T* component = (T*)*iter;
					m_components.erase(iter);
					return component;
				}
			}
			return nullptr;
		}

		template<typename T>
		T* GetComponent()
		{
			core::ScopedLock lock{ m_mutex };
			for (Component* comp : m_components)
			{
				if (comp->IsSameAs(*comp))
				{
					return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}

		bool HasComponent(const Component* component);
		EntityId GetId() const;

	private:

		static EntityId GenerateId();

		EntityId m_id;
		bool m_allowDuplicateComponents;
		core::Mutex m_mutex;
		std::vector<Component*> m_components;
	};
}
