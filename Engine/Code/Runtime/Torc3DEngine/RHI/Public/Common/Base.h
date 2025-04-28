#pragma once
#include <Core/Std/intrusive_ptr.h>
#include <Core/Base.h>

namespace Torc
{
	namespace RHI
	{		
		template<typename T>
		using Ptr = Std::intrusive_ptr<T>;
	}
}