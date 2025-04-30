#include "Core/Component/ECManager.h"
#include "Core/Component/Entity.h"
#include "Core/Component/ECRegistry.h"
#include "Core/Application.h"
#include "Core/System/ISystem.h"

namespace Torc
{
	ECManager* ECManager::m_instance = nullptr;
	bool ECManager::StartUp()
	{
		if (m_instance == nullptr)
		{
			m_instance = new ECManager(gEnv);
		}
		return true;
	}

	void ECManager::Shutdown()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	ECManager* ECManager::GetInstance()
	{
		if (!m_instance)
		{
			StartUp();
		}
		return m_instance;
	}

	Entity* ECManager::Create()
	{
		return m_registry->Create();
	}
	void ECManager::Destroy(Entity* entity)
	{
		if (entity == nullptr)
		{
			return;
		}
		m_registry->Destroy(entity->GetId());
	}
	Entity* ECManager::GetEntity(Entity* entity)
	{
		if (entity == nullptr)
		{
			return nullptr;
		}
		return m_registry->GetEntity(entity->GetId());
	}
	bool ECManager::IsExist(Entity* entity)
	{
		if (entity == nullptr)
		{
			return false;
		}
		return m_registry->IsExist(entity->GetId());
	}

	ECManager::ECManager(SystemGlobalEnvironment* gEnv)
	{
		m_registry = new ECRegistry<EntityId, void>();
		//gEnv->application->SetECManager(this);
	}

	ECManager::~ECManager()
	{
		if (m_registry)
		{
			delete m_registry;
		}
	}
}
