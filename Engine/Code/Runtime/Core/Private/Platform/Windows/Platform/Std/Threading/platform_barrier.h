#pragma once
#include "platform_atomic.h"

#include <barrier>

namespace Std
{
	class arrival_token
	{

	};

	template<class CompletionFunction>
	class barrier
	{
	public:
		barrier();
		~barrier();

		barrier(const barrier&) = delete;
		barrier& operator=(const barrier&) = delete;

		arrival_token arrive(std::ptrdiff_t n = 1);
		void wait(arrival_token&& arrival) const;
		void arrive_and_wait();
		void arrive_and_drop();

		static constexpr std::ptrdiff_t max() { return 10; }
	private:
		arrival_token m_arrival_token;
	};
}
