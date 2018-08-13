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
			void setTimeStep(int timeStep);
			double getTimeStep();
			double getElapsedTime();
		private:

			std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_currentTime;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
			double m_timeStep;
		};
	}
}
