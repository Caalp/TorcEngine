#include "pch.h"
#include "Core/Timer.h"
#include "Platform/Platform.h"

using namespace Torc;
bool Timer::StartTimer()
{
	// WinAPI function gets the performance-frequency counter in seconds.
	// If it returns zero that means system doesn't support high-resolution
	// counter. ( per unit of time in seconds)

	//QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	Platform::GetSystemFrequency(frequency);

	if (frequency == 0)
	{
		return false;
	}

	// Divide it by 1000 to find occurence in ms
	tickPerMs = (float)(frequency / 1000);

	// Retrieve current value of performance counter and save it into startTime
	//QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	Platform::GetSystemPerformanceCounter(startTime);

	return true;
}

void Timer::StopTimer()
{
	// 64-bit int for storing current time
	__int64 currentTime = 0;
	// Get the current value of performance counter 
	//QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	Platform::GetSystemPerformanceCounter(currentTime);
	// calculate the difference of current and starting time
	__int64 difference = currentTime - startTime;
	// in order to calculate the frameTime in ms we should divide it by tickPerMs
	// such as if it is capable of ticking 20 times per ms how much time it will take to
	// tick to get equal to difference(variable)
	elapsedTime = difference / tickPerMs;

	// After calculation set the startTime as currentTime for next run countinue from there
	startTime = currentTime;
}

double Timer::GetElapsedTime() const
{
	return elapsedTime;
}