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
 * \brief Return instance of the engine class
 */
#define ENGINE Engine::GetInstance()

/**
 * \brief Return a parameter as a string
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_PARAMETER(section, parameter) ENGINE->GetParameters()->Get(section, parameter)
/**
 * \brief Return a parameter as a float
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_FLOAT_PARAMETER(section, parameter) ENGINE->GetParameters()->GetFloat(section, parameter)
/**
 * \brief Return a parameter as an int
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_INT_PARAMETER(section, parameter) ENGINE->GetParameters()->GetInt(section, parameter)
/**
 * \brief Return a parameter as a boolean
 * \param section Name of the section
 * \param parameter Name of the key/parameter
 */
#define GET_BOOL_PARAMETER(section, parameter) ENGINE->GetParameters()->GetBool(section, parameter)

/**
 * \brief Get a module by his type
 * \param T Type of module
 */
#define MODULE(T) ENGINE->GetModule<T>()

/**
 * \brief Create an entry in the logger
 * \param log Text of entry
 * \param level Level of the log (see ELog_level)
 */
#define LOG(log, level) MODULE(Module::Tools::Logs::Logger)->CreateEntry(log, ELog_level::level)

/**
 * \brief Add a script to the engine
 * \param T Type of the script
 */
#define ADD_SCRIPT(T) ENGINE->AddScript<T>()