#pragma once
#include <mutex>

namespace core
{
	class Mutex
	{
	public:
		Mutex() noexcept;
		Mutex(const Mutex&) = delete;
		void Lock();
		void Unlock();
		bool TryLock();
	private:
		std::mutex m_mutex;
	};

	class ScopedLock
	{
	public:
		ScopedLock(Mutex& m) noexcept;
		ScopedLock(const ScopedLock&) = delete;
		~ScopedLock();
	private:
		Mutex& m_mutex;
	};
}