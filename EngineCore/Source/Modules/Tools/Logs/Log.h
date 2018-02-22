#pragma once

#include "Core/CoreType/String.h"
#include "Core/CoreType/TimePoint.h"

/**
* \brief Define the level of log
*/
enum class ELog_level
{
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
	LOG_VERBOSE
};

namespace Module
{
	namespace Tools
	{
		namespace Logs
		{
			/**
			 * \brief Log with message, level, ...
			 */
			class Log
			{
			public:
				/**
				 * \brief Log constructor
				 * \param _message Message of log
				 * \param _level Level of log
				 */
				Log(const Core::CoreType::String& _message, ELog_level _level);
				/**
				 * \brief Log constructor
				 * \param _message Message of log
				 * \param _level Level of log
				 * \param _file File caller
				 * \param _line Line number of file caller
				 */
				Log(const Core::CoreType::String& _message, ELog_level _level, const Core::CoreType::String& _file, int _line);
				/**
				 * \brief Default destructor
				 */
				~Log() = default;

				/**
				 * \brief Return the message of the log
				 * \return Message of log
				 */
				Core::CoreType::String GetStringMessage() const { return message; }

				/**
				 * \brief Return the message of the log as C String
				 * \return Message of log
				 */
				const char* GetCMessage() const { return message.CStr(); }
				/**
				 * \brief Create a fancy message ready for console or file with time and additionnals informations
				 * \return Log structured for console, file, ...
				 */
				Core::CoreType::String GetStructuredLog();

				/**
				 * \brief Return the level of the log
				 * \return Level of log
				 */
				ELog_level GetLevel() const { return level; }
				/**
				 * \brief Return time entry has been created
				 * \return Time of entry
				 */
				Core::CoreType::TimePoint GetTime() const { return time; }

			private:
				/**
				 * \brief Message of log
				 */
				Core::CoreType::String message;
				/**
				 * \brief Level of log
				 */
				ELog_level level = ELog_level::LOG_VERBOSE;
				/**
				 * \brief Source file that create log
				 */
				Core::CoreType::String file;
				/**
				 * \brief Line number of file that create log
				 */
				int line = 0;
				/**
				 * \brief Time of log
				 */
				Core::CoreType::TimePoint time;

				/**
				 * \brief Fancy version of log (only populated if call to GetStructuredLog)
				 */
				Core::CoreType::String structuredLog;
			};
		}
	}
}