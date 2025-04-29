#include "FrameGraph/Job.h"

Job::Job(const Step& s)
	: step(&s)
{}

void Job::Execute()
{}