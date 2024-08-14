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

	class ComponentBase;

	template<typename, typename>
	class ECRegistry;

	class Entity
	{
	public:

		static Entity* Create();

		Entity(EntityId id)
			: m_id(id)
		{}

		// Assigns given component to entity, memory of component should be persist
		// outside of scope of this function. Function only stores pointer to passed component.
		// Function will return true if same type of component is not exists and passed one is assigned
		// otherwise, false.
		template<typename T>
		bool AssignComponent(T& component, bool replaceIfExist = false)
		{
			core::ScopedLock lock{ m_mutex };
			T* foundComponent = nullptr;
			size_t componentId = HashType<T>::Hash();
			for (ComponentBase* comp : m_components)
			{
				/*if (comp::GetId() == (uint64_t)componentId)
				{
					foundComponent =  static_cast<T*>(comp);
					break;
				}*/
			}
			if (foundComponent)
			{
				return false;
			}

			component.SetEntity(this);
			m_components.push_back(&component);
			return true;
		}

		/*template<typename T>
		bool CreateComponent(T& component)
		{
			core::ScopedLock lock{ m_mutex };
			T* foundComponent = nullptr;
			size_t componentId = HashType<T>::Hash();
			for (ComponentBase* comp : m_components)
			{
				if (comp::GetId() == (uint64_t)componentId)
				{
					foundComponent = static_cast<T*>(comp);
					break;
				}
			}
			if (foundComponent)
			{
				return false;
			}

			component.SetEntity(this);
			m_components.push_back(&component);
			return true;
		}*/

		template<typename T>
		T* RemoveComponent()
		{
			size_t componentId = HashType<T>::Hash();
			core::ScopedLock lock{ m_mutex };
			for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
			{
				if ((*iter)->GetId().m_id == (uint64_t)componentId)
				{
					component = *iter;
					m_components.erase(iter);
					return *iter;
				}
			}
			return nullptr;
		}

		template<typename T>
		T* GetComponent()
		{
			size_t componentId = HashType<T>::Hash();
			core::ScopedLock lock{ m_mutex };
			for (ComponentBase* comp : m_components)
			{
				if (comp->GetId().m_id == (uint64_t)componentId)
				{
					return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}

		bool HasComponent(uint64 componentId);
		EntityId GetId() const;

	private:
		/*template<typename T>
		T* GetComponentInternal()
		{
			size_t componentId = HashType<T>::Hash();
			core::ScopedLock lock{ m_mutex };
			for (ComponentBase* comp : m_components)
			{
				if (comp->GetId().m_id == (uint64_t)componentId)
				{
					return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}*/
	private:
		EntityId m_id;
		core::Mutex m_mutex;
		std::vector<ComponentBase*> m_components;
	};
}
