#pragma once

#include "macros.h"
#include <fstream>
#include <unordered_map>

class IniParser
{
public:
	ENGINEDLL_API explicit IniParser(char *);
	ENGINEDLL_API ~IniParser();

	ENGINEDLL_API bool Parse();
	ENGINEDLL_API bool Has(const char*, const char*) const;
	ENGINEDLL_API const char* Get(const char*, const char*) const;
	ENGINEDLL_API int GetInt(const char*, const char*) const;
	ENGINEDLL_API float GetFloat(const char*, const char*) const;
	ENGINEDLL_API void Set(const char*, const char*, const char*);

private:
	bool IsLineToParse(const std::string) const;
	void NewSection();
	void InsertSection();
	void ExtractSectionName(const std::string);
	std::string ExtractKey(const std::string) const;
	std::string ExtractValue(const std::string) const;

	std::string filePath;
	std::ifstream file;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>*> content;

	std::unordered_map<std::string, std::string>* current_section = nullptr;
	std::string current_section_name = "";
};

