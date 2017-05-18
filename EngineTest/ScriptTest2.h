#pragma once

#include "Engine.h"
#include "Core/Interface/IScript.h"

class ScriptTest2 : public Core::Interface::IScript
{
public:
	DECLARE_SCRIPT(S("Script Test 2"), Core::CoreType::SimpleScript)

	ScriptTest2() = default;
	~ScriptTest2() = default;

	void Initialize() override { LOG("Second Script", LOG_INFO); };
};

