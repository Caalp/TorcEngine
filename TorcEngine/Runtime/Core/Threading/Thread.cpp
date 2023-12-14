#include "pch.h"
#include "Thread.h"
#include <sstream>

using namespace core;

Thread::Thread() noexcept
	: m_isDetached(false)
	, m_isBusy(false)
{}

bool Thread::IsFinished() const
{
	return !m_thread.joinable();
}

bool Thread::IsDetached() const
{
	return m_isDetached;
}

uint64_t Thread::GetID() const
{
	std::stringstream ss;
	ss << m_thread.get_id();
	return std::stoul(ss.str(), nullptr);
}

uint32_t Thread::GetHardwareConcurreny()
{
	return std::thread::hardware_concurrency();
}

size_t Thread::GetCurrentThreadID()
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	return std::stoul(ss.str(), nullptr);
}

void Thread::WaitToFinish()
{
	m_thread.join();
	m_isBusy = false;
}

void Thread::Detach()
{
	m_isDetached = true;
	m_thread.detach();
}