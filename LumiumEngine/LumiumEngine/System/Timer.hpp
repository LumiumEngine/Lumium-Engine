#pragma once
#include <chrono>
#include <ctime>
#include <string>

namespace lumi
{
	namespace system
	{
		class Timer
		{
		public:
			Timer();
			~Timer();
			void startTime();
			double getTime();
			void sleepCycle();
			void setTimeStep(int timeStep);
			double getFrameTime();
			double getElapsedTime();
			std::string getCurrentTimeLabel();
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_bootTime;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
			double m_frameTime;
			double m_timeStep;
		};
	}
}
