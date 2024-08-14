#pragma once
#include "Core/RTTI/TypeList.h"

//! TORC_RTTI takes argument to _className which is the name of the class that is using this define,
//! generated uuid for this class, and variable number of base classes that _className is inheriting from.
//! TODO(cay): __VA_ARGS__ should be unrolled to handle paranthesis. Currently, it wouldn't work if there are
//! parenthesis around list of parent classes.
#define TORC_RTTI(_className, _classUuid, ...)\
	static Torc::TypeList<_className, __VA_ARGS__> _torcRttiTypeList;\
	static Uuid _torcRttiUuid(_classUuid);\
	const char* _torcGetClassName() { return #_className; }
