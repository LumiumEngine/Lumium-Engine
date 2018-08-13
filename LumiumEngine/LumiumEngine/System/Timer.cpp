#include "Timer.hpp"

lumi::system::Timer::Timer()
{
}

lumi::system::Timer::~Timer()
{
}

void lumi::system::Timer::startTime()
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_currentTime = m_startTime;
	m_lastTime = m_startTime;
}

double lumi::system::Timer::getTime()
{
	m_lastTime = m_currentTime;
	m_currentTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<double>(m_currentTime - m_lastTime).count();
}

void lumi::system::Timer::setTimeStep(int timeStep)
{
	m_timeStep = 1.00 / static_cast<double>(timeStep);
}

double lumi::system::Timer::getTimeStep()
{
	return m_timeStep;
}

double lumi::system::Timer::getElapsedTime()
{
	return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - m_startTime).count();
}
