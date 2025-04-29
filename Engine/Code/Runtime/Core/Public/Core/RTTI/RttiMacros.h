#pragma once
#include "RTTI/TypeList.h"
#include "Math/Uuid.h"

//! TORC_RTTI takes argument to _className which is the name of the class that is using this define,
//! generated uuid for this class, and variable number of base classes that _className is inheriting from.
//! TODO(cay): __VA_ARGS__ should be unrolled to handle paranthesis. Currently, it wouldn't work if there are
//! parenthesis around list of parent classes.
//! TODO(cay): We have to handle recursive look-ups into parent's parent's inheritence if exists
#define TORC_RTTI(_className, _classUuid, ...)\
	typedef _className ThisType;\
	typedef typename Torc::NoDuplicates<Torc::BuildTypeList<_className, __VA_ARGS__>::Result>::Result _torcRttiTypeList;\
	static constexpr Torc::Uuid _torcRttiUuid{_classUuid};\
	const char* _torcGetClassName() const { return #_className; }\
	template<typename T> static bool IsTypeOf() {return Torc::HasType<T, Torc::TypeList<_torcRttiTypeList::type, _torcRttiTypeList::rest>>::value;}

