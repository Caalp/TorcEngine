#pragma once
#include <thread>

namespace Std
{
	class thread final : private std::thread
	{
	public:
		
		using id = std::thread::id;

		using std::thread::thread;

		template< class Function, class... Args>
		void start(Function&& f, Args&&... args)
		{
			if (m_busy == true)
			{
				return;
			}
			swap(std::thread(f, args...));
			m_busy = true;
		}

		void wait_to_finish()
		{
			join();
			m_busy = false;
		}

		bool is_busy()
		{
			return m_busy;
		}

		void detach()
		{
			m_detached = true;
			std::thread::detach();
		}

		void join()
		{
			m_busy = false;
			std::thread::join();
		}

		bool is_detached()
		{
			return m_detached;
		}

	private:
		bool m_busy = false;
		bool m_detached = false;
	};

	namespace this_thread = std::this_thread;
}
