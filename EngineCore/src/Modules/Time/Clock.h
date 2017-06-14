#pragma once

#include "Core/Interface/IModule.h"

#include <chrono>
#include "Core/CoreType/Time.h"

namespace Module
{
	class Clock : public Core::Interface::IModule
	{
	public:
		DECLARE_MODULE(S("Clock"))

		Clock() = default;
		~Clock() = default;

		ENGINEDLL_API float GetDeltaTime() const;
		ENGINEDLL_API Core::CoreType::Time GetTotalTime() const;
		ENGINEDLL_API float GetDeltaAverage() const;
		ENGINEDLL_API float GetFpsAverage() const;

	private:
		void ComputeDeltaTime();

		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point startProgramPoint = clock.now();

		std::chrono::high_resolution_clock::time_point previousTimePoint = clock.now();
		std::chrono::high_resolution_clock::time_point currentTimePoint = clock.now();
		std::chrono::high_resolution_clock::duration currentDeltaTime;

		int currentFrame = 0;
		float deltaAverage = 0.f;
	};

}
