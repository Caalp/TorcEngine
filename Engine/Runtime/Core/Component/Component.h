#pragma once
#include "Core/Base.h"
#include "Core/Std/String/String.h"

typedef uint64 ComponentId;

#define TORC_COMPONENT(_name)\
	static constexpr const char* _componentName = #_name;\
	virtual Std::string GetName() const {return _name::_componentName;}\

#define TORC_BASE_COMPONENT_DECL(_name)\
	virtual Std::string GetName() const = 0;\
	virtual bool IsSameAs(const Component& comp) const { return comp.GetName() == this->GetName(); }\


namespace Torc
{
	class Entity;
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
