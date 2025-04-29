#include "platform_atomic.h"

#include <windows.h>

#ifdef InterlockedCompareExchangePointer
#undef InterlockedCompareExchangePointer
#endif

namespace Std
{
	namespace Internal
	{
		void* InterlockedCompareExchangePointer(void* volatile* Destination, void* Exchange, void* Comperand)
		{
			return ::_InterlockedCompareExchangePointer(Destination, Exchange, Comperand);
		}
	}
}
