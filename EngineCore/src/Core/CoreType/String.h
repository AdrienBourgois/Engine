#pragma once

///@cond DUPLICATE_MACRO
#ifdef ENGINECORE_EXPORTS
/**
 * \brief If ENGINECORE_EXPORTS defined, export the symbol
 */
#define ENGINEDLL_API __declspec(dllexport)
#else
/**
 * \brief If ENGINECORE_EXPORTS is not defined, import the symbol
 */
#define ENGINEDLL_API __declspec(dllimport)
#endif
///@endcond

/**
 * \brief Helper template to define size of a string at compilation
 * \tparam T Always char
 * \tparam N Deduced size of string
 * \param _array Input string
 * \return Size of string
 */
template <typename T = char, size_t N>
char (& StringSizeHelper(T (&_array)[N]))[N]{return N;}
/**
 * \brief Using StringSizeHelper template, return size of string
 * \param array Input string
 */
#define STRINGSIZE(array) (sizeof(StringSizeHelper(array)))

/**
 * \brief Create String and deduce size
 * \param _text Input string
 */
#define S(_text) Core::CoreType::String(_text, STRINGSIZE(_text))
/**
 * \brief Create String with number (float / int)
 * \param _value Value to stringify
 */
#define SN(_value) Core::CoreType::String(_value)

/**
 * \brief Return C Str with plain text input (Used with MTOS macro)
 * \param text Input Text
 */
#define TEXT_TO_STRING(text) S(#text).CStr()
/**
 * \brief Macro to string : Return C String with value of resolved macro
 * \param macro Macro to resolve
 */
#define MTOS(macro) TEXT_TO_STRING(macro)

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief Class to simples characters manipulations
		 * \note Design to always have a Null Terminating Character ('\0') at the end of String
		 */
		class ENGINEDLL_API String
		{
		public:
			/**
			 * \brief Constructor (empty String)
			 */
			String();
			/**
			 * \brief Interger constructor
			 * \param _value Value to convert in string
			 */
			explicit String(const int _value);
			/**
			 * \brief Float constructor
			 * \param _value Value to convert in string
			 */
			explicit String(const float _value);
			/**
			 * \brief Constructor from C String and her size
			 * \param _text Pointer to a C String
			 * \param _size C String size
			 */
			String(const char* _text, const unsigned int _size);
			/**
			 * \brief Copy constructor
			 * \param _other_string String to copy
			 */
			String(const String& _other_string);
			/**
			 * \brief Destructor
			 */
			~String();

			/**
			 * \brief Determine if String is empty
			 * \return Is String empty
			 */
			bool IsEmpty() const;
			/**
			 * \brief Determine if String is null
			 * \return Is String null
			 */
			bool IsNull() const;
			/**
			 * \brief Access to position in String
			 * \param _index 0-based index in String
			 * \return Pointer to data at desired position
			 */
			char* At(const unsigned _index) const;
			/**
			 * \brief Access to character in String
			 * \param _index 0-based index in String
			 * \return Character at desired position
			 */
			char operator[](const unsigned _index) const;
			/**
			 * \brief Copy string into another
			 * \param _new_string String to copy
			 */
			void operator=(const String _new_string);
			/**
			 * \brief Add string to another / Concatenation
			 * \param _other_string String to copy
			 * \return New String with concatenation of the input Strings
			 */
			String operator+(const String _other_string) const;
			/**
			 * \brief Add String to this String
			 * \param _other_string String to add
			 */
			void operator+=(const String _other_string);
			/**
			 * \brief Add a single character to the string
			 * \param _character Character to add
			 */
			void operator+=(const char _character);
			/**
			 * \brief Compare content of Strings
			 * \param _other_string String to compare
			 * \return Comparison result
			 */
			bool operator==(const String _other_string) const;
			/**
			 * \brief Compare content of Strings
			 * \param _other_string String to compare
			 * \return Comparison result
			 */
			bool operator!=(const String _other_string) const;
			/**
			 * \brief Does String has content
			 */
			explicit operator bool() const;

			/**
			 * \brief Add String to this String
			 * \param _string String to add
			 */
			void Append(const String _string);

			/**
			 * \brief Determine if this String contain an other String
			 * \param _string_to_find String to find in this String
			 * \return Does this String contain target String
			 */
			bool Contain(const String _string_to_find) const;
			/**
			 * \brief Return position of a sub-string to find in this String
			 * \param _string_to_find String to find in this String
			 * \return 0-based index of begining of target String (-1u if does not contain target String)
			 */
			unsigned First(const String _string_to_find) const;

			/**
			 * \brief Return C Style string pointer
			 * \return C Style string pointer
			 */
			const char* CStr() const { return data; }
			/**
			 * \brief Return length of the String without null terminated character
			 * \return Length of String
			 */
			unsigned int Length() const { return size; }
			/**
			 * \brief Return length of the String with null terminated character
			 * \return Length of String with '\0'
			 */
			unsigned int SafeLength() const { return size + 1; }
			/**
			 * \brief Return a wide version of string
			 * \return String with wide char
			 */
			wchar_t const* ToWideString();

		private:
			/**
			 * \brief Free string memory and reset size
			 */
			void DeletePointer();
			/**
			 * \brief Verify the Null Terminating Character ('\0') and size of String
			 */
			void VerifyString();

			/**
			 * \brief Pointer to data
			 */
			char* data = nullptr;
			/**
			 * \brief Pointer to wide data (only populated if ToWideString is called)
			 */
			wchar_t* widePointer = nullptr;
			/**
			 * \brief Length of String without null terminated character
			 */
			unsigned int size = -1;
			/**
			 * \brief Size of allocated datas
			 */
			unsigned int capacity = -1;
		};
	}
}