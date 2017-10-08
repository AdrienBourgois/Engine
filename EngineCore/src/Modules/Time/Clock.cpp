#include <chrono>

#include "Engine.h"

#include "Core/CoreType/TimePoint.h"
#include "Clock.h"


bool Module::Time::Clock::Initialize()
{
	ComputeDeltaTime();
	return true;
}

bool Module::Time::Clock::Start()
{
	ComputeDeltaTime();
	return true;
}

bool Module::Time::Clock::Update()
{
	ComputeDeltaTime();
	deltaAverage = (deltaAverage * currentFrame + GetDeltaTime()) / ++currentFrame;

	return true;
}

bool Module::Time::Clock::Destruct()
{
	return true;
}

float Module::Time::Clock::GetDeltaTime() const
{
	return static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(currentDeltaTime).count() / 1000.f);
}

Core::CoreType::TimePoint Module::Time::Clock::GetTotalTime() const
{
	return Core::CoreType::TimePoint(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - startProgramPoint).count()));
}

float Module::Time::Clock::GetDeltaAverage() const
{
	return deltaAverage;
}

float Module::Time::Clock::GetFpsAverage() const
{
	float fps_average = 0.f;

	if (GetTotalTime())
	{
		fps_average = static_cast<float>(currentFrame);
		fps_average /= GetTotalTime().GetTotalMillisecond();
		fps_average *= 1000.f;
	}

	return fps_average;
}

Core::CoreType::TimePoint Module::Time::Clock::Now()
{
	time_t current_time;
	time(&current_time);
	tm local_time;
	localtime_s(&local_time, &current_time);
	return Core::CoreType::TimePoint(local_time.tm_hour, local_time.tm_min, local_time.tm_sec, 0);
}

void Module::Time::Clock::ComputeDeltaTime()
{
	currentTimePoint = clock.now();
	currentDeltaTime = currentTimePoint - previousTimePoint;
	previousTimePoint = currentTimePoint;
}