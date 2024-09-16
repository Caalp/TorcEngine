#include "Mutex.h"

namespace Std
{
    scoped_lock::scoped_lock(mutex& m) noexcept
        : m_mutex(m)
    {
        m_mutex.lock();
    }

    scoped_lock::~scoped_lock()
    {
        m_mutex.unlock();
    }
}
