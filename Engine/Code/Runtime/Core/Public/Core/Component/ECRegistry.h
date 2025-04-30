#pragma once
#include "Core/Base.h"
#include "Core/Component/Entity.h"
#include "Core/Std/Threading/Atomic.h"
#include "Core/Std/Threading/Mutex.h"

#include <unordered_map>

namespace Torc
{
	template<typename TEntity, typename TAllocator>
	class ECRegistry
	{
		friend class ECManager;
		using EntityType = TEntity;
		using Allocator = TAllocator;
	public:
		ECRegistry()
			: m_entityIdGen(0)
		{}

	private:
		Entity* Create();
		void Destroy(EntityId entityId);
		Entity* GetEntity(EntityId entityId);
		bool IsExist(EntityId entityId);


		Std::atomic<EntityType> m_entityIdGen;
		Std::mutex m_mutex;
		std::unordered_map<EntityType, Entity*> m_entities;
	};

	// Impl
	template<typename TEntity, typename TAllocator>
	inline Entity* ECRegistry<TEntity, TAllocator>::Create()
	{
		EntityType id = m_entityIdGen++;
		Entity* entity = new Entity(id);
		{
			Std::scoped_lock{ m_mutex };
			m_entities.emplace(id, entity);
		}
		return entity;
	}

	/// <summary>
	/// delete entity from registry
	/// </summary>
	template<typename TEntity, typename TAllocator>
	inline void ECRegistry<TEntity, TAllocator>::Destroy(EntityId entityId)
	{
		Std::scoped_lock{ m_mutex };
		m_entities.erase(entityId);
	}

	/// <summary>
	/// Gets and returns entity if exists otherwise returns nullptr
	/// </summary>
	template<typename TEntity, typename TAllocator>
	inline Entity* ECRegistry<TEntity, TAllocator>::GetEntity(EntityId entityId)
	{
		Std::scoped_lock{ m_mutex };
		if (auto item = m_entities.find(entityId); item != m_entities.end())
		{
			return item->second;
		}
		return nullptr;
	}

	/// <summary>
	/// return true if entity exists and not null otherwise false
	/// </summary>
	template<typename TEntity, typename TAllocator>
	inline bool ECRegistry<TEntity, TAllocator>::IsExist(EntityId entityId)
	{
		return GetEntity(entityId) != nullptr;
	}
}
