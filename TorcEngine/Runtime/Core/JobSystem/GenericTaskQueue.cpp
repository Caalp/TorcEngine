#include "pch.h"
#include "GenericTaskQueue.h"

bool GenericTaskQueue::Empty() const
{
    return m_tasks.size() == 0;
}

bool GenericTaskQueue::ExecuteTask()
{
    m_mutex.Lock();
    if (m_tasks.empty())
    {
        m_mutex.Unlock();
        return false;
    }
    auto t = std::move(m_tasks.front());
    m_tasks.pop_front();
    m_mutex.Unlock();
    t();
    return true;
}

void GenericTaskQueue::Clear()
{}