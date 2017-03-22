#pragma once

#include "Macros.h"

#define DECLARE_MODULE(name)\
	bool Initialize() override;\
	bool Start() override;\
	bool Update() override;\
	bool Destruct() override;\
	void SetDefaultModuleName() override { moduleName = name; }

class ENGINEDLL_API IModule
{
public:
	virtual ~IModule() = default;

	virtual bool Initialize() = 0;
	virtual bool Start() = 0;
	virtual bool Update() = 0;
	virtual bool Destruct() = 0;
	virtual void SetDefaultModuleName() = 0;

	void SetModuleName(CoreType::String _new_name = S("")) { moduleName = _new_name; };
	const char* GetModuleName() const { return moduleName.CStr(); }

protected:
	CoreType::String moduleName = S("Unamed Module");
};