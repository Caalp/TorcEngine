#pragma once
#include <atomic>

namespace core
{
#if defined (_MSC_VER)
	template<typename E>
	static bool CAS(E& destination, E comperand, E exchange)
	{
		void* old = InterlockedCompareExchangePointer(reinterpret_cast<void**>(&destination), 
			(void*)*reinterpret_cast<uint64_t*>(&exchange), (void*) * reinterpret_cast<uint64_t*>(&comperand));
		
		return old == (void*)*reinterpret_cast<uint64_t*>(&comperand);
	}

#else
	template<typename E>
	static bool CAS(E& destination, E comperand, E exchange) { return false; }
#endif

	template<typename T>
	class Atomic
	{
		enum MemoryOrder {
			MEMORY_ORDER_RELAXED = std::memory_order::memory_order_relaxed,
			MEMORY_ORDER_CONSUME,
			MEMORY_ORDER_ACQUIRE,
			MEMORY_ORDER_RELEASE,
			MEMORY_ORDER_ACQ_REL,
			MEMORY_ORDER_SEQ_CST
		};
	public:
		constexpr Atomic() noexcept = default;
		constexpr Atomic(T desired) noexcept;
		Atomic(const Atomic&) = delete;

		void Store(T desired, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T Load(MemoryOrder order = MEMORY_ORDER_SEQ_CST) const noexcept;
		T Exchange(T desired, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T FetchAdd(T arg, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T* FetchAdd(std::ptrdiff_t arg, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T FetchSubtract(T arg, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T* FetchSubtract(std::ptrdiff_t arg, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T FetchAND(T arg, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T FetchOR(T arg, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		T FetchXOR(T arg, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		
		operator T() const noexcept;
				
		T operator++() noexcept;
		T operator++(int) noexcept;
		T operator--() noexcept;
		T operator--(int) noexcept;
		T operator+=(T arg) noexcept;
		T* operator+=(std::ptrdiff_t arg) noexcept;
		T operator-=(T arg) noexcept;
		T* operator-=(std::ptrdiff_t arg) noexcept;
		T operator&=(T arg) noexcept;
		T operator|=(T arg) noexcept;
		T operator^=(T arg) noexcept;

		bool CASWeak(T& expected, T desired, MemoryOrder success, MemoryOrder failure) noexcept;
		bool CASWeak(T& expected, T desired, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		bool CASStrong(T& expected, T desired, MemoryOrder success, MemoryOrder failure) noexcept;
		bool CASStrong(T& expected, T desired, MemoryOrder order = MEMORY_ORDER_SEQ_CST) noexcept;
		
	private:
		std::atomic<T> m_atomic;
	};

	template<typename T>
	inline constexpr Atomic<T>::Atomic(T desired) noexcept
		: m_atomic(desired)
	{
	}

	template<typename T>
	inline void Atomic<T>::Store(T desired, MemoryOrder order) noexcept
	{
		m_atomic.store(desired, (std::memory_order)order);
	}

	template<typename T>
	inline T Atomic<T>::Load(MemoryOrder order) const noexcept
	{
		return m_atomic.load((std::memory_order)order);
	}
	
template<typename T>
	inline T Atomic<T>::Exchange(T desired, MemoryOrder order) noexcept
	{
		return m_atomic.exchange(desired, (std::memory_order)order);
	}
	
	template<typename T>
	inline T Atomic<T>::FetchAdd(T arg, MemoryOrder order) noexcept
	{
		return m_atomic.fetch_add(arg, (std::memory_order)order);
	}
	
	template<typename T>
	inline T* Atomic<T>::FetchAdd(std::ptrdiff_t arg, MemoryOrder order) noexcept
	{
		return m_atomic.fech_add(arg, (std::memory_order)order);
	}
	
	template<typename T>
	inline T Atomic<T>::FetchSubtract(T arg, MemoryOrder order) noexcept
	{
		return m_atomic.fetch_sub(arg, (std::memory_order)order);
	}
	
	template<typename T>
	inline T* Atomic<T>::FetchSubtract(std::ptrdiff_t arg, MemoryOrder order) noexcept
	{
		return m_atomic.fetch_sub(arg, (std::memory_order)order);
	}
	
	template<typename T>
	inline T Atomic<T>::FetchAND(T arg, MemoryOrder order) noexcept
	{
		return m_atomic.fetch_and(arg, (std::memory_order)order);
	}
	
	template<typename T>
	inline T Atomic<T>::FetchOR(T arg, MemoryOrder order) noexcept
	{
		return m_atomic.fetch_or(arg, (std::memory_order)order);
	}
	
	template<typename T>
	inline T Atomic<T>::FetchXOR(T arg, MemoryOrder order) noexcept
	{
		return m_atomic.fetch_xor(arg, (std::memory_order)order);
	}

	template<typename T>
	inline Atomic<T>::operator T() const noexcept
	{
		return m_atomic.load();
	}

	template<typename T>
	inline T Atomic<T>::operator++() noexcept
	{
		return ++m_atomic;
	}

	template<typename T>
	inline T Atomic<T>::operator++(int) noexcept
	{
		return m_atomic++;
	}

	template<typename T>
	inline T Atomic<T>::operator--() noexcept
	{
		return --m_atomic;
	}

	template<typename T>
	inline T Atomic<T>::operator--(int) noexcept
	{
		return m_atomic--;
	}

	template<typename T>
	inline T Atomic<T>::operator+=(T arg) noexcept
	{
		return (m_atomic += arg);
	}
	template<typename T>
	inline T* Atomic<T>::operator+=(std::ptrdiff_t arg) noexcept
	{
		return (m_atomic += arg);
	}

	template<typename T>
	inline T Atomic<T>::operator-=(T arg) noexcept
	{
		return (m_atomic -= arg);
	}

	template<typename T>
	inline T* Atomic<T>::operator-=(std::ptrdiff_t arg) noexcept
	{
		return (m_atomic -= arg);
	}

	template<typename T>
	inline T Atomic<T>::operator&=(T arg) noexcept
	{
		return (m_atomic &= arg);
	}

	template<typename T>
	inline T Atomic<T>::operator|=(T arg) noexcept
	{
		return (m_atomic |= arg);
	}
	
	template<typename T>
	inline T Atomic<T>::operator^=(T arg) noexcept
	{
		return (m_atomic ^= arg);
	}
	
	template<typename T>
	inline bool Atomic<T>::CASWeak(T& expected, T desired, MemoryOrder success, MemoryOrder failure) noexcept
	{
		return m_atomic.compare_exchange_weak(expected, desired, (std::memory_order)sucess, (std::memory_order)failure);
	}
	
	template<typename T>
	inline bool Atomic<T>::CASWeak(T& expected, T desired, MemoryOrder order) noexcept
	{
		return m_atomic.compare_exchange_weak(expected, desired, (std::memory_order)order);
	}
	
	template<typename T>
	inline bool Atomic<T>::CASStrong(T& expected, T desired, MemoryOrder success, MemoryOrder failure) noexcept
	{
		return m_atomic.compare_exchange_strong(expected, desired, (std::memory_order)sucess, (std::memory_order)failure);
	}
	
	template<typename T>
	inline bool Atomic<T>::CASStrong(T& expected, T desired, MemoryOrder order) noexcept
	{
		return m_atomic.compare_exchange_strong(expected, desired, (std::memory_order)order);
	}
}