#pragma once

#include "Engine.h"
#include "Core/Interface/IScript.h"
#include "ScriptTest2.h"

class ScriptTest : public Core::Interface::IScript
{
public:
	DECLARE_SCRIPT(S("Script Test"), Core::CoreType::SimpleScript)

	ScriptTest() = default;
	~ScriptTest() = default;

	void Initialize() override
	{
		LOG("Script", LOG_DEBUG);
		ADD_SCRIPT(ScriptTest2);
	}
};

