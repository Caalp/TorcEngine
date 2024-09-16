#pragma once
#include <atomic>

namespace Std
{
	namespace Internal
	{
		void* InterlockedCompareExchangePointer(void* volatile* Destination, void* Exchange, void* Comperand);
	}

	template<typename T>
	struct atomic : std::atomic<T>
	{
		template<typename E>
		static bool atomic_cas(E& destination, E comperand, E exchange)
		{
			void* old = Internal::InterlockedCompareExchangePointer(reinterpret_cast<void**>(&destination),
														  (void*)*reinterpret_cast<uint64_t*>(&exchange), (void*)*reinterpret_cast<uint64_t*>(&comperand));

			return old == (void*)*reinterpret_cast<uint64_t*>(&comperand);
		}
	};
}
