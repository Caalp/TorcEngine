#include "Core/Std/Threading/Mutex.h"

#include <deque>
#include <future>

class GenericTaskQueue
{
public:
    GenericTaskQueue() = default;

    template<typename F>
    void PushTask(F&& task);

    bool Empty() const;
    bool ExecuteTask();
    void Clear();
     
private:
    Std::mutex m_mutex;
    std::deque<std::packaged_task<void()>> m_tasks;
 };

template<typename F>
inline void GenericTaskQueue::PushTask(F&& task)
{
    m_mutex.Lock();
    m_tasks.emplace_back(std::move(task));
    m_mutex.Unlock();
}