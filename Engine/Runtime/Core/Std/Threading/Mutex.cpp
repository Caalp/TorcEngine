#include "Mutex.h"

using namespace core;

Mutex::Mutex() noexcept
{}

void Mutex::Lock()
{
    m_mutex.lock();
}

void Mutex::Unlock()
{
    m_mutex.unlock();
}

bool Mutex::TryLock()
{
    return m_mutex.try_lock();
}

ScopedLock::ScopedLock(Mutex& m) noexcept
    : m_mutex(m)
{
    m_mutex.Lock();
}

ScopedLock::~ScopedLock()
{
    m_mutex.Unlock();
}