#pragma once

namespace core
{
	class Timer
	{
	public:
		struct ElapsedTime
		{
			double elapsed;
			double ToSeconds()
			{
				return elapsed / 1000.0;
			}
			operator double() const { return elapsed; }
		};

	public:
		Timer();
		void Start();
		ElapsedTime Elapsed();

	private:
		__int64 frequency;
		__int64 startTime;
		double tickPerMs;
		double elapsedTime;
	};
}