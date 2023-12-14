#include "pch.h"

#include "SystemTimer.h"

SystemTimer::SystemTimer() 
	: m_startTime(0.0f)
	, m_finishTime(0.0f)
{
	if (!Torc::Platform::GetSystemFrequency(m_frequency))
	{
		m_frequency = 10'000'000;
	}

	m_ticksPerMs = m_frequency / 1000;
}

double SystemTimer::GetCurrentSysTime() const
{
	int64 time;
	Torc::Platform::GetSystemPerformanceCounter(time);
	return static_cast<double>(time) / (double)m_ticksPerMs;
}

double SystemTimer::GetRawFrameTime() const
{
	return m_rawFrameTime;
}

void SystemTimer::CalculateSmoothedFrameTime()
{
	m_smoothedFrameTime = 0.0f;
}

double SystemTimer::GetSmoothedFrameTime() const
{
	return m_smoothedFrameTime;
}

void SystemTimer::CalculateAverageFrameTime()
{
	double frameTimeSum = 0.0f;
	for (int i = 0; i < MAX_FRAME_TIME_COUNT; i++)
	{
		frameTimeSum += m_frameTimes[i];
	}

	m_averageFrameTime = frameTimeSum / MAX_FRAME_TIME_COUNT;
}

double SystemTimer::GetAverageFrameTime()
{
	return m_averageFrameTime;
}

void SystemTimer::UpdateTimer()
{
	m_finishTime = GetCurrentSysTime();
	m_rawFrameTime = m_finishTime - m_startTime;

	m_startTime = m_finishTime;

	for (int i = MAX_FRAME_TIME_COUNT - 2; i > -1; --i)
	{
		m_frameTimes[i + 1] = m_frameTimes[i];
	}

	if (m_rawFrameTime < 33.33)
	{
		// spin until reaching 0.4
		double tAccum = m_rawFrameTime;
		do
		{

			m_finishTime = GetCurrentSysTime();
			tAccum += m_finishTime - m_startTime;
			m_startTime = m_finishTime;
			

		} while (tAccum < 33.0);
		m_rawFrameTime = tAccum;
	}

	m_frameTimes[0] = m_rawFrameTime;

	double oldAveFrameTime = m_averageFrameTime;
	CalculateAverageFrameTime();
	double newAveFrameTime = m_averageFrameTime;
	if (newAveFrameTime > 0.4)
	{
		m_smoothedFrameTime = 0.4;
	}
	else
	{
		m_smoothedFrameTime = newAveFrameTime;
	}
}