#pragma once

#include "Engine.h"

namespace Core
{
	namespace CoreType
	{
		class ENGINEDLL_API Time
		{
		public:
			Time() = default;
			explicit Time(int _day, int _hour, int _minute, int _second, int _millisecond);
			explicit Time(int _hour, int _minute, int _second, int _millisecond);
			explicit Time(int _minute, int _second, int _millisecond);
			explicit Time(int _second, int _millisecond);
			explicit Time(int _millisecond);
			~Time() = default;

			int GetDay() const;
			int GetHour() const;
			int GetMinute() const;
			int GetSecond() const;
			int GetMillisecond() const;

			int GetTotalDay() const;
			int GetTotalHour() const;
			int GetTotalMinute() const;
			int GetTotalSecond() const;
			int GetTotalMillisecond() const;

			Time operator+(Time _other) const;
			void operator+=(Time _other);

			explicit operator bool() const;

		private:
			void Normalize();

			int day = 0;

			int hour = 0;
			int minute = 0;
			int second = 0;

			int millisecond = 0;
		};
	}
}

