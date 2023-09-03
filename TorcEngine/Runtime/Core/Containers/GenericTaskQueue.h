
class GenericTaskQueue
{
public:
    GenericTaskQueue() = default;

    template<typename F>
    void PushTask(F&& task);

    bool ExecuteTask();
    void Clear();
 
private:
    std::mutex m_mutex;
    std::deque<std::packaged_task<void()>> m_tasks;
 };

template<typename F>
inline void GenericTaskQueue::PushTask(F&& task)
{
    m_mutex.lock();
    m_tasks.emplace_back(std::move(task));
    m_mutex.unlock();
}