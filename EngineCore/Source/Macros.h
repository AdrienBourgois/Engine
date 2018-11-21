#pragma once

#ifdef ENGINECORE_EXPORTS
/**
 * \brief If ENGINECORE_EXPORTS defined, export the symbol
 */
#define ENGINEDLL_API __declspec(dllexport)
#else
/**
 * \brief If ENGINECORE_EXPORTS is not defined, import the symbol
 */
#define ENGINEDLL_API __declspec(dllimport)
#endif

#include "Core/CoreType/Id.h"
#include "Core/CoreType/String.h"
#include "Modules/Tools/Logs/Logger.h"

/**
 * \brief Return a parameter as a string
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_PARAMETER(section, parameter) Engine::GetInstance()->GetParameters()->Get(section, parameter)
/**
 * \brief Return a parameter as a float
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_FLOAT_PARAMETER(section, parameter) Engine::GetInstance()->GetParameters()->GetFloat(section, parameter)
/**
 * \brief Return a parameter as an int
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_INT_PARAMETER(section, parameter) Engine::GetInstance()->GetParameters()->GetInt(section, parameter)
/**
 * \brief Return a parameter as a boolean
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_BOOL_PARAMETER(section, parameter) Engine::GetInstance()->GetParameters()->GetBool(section, parameter)

/**
 * \brief Create an entry in the logger
 * \param log Text of entry
 * \param level Level of the log (see ELog_level)
 */
#define LOG(log, level) Engine::GetInstance()->GetModule<Module::Tools::Logs::Logger>()->CreateEntry(log, ELog_level::level, S(__FILE__), __LINE__)

/**
 * \brief Add a script to the engine
 * \param T Type of the script
 */
#define ADD_SCRIPT(T) Engine::GetInstance()->AddScript<T>()