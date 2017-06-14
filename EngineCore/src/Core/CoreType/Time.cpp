#include "Time.h"

Core::CoreType::Time::Time(int _day, int _hour, int _minute, int _second, int _millisecond): day(_day), hour(_hour), minute(_minute), second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::Time::Time(int _hour, int _minute, int _second, int _millisecond): hour(_hour), minute(_minute), second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::Time::Time(int _minute, int _second, int _millisecond): minute(_minute), second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::Time::Time(int _second, int _millisecond): second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::Time::Time(int _millisecond): millisecond(_millisecond)
{
	Normalize();
}

int Core::CoreType::Time::GetDay() const
{
	return day;
}

int Core::CoreType::Time::GetHour() const
{
	return hour;
}

int Core::CoreType::Time::GetMinute() const
{
	return minute;
}

int Core::CoreType::Time::GetSecond() const
{
	return second;
}

int Core::CoreType::Time::GetMillisecond() const
{
	return millisecond;
}

int Core::CoreType::Time::GetTotalDay() const
{
	return day;
}

int Core::CoreType::Time::GetTotalHour() const
{
	return GetTotalDay() * 24 + hour;
}

int Core::CoreType::Time::GetTotalMinute() const
{
	return GetTotalHour() * 60 + minute;
}

int Core::CoreType::Time::GetTotalSecond() const
{
	return GetTotalMinute() * 60 + second;
}

int Core::CoreType::Time::GetTotalMillisecond() const
{
	return GetTotalSecond() * 1000 + millisecond;
}

Core::CoreType::Time Core::CoreType::Time::operator+(Time _other) const
{
	Time time = *this;
	time += _other;
	return time;
}

void Core::CoreType::Time::operator+=(Time _other)
{
	millisecond += _other.millisecond;
	second += _other.second;
	minute += _other.minute;
	hour += _other.hour;
	day += _other.day;
	Normalize();
}

Core::CoreType::Time::operator bool() const
{
	if (millisecond || second || minute || hour || day)
		return true;
	return false;
}

void Core::CoreType::Time::Normalize()
{
	int carry = millisecond / 1000;
	millisecond %= 1000;

	second += carry;
	carry = second / 60;
	second %= 60;

	minute += carry;
	carry = minute / 60;
	minute %= 60;

	hour += carry;
	carry = hour / 60;
	hour %= 60;

	day += carry;
}
