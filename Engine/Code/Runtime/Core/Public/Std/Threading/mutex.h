#pragma once

#include <Platform/Std/Threading/platform_mutex.h>

namespace Std
{
	class scoped_lock
	{
	public:
		scoped_lock(mutex& m) noexcept;
		scoped_lock(const scoped_lock&) = delete;
		scoped_lock& operator=(const scoped_lock&) = delete;
		~scoped_lock();
	private:
		mutex& m_mutex;
	};
}
