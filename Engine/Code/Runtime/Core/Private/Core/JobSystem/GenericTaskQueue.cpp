#include "Core/JobSystem/GenericTaskQueue.h"

bool GenericTaskQueue::Empty() const
{
    return m_tasks.size() == 0;
}

bool GenericTaskQueue::ExecuteTask()
{
    m_mutex.lock();
    if (m_tasks.empty())
    {
        m_mutex.unlock();
        return false;
    }
    auto t = std::move(m_tasks.front());
    m_tasks.pop_front();
    m_mutex.unlock();
    t();
    return true;
}

void GenericTaskQueue::Clear()
{}