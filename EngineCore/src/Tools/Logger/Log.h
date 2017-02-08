#pragma once

#include <string>

namespace Tools
{
	/**
	 * \brief Define the level of log
	 */
	enum ELog_level : char
	{
		ERROR,
		WARNING,
		INFO,
		DEBUG,
		VERBOSE,
	};

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
		Log(char* _message, ELog_level _level);
		~Log() = default;

		/**
		 * \brief Return the message of the log
		 * \return Message of log
		 */
		std::string GetMessage() const { return message; }

		/**
		 * \brief Return the message of the log as C String
		 * \return Message of log
		 */
		const char* GetCMessage() const { return message.c_str(); }

		/**
		 * \brief Return the level of the log
		 * \return Level of log
		 */
		ELog_level GetLevel() const { return level; }

	private:
		std::string message;
		ELog_level level;
	};
}
