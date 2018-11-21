#pragma once

#include "Macros.h"
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
		/**
		 * \brief Destructor
		 */
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
		/**
		 * \brief Check if line has to be parsed
		 * \return Is current line has to be parsed
		 */
		bool IsLineToParse(const std::string) const;
		/**
		 * \brief Create new section
		 */
		void NewSection();
		/**
		 * \brief Inster section in database
		 */
		void InsertSection();
		/**
		 * \brief Get the name of the section
		 */
		void ExtractSectionName(const std::string);
		/**
		 * \brief Get key of the current element
		 * \return Key of the element
		 */
		std::string ExtractKey(const std::string) const;
		/**
		 * \brief Get value of the current element
		 * \return Value of the element
		 */
		std::string ExtractValue(const std::string) const;

		/**
		 * \brief Path of the file
		 */
		std::string filePath;
		/**
		 * \brief Stream to file
		 */
		std::ifstream file;
		/**
		 * \brief Store keys and values by sections
		 */
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>*> content;

		/**
		 * \brief Handle current section
		 */
		std::unordered_map<std::string, std::string>* current_section = nullptr;
		/**
		 * \brief Store current section name
		 */
		std::string current_section_name = "";
	};
} // namespace Tools