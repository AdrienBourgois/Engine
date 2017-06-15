#pragma once

#include "Core/CoreType/String.h"

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
				Log(Core::CoreType::String _message, ELog_level _level);
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
				 * \brief Return the level of the log
				 * \return Level of log
				 */
				ELog_level GetLevel() const { return level; }

			private:
				/**
				 * \brief Message of log
				 */
				Core::CoreType::String message;
				/**
				 * \brief Level of log
				 */
				ELog_level level = ELog_level::LOG_VERBOSE;
			};
		}
	}
}