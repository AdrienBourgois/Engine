#include "Clock.h"
#include <chrono>
#include "Core/CoreType/Time.h"


bool Module::Clock::Initialize()
{
	ComputeDeltaTime();
	return true;
}

bool Module::Clock::Start()
{
	ComputeDeltaTime();
	return true;
}

bool Module::Clock::Update()
{
	ComputeDeltaTime();
	deltaAverage = (deltaAverage * currentFrame + GetDeltaTime()) / ++currentFrame;

	return true;
}

bool Module::Clock::Destruct()
{
	return true;
}

float Module::Clock::GetDeltaTime() const
{
	return static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(currentDeltaTime).count() / 1000.f);
}

Core::CoreType::Time Module::Clock::GetTotalTime() const
{
	return Core::CoreType::Time(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - startProgramPoint).count()));
}

float Module::Clock::GetDeltaAverage() const
{
	return deltaAverage;
}

float Module::Clock::GetFpsAverage() const
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

void Module::Clock::ComputeDeltaTime()
{
	currentTimePoint = clock.now();
	currentDeltaTime = currentTimePoint - previousTimePoint;
	previousTimePoint = currentTimePoint;
}
