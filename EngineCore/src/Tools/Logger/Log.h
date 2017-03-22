﻿#pragma once

#include "Core/CoreTypes/String.h"

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
		Log(CoreType::String _message, ELog_level _level);
		~Log() = default;

		/**
		 * \brief Return the message of the log
		 * \return Message of log
		 */
		CoreType::String GetMessage() const { return message; }

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
		CoreType::String message;
		ELog_level level = VERBOSE;
	};
}
