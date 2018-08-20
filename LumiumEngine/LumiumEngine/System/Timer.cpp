#include "Timer.hpp"
#include <thread>

lumi::system::Timer::Timer()
{
}

lumi::system::Timer::~Timer()
{
}

void lumi::system::Timer::startTime()
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_endTime = std::chrono::high_resolution_clock::now();
}

double lumi::system::Timer::getTime()
{
	m_startTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<double, std::milli>(m_startTime - m_endTime).count();
}

void lumi::system::Timer::sleepCycle()
{
	auto workTime = getTime();
	if (workTime < m_timeStep)
	{
		std::chrono::duration<double, std::milli> delta_ms(m_timeStep - workTime);
		auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
		std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
	}
	m_endTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = m_endTime - m_startTime;
	m_frameTime = workTime + deltaTime.count();
}

void lumi::system::Timer::setTimeStep(int timeStep)
{
	m_timeStep = 1000 / static_cast<double>(timeStep);
}

double lumi::system::Timer::getFrameTime()
{
	return m_frameTime;
}

double lumi::system::Timer::getElapsedTime()
{
	return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - m_startTime).count();
}
