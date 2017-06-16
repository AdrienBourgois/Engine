#include "TimePoint.h"

Core::CoreType::TimePoint::TimePoint(int _day, int _hour, int _minute, int _second, int _millisecond): day(_day), hour(_hour), minute(_minute), second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::TimePoint::TimePoint(int _hour, int _minute, int _second, int _millisecond): hour(_hour), minute(_minute), second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::TimePoint::TimePoint(int _minute, int _second, int _millisecond): minute(_minute), second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::TimePoint::TimePoint(int _second, int _millisecond): second(_second), millisecond(_millisecond)
{
	Normalize();
}

Core::CoreType::TimePoint::TimePoint(int _millisecond): millisecond(_millisecond)
{
	Normalize();
}

int Core::CoreType::TimePoint::GetDay() const
{
	return day;
}

int Core::CoreType::TimePoint::GetHour() const
{
	return hour;
}

int Core::CoreType::TimePoint::GetMinute() const
{
	return minute;
}

int Core::CoreType::TimePoint::GetSecond() const
{
	return second;
}

int Core::CoreType::TimePoint::GetMillisecond() const
{
	return millisecond;
}

int Core::CoreType::TimePoint::GetTotalDay() const
{
	return day;
}

int Core::CoreType::TimePoint::GetTotalHour() const
{
	return GetTotalDay() * 24 + hour;
}

int Core::CoreType::TimePoint::GetTotalMinute() const
{
	return GetTotalHour() * 60 + minute;
}

int Core::CoreType::TimePoint::GetTotalSecond() const
{
	return GetTotalMinute() * 60 + second;
}

int Core::CoreType::TimePoint::GetTotalMillisecond() const
{
	return GetTotalSecond() * 1000 + millisecond;
}

Core::CoreType::TimePoint Core::CoreType::TimePoint::operator+(TimePoint _other) const
{
	TimePoint time = *this;
	time += _other;
	return time;
}

void Core::CoreType::TimePoint::operator+=(TimePoint _other)
{
	millisecond += _other.millisecond;
	second += _other.second;
	minute += _other.minute;
	hour += _other.hour;
	day += _other.day;
	Normalize();
}

Core::CoreType::TimePoint::operator bool() const
{
	if (millisecond || second || minute || hour || day)
		return true;
	return false;
}

Core::CoreType::String Core::CoreType::TimePoint::ToString()
{
	Normalize();

	return SN(hour) + S(":") + SN(minute) + S(":") + SN(second);
}

void Core::CoreType::TimePoint::Normalize()
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
