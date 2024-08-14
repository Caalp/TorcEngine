#include "Core/Profiling/Timer.h"
#include "Core/Platform/Platform.h"

using namespace core;

core::Timer::Timer()
{
	// WinAPI function gets the performance-frequency counter in seconds.
	// If it returns zero that means system doesn't support high-resolution
	// counter. ( per unit of time in seconds)

	// returns freq in secs
	Torc::Platform::GetSystemFrequency(frequency);

	// Divide it by 1000 to find occurence in ms
	tickPerMs = (double)(frequency / 1000.0);
}

void Timer::Start()
{
	// Retrieve current value of performance counter and save it into startTime
	Torc::Platform::GetSystemPerformanceCounter(startTime);
}

Timer::ElapsedTime Timer::Elapsed()
{
	// 64-bit int for storing current time/ticks
	__int64 currentTime = 0;

	// Get the number of ticks
	Torc::Platform::GetSystemPerformanceCounter(currentTime);

	// calculate the difference of current and starting time
	// which gives the number of ticks happened since begining
	__int64 difference = currentTime - startTime;

	// total time that passed in milliseconds during ticks
	elapsedTime = difference / tickPerMs;

	// After calculation set the startTime as currentTime for next run countinue from there
	startTime = currentTime;

	return { elapsedTime };
}