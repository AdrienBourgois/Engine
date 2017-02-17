#include "IniParser.h"
#include <string>

IniParser::IniParser(char * _filePath)
{
	filePath = _filePath;
}

IniParser::~IniParser()
{
	for (auto element : content)
		delete element.second;
}

bool IniParser::Parse()
{
	file.open(filePath);
	if (!file.is_open())
		return false;

	while (file.good() && !file.eof())
	{
		std::string current_line;
		getline(file, current_line);

		if (IsLineToParse(current_line))
		{
			if (current_line.front() == '[' && current_line.back() == ']')
			{
				NewSection();
				ExtractSectionName(current_line);
			}
			else
				current_section->insert(make_pair(ExtractKey(current_line), ExtractValue(current_line)));
		}
	}
	return true;
}

bool IniParser::Has(const char* _section_to_find, const char* _key_to_find = "") const
{
	for (auto section : content)
	{
		if(section.first == _section_to_find)
		{
			if (_key_to_find != "")
			{
				for (auto key : *section.second)
					if (key.first == _key_to_find)
						return true;
			}
			else
				return true;
		}
	}
	return false;
}

const char* IniParser::Get(const char* _section, const char* _key) const
{
	if (Has(_section, _key))
		return content.at(_section)->at(_key).c_str();

	return nullptr;
}

void IniParser::Set(const char* _section, const char* _key, const char* _value)
{
	if (Has(_section, _key))
		content.at(_section)->at(_key) = _value;
}

bool IniParser::IsLineToParse(const std::string _line) const
{
	for (char element : _line)
	{
		if (element != ' ')
		{
			if (element == ';' || element == '#' || element == '\n')
				return false;
		}
		else
			return true;
	}
	return false;
}

void IniParser::NewSection()
{
	if (current_section)
		content.insert(make_pair(current_section_name, current_section));

	current_section = new std::unordered_map<std::string, std::string>();
	current_section_name = "";
}

void IniParser::ExtractSectionName(const std::string _line)
{
	std::string name = "";
	for (char element : _line)
	{
		if (element != ' ' && element != '[')
			name += element;
		if (element == ']')
			break;
	}
	current_section_name = name;
}

std::string IniParser::ExtractKey(const std::string _line) const
{
	std::string key = "";
	for (char element : _line)
	{
		if (element == ' ' || element == '\n')
		{
			if (key == "")
				break;
		}
		else
			key += element;
	}
	return key;
}

std::string IniParser::ExtractValue(const std::string _line) const
{
	std::string value = "";
	size_t pos = _line.find('=');

	for (char element : _line.substr(pos + 1))
	{
		if (element == ' ' || element == '\n')
		{
			if (value == "")
				break;
		}
		else
			value += element;
	}
	return value;
}
