#pragma once

#include "Core/Interface/IModule.h"

#include <chrono>
#include "Core/CoreType/TimePoint.h"

namespace Module
{
	/**
	 * \brief Manage time elements
	 */
	namespace Time
	{
		/**
		 * \brief Compute delta time and other timers
		 */
		class Clock : public Core::Interface::IModule
		{
		public:
			DECLARE_MODULE(S("Clock"))

			/**
			 * \brief Default constructor
			 */
			Clock() = default;
			/**
			 * \brief Default destructor
			 */
			~Clock() = default;

			/**
			 * \brief Return delta time from previous frame in milliseconds
			 * \return DeltaTime in milliseconds
			 * \note Pause of engine (with debugger for example) will invalid value
			 */
			ENGINEDLL_API float GetDeltaTime() const;
			/**
			 * \brief Return time passed since engine start
			 * \return Running time
			 */
			ENGINEDLL_API Core::CoreType::TimePoint GetTotalTime() const;
			/**
			 * \brief Return the average delta time
			 * \return Average delta time
			 * \note Pause of engine (with debugger for example) will invalid value
			 */
			ENGINEDLL_API float GetDeltaAverage() const;
			/**
			 * \brief Return the average FPS
			 * \return Average FPS
			 */
			ENGINEDLL_API float GetFpsAverage() const;
			/**
			 * \brief Return the current time
			 * \return Current time point
			 */
			ENGINEDLL_API static Core::CoreType::TimePoint Now();

		private:
			/**
			 * \brief Get the new delta time
			 */
			void ComputeDeltaTime();

			/**
			 * \brief System clock handle
			 */
			std::chrono::high_resolution_clock clock;
			/**
			 * \brief Time point set at the start of the programm
			 */
			std::chrono::high_resolution_clock::time_point startProgramPoint = clock.now();

			/**
			 * \brief Time point set at previous frame
			 */
			std::chrono::high_resolution_clock::time_point previousTimePoint = clock.now();
			/**
			 * \brief Time point set at current frame
			 */
			std::chrono::high_resolution_clock::time_point currentTimePoint = clock.now();
			/**
			 * \brief Current delta time
			 */
			std::chrono::high_resolution_clock::duration currentDeltaTime;

			/**
			 * \brief Count of total frame
			 */
			int currentFrame = 0;
			/**
			 * \brief Store average delta time
			 */
			float deltaAverage = 0.f;
		};
	}

}
