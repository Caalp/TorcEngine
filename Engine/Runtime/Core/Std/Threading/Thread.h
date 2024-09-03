#pragma once
#include <thread>

namespace core
{
	class Thread
	{
	public:
		Thread() noexcept;
		~Thread() = default;

		template< class Function, class... Args>
		void Start(Function&& f, Args&&... args);

		Thread(const Thread&) = delete;
		Thread(Thread&&) = delete;

		bool IsFinished() const;
		bool IsDetached() const;
		uint64_t GetID() const;
		static uint32_t GetHardwareConcurreny();
		static size_t GetCurrentThreadID();

		void WaitToFinish();
		void Detach();

	private:
		bool m_isBusy;
		bool m_isDetached;
		std::thread m_thread;
	};

	template<class Function, class ...Args>
	inline void Thread::Start(Function&& f, Args && ...args)
	{
		if (m_isBusy == true)
		{
			return;
		}

		m_thread = std::thread(f, args...);
		m_isBusy = true;
	}
}
