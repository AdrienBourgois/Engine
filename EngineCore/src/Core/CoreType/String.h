#pragma once

///@cond DUPLICATE_MACRO
#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif
///@endcond

/**
 * \brief Helper template to define size of a string at compilation
 * \tparam T Always char
 * \tparam N Deduced size of string
 * \param array Input string
 * \return Size of string
 */
template <typename T = char, size_t N>
char (& StringSizeHelper(T (&array)[N]))[N]{return N;}
/**
 * \brief Using StringSizeHelper template, return size of string
 * \param array Input string
 */
#define stringsize(array) (sizeof(StringSizeHelper(array)))

/**
 * \brief Create String and deduce size
 * \param _text Input string
 */
#define S(_text) Core::CoreType::String(_text, stringsize(_text))
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
		 */
		class ENGINEDLL_API String
		{
		public:
			/**
			 * \brief Default constructor
			 */
			String() = default;
			/**
			 * \brief Interger constructor
			 * \param _value Value to convert in string
			 */
			explicit String(int _value);
			/**
			 * \brief Float constructor
			 * \param _value Value to convert in string
			 */
			explicit String(float _value);
			/**
			 * \brief Constructor from C String and her size
			 * \param _text Pointer to a C String
			 * \param size C String size
			 */
			String(const char* _text, unsigned int size);
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
			 * \brief Copy string into another
			 * \param _new_string String to copy
			 */
			void operator=(String _new_string);
			/**
			 * \brief Add string to another / Concatenation
			 * \param _other_string String to copy
			 * \return New String with concatenation of the input Strings
			 */
			String operator+(String _other_string) const;
			/**
			 * \brief Add String to this String
			 * \param _other_string String to add
			 */
			void operator+=(String _other_string);
			/**
			 * \brief Add a single character to the string
			 * \param _character Character to add
			 */
			void operator+=(char _character);
			/**
			 * \brief Compare content of Strings
			 * \param _other_string String to compare
			 * \return Comparison result
			 */
			bool operator==(String _other_string) const;
			/**
			 * \brief Compare content of Strings
			 * \param _other_string String to compare
			 * \return Comparison result
			 */
			bool operator!=(String _other_string) const;
			/**
			 * \brief Does String has content
			 */
			explicit operator bool() const;

			/**
			 * \brief Add String to this String
			 * \param _string String to add
			 */
			void Append(String _string);

			/**
			 * \brief Return C Style string pointer
			 * \return C Style string pointer
			 */
			const char* const CStr() const { return pointer; }
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
			 * \brief Pointer to data
			 */
			char* pointer = nullptr;
			/**
			 * \brief Pointer to wide data (only populate if ToWideString is called)
			 */
			wchar_t* widePointer = nullptr;
			/**
			 * \brief Length of String without null terminated character
			 */
			unsigned int size;
		};
	}
}