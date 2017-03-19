#pragma once

#include "Macros.h"

class ENGINEDLL_API IModule
{
public:
	virtual ~IModule() = default;

	virtual bool Initialize() = 0;
	virtual bool Update() = 0;
	virtual bool Destruct() = 0;
};