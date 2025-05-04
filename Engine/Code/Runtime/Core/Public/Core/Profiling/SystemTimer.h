#pragma once
#include "Core/Base.h"

class SystemTimer
{
	enum { MAX_FRAME_TIME_COUNT = 100 };
public:
	SystemTimer();
	double GetCurrentSysTime() const;
	double GetRawFrameTime() const;
	void CalculateSmoothedFrameTime();
	double GetSmoothedFrameTime() const;
	void CalculateAverageFrameTime();
	double GetAverageFrameTime();
	void UpdateTimer();

private:
	double m_startTime;
	double m_finishTime;
	double m_rawFrameTime;
	double m_smoothedFrameTime;
	double m_averageFrameTime;
	double m_frameTimes[MAX_FRAME_TIME_COUNT];
	int64 m_frequency;
	int64 m_ticksPerMs;
};