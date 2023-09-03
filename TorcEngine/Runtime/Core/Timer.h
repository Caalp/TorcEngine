#pragma once

namespace Torc
{
	class Timer
	{
	public:
		Timer() = default;
		bool StartTimer();
		void StopTimer();
		double GetElapsedTime() const;

	private:
		__int64 frequency;
		__int64 startTime;
		double tickPerMs;
		double elapsedTime;

	};
}
