#include "Component/Component.h"

namespace Torc
{
	Component::~Component()
	{
	}

	// ComponentBase Impl
	Entity* Component::GetEntity()
	{
		return m_ownerEntity;
	}

	void Component::SetEntity(Entity* ownerEntity)
	{
		m_ownerEntity = ownerEntity;
	}

	void Component::Activate()
	{
	}

	void Component::Deactivate()
	{
	}

	/*ComponentId ComponentBase::GetId() const
	{
		return m_id;
	}*/
}
