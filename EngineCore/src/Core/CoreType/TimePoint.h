#pragma once

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief Store time point or duration
		 */
		class TimePoint
		{
		public:
			/**
			 * \brief Default constructor
			 */
			TimePoint() = default;
			/**
			 * \brief Constructor
			 * \param _day Count of days
			 * \param _hour Count of hours
			 * \param _minute Count of minutes
			 * \param _second Count of seconds
			 * \param _millisecond Count of milliseconds
			 */
			explicit TimePoint(int _day, int _hour, int _minute, int _second, int _millisecond);
			/**
			 * \brief Constructor
			 * \param _hour Count of hours
			 * \param _minute Count of minutes
			 * \param _second Count of seconds
			 * \param _millisecond Count of milliseconds
			 */
			explicit TimePoint(int _hour, int _minute, int _second, int _millisecond);
			/**
			 * \brief Constructor
			 * \param _minute Count of minutes
			 * \param _second Count of seconds
			 * \param _millisecond Count of milliseconds
			 */
			explicit TimePoint(int _minute, int _second, int _millisecond);
			/**
			 * \brief Constructor
			 * \param _second Count of seconds
			 * \param _millisecond Count of milliseconds
			 */
			explicit TimePoint(int _second, int _millisecond);
			/**
			 * \brief Constructor
			 * \param _millisecond Count of milliseconds
			 */
			explicit TimePoint(int _millisecond);
			/**
			 * \brief Default destructor
			 */
			~TimePoint() = default;

			/**
			 * \brief Return day count
			 * \return Day count
			 */
			int GetDay() const;
			/**
			 * \brief Return hour count
			 * \return Hour count
			 */
			int GetHour() const;
			/**
			 * \brief Return minute count
			 * \return Minute count
			 */
			int GetMinute() const;
			/**
			 * \brief Return second count
			 * \return Second count
			 */
			int GetSecond() const;
			/**
			 * \brief Return millisecond count
			 * \return Millisecond count
			 */
			int GetMillisecond() const;

			/**
			 * \brief Return Cumulated count of day
			 * \return Cumulated count of day
			 */
			int GetTotalDay() const;
			/**
			 * \brief Return Cumulated count of hour
			 * \return Cumulated count of hour
			 */
			int GetTotalHour() const;
			/**
			 * \brief Return Cumulated count of minute
			 * \return Cumulated count of minute
			 */
			int GetTotalMinute() const;
			/**
			 * \brief Return Cumulated count of second
			 * \return Cumulated count of second
			 */
			int GetTotalSecond() const;
			/**
			 * \brief Return Cumulated count of millisecond
			 * \return Cumulated count of millisecond
			 */
			int GetTotalMillisecond() const;

			/**
			 * \brief Add period to another
			 * \param _other Period to add
			 * \return Sum of periods
			 */
			TimePoint operator+(TimePoint _other) const;
			/**
			 * \brief Add period to this
			 * \param _other Period to add
			 */
			void operator+=(TimePoint _other);

			/**
			 * \brief Is period different from 0
			 */
			explicit operator bool() const;

		private:
			/**
			 * \brief Compute carries
			 */
			void Normalize();

			/**
			 * \brief Day component
			 */
			int day = 0;

			/**
			 * \brief Hour component
			 */
			int hour = 0;
			/**
			 * \brief Minute component
			 */
			int minute = 0;
			/**
			 * \brief Second component
			 */
			int second = 0;

			/**
			 * \brief Millisecond component
			 */
			int millisecond = 0;
		};
	}
}

