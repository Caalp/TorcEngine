#pragma once
#include "Core/Base.h"
#include "Core/TorcStd/String/String.h"

typedef uint64 ComponentId;

#define TORC_RTTI(_className, _uuid, _parent)

#define TORC_COMPONENT(_name)\
	static constexpr const char* _componentName = #_name;\
	virtual TorcStd::string GetName() const {return _name::_componentName;}\

#define TORC_BASE_COMPONENT_DECL(_name)\
	virtual TorcStd::string GetName() const = 0;\
	virtual bool IsSameAs(const Component& comp) const { return comp.GetName() == this->GetName(); }\


namespace Torc
{
	//! Base component class for all components
	class Component
	{
		friend class Entity;
	public:

		TORC_BASE_COMPONENT_DECL(Component)
		virtual ~Component();

		Entity* GetEntity();
		void SetEntity(Entity* ownerEntity);

		virtual void Activate();
		virtual void Deactivate();

	private:
		Entity* m_ownerEntity;
	};
}
