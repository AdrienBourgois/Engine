#pragma once

#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif

#include "Core/CoreType/Id.h"
#include "Core/CoreType/String.h"
#include "Modules/Tools/Logger/Logger.h"

/**
 * \brief Return instance of the engine class
 */
#define ENGINE Engine::GetInstance()

#define GET_PARAMETER(section, parameter) ENGINE->GetParameters()->Get(section, parameter)
#define GET_FLOAT_PARAMETER(section, parameter) ENGINE->GetParameters()->GetFloat(section, parameter)
#define GET_INT_PARAMETER(section, parameter) ENGINE->GetParameters()->GetInt(section, parameter)
#define GET_BOOL_PARAMETER(section, parameter) ENGINE->GetParameters()->GetBool(section, parameter)

#define MODULE(T) ENGINE->GetModule<T>()

#define LOG(log, level) MODULE(Module::Tools::Logger)->CreateEntry(S(log), ELog_level::level)

#define ADD_SCRIPT(T) ENGINE->AddScript<T>()