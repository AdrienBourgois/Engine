#include <chrono>
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
	time_t currentTime;
	time(&currentTime);
	tm *localTime = nullptr;
	localtime_s(localTime ,&currentTime);
	return Core::CoreType::TimePoint(localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
}

void Module::Time::Clock::ComputeDeltaTime()
{
	currentTimePoint = clock.now();
	currentDeltaTime = currentTimePoint - previousTimePoint;
	previousTimePoint = currentTimePoint;
}

/*#include <iostream>
#include <ctime>

int main()
{
  time_t currentTime;
  struct tm *localTime;

  time( &currentTime );                   // Get the current time
  localTime = localtime( &currentTime );  // Convert the current time to the local time

  int Day    = localTime->tm_mday;
  int Month  = localTime->tm_mon + 1;
  int Year   = localTime->tm_year + 1900;
  int Hour   = localTime->tm_hour;
  int Min    = localTime->tm_min;
  int Sec    = localTime->tm_sec;

  std::cout << "This program was exectued at: " << Hour << ":" << Min << ":" << Sec << std::endl;
  std::cout << "And the current date is: " << Day << "/" << Month << "/" << Year << std::endl;
  return 0;
}
 */