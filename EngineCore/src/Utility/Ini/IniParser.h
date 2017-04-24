#pragma once

#include "macros.h"
#include <fstream>
#include <unordered_map>

namespace Utility
{
	/**
	 * \brief Class to parse .ini files
	 */
	class IniParser
	{
	public:
		/**
		 * \brief
		 * \param _filePath Path of the file to parse
		 */
		ENGINEDLL_API explicit IniParser(char * _filePath);
		ENGINEDLL_API ~IniParser();

		/**
		 * \brief Parse file
		 * \return Is file successfully parsed
		 */
		ENGINEDLL_API bool Parse();

		/**
		 * \brief Return existence of key in section of file
		 * \param _section Section name
		 * \param _key Key name
		 * \return Is key in file
		 */
		ENGINEDLL_API bool Has(const char* _section, const char* _key) const;

		/**
		 * \brief Return value of key in section of file
		 * \param _section Section name
		 * \param _key Key name
		 * \return String value of key
		 */
		ENGINEDLL_API const char* Get(const char* _section, const char* _key) const;

		/**
		 * \brief Return value of key in section of file as int
		 * \param _section Section name
		 * \param _key Key name
		 * \return Int value of key
		 */
		ENGINEDLL_API int GetInt(const char* _section, const char* _key) const;

		/**
		 * \brief Return value of key in section of file as float
		 * \param _section Section name
		 * \param _key Key name
		 * \return Float value of key
		 */
		ENGINEDLL_API float GetFloat(const char* _section, const char* _key) const;

		/**
		 * \brief Return value of key in section of file as float
		 * \param _section Section name
		 * \param _key Key name
		 * \return Bool value of key
		 */
		ENGINEDLL_API bool GetBool(const char* _section, const char* _key) const;

		/**
		 * \brief Change value of key (any change if file)
		 * \param _section Section name
		 * \param _key Key name
		 * \param _new_value New value of key
		 */
		ENGINEDLL_API void Set(const char* _section, const char* _key, const char* _new_value);

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
} // namespace Tools