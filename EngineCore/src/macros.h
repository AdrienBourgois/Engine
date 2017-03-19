#pragma once

#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif

/**
 * \brief Return instance of the engine class
 */
#define ENGINE Engine::GetInstance()

#define GET_PARAMETER(section, parameter) ENGINE->GetParameters()->Get(section, parameter);
#define GET_FLOAT_PARAMETER(section, parameter) ENGINE->GetParameters()->GetFloat(section, parameter);
#define GET_INT_PARAMETER(section, parameter) ENGINE->GetParameters()->GetInt(section, parameter);