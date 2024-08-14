#pragma once
#include "Core/Base.h"
#include "Core/Component/Entity.h"
#include "Core/Threading/Atomic.h"
#include "Core/Threading/Mutex.h"

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


		core::Atomic<EntityType> m_entityIdGen;
		core::Mutex m_mutex;
		std::unordered_map<EntityType, Entity*> m_entities;
	};

	// Impl
	template<typename TEntity, typename TAllocator>
	inline Entity* ECRegistry<TEntity, TAllocator>::Create()
	{
		EntityType id = m_entityIdGen++;
		Entity* entity = new Entity(id);
		{
			core::ScopedLock{ m_mutex };
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
		core::ScopedLock{ m_mutex };
		m_entities.erase(entityId);
	}

	/// <summary>
	/// Gets and returns entity if exists otherwise returns nullptr
	/// </summary>
	template<typename TEntity, typename TAllocator>
	inline Entity* ECRegistry<TEntity, TAllocator>::GetEntity(EntityId entityId)
	{
		core::ScopedLock{ m_mutex };
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
