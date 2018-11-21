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
 * \tparam T Always array element / character type
 * \tparam N Deduced size of string
 * \param _array Input string
 * \return Size of string
 */
template<typename T, size_t N>
T (& StringSizeHelper(T (&_array)[N]))[N] { return N; }

/**
 * \brief Using StringSizeHelper template, return size of string
 * \param array Input string
 */
#define STRINGSIZE(array) (sizeof(StringSizeHelper(array)))

/**
 * \brief Create string and deduce size
 * \param _text Input string
 */
#define S(_text) Core::CoreType::String(_text, STRINGSIZE(_text))

/**
 * \brief Create Wide string and deduce size
 * \param _text Input wide-string
 */
#define WS(_text) Core::CoreType::WideString(_text, STRINGSIZE(_text))

/**
 * \brief Create string with number (float / int)
 * \param _value Value to stringify
 */
#define SN(_value) Core::CoreType::String(_value)

/**
 * \brief Return C Str with plain text input (Used with MTOS macro)
 * \param text Input Text
 */
#define TEXT_TO_STRING(text) S(#text).CStr()
/**
 * \brief Macro to string : Return C string with value of resolved macro
 * \param macro Macro to resolve
 */
#define MTOS(macro) TEXT_TO_STRING(macro)

#define REAL_SIZE(_variable) _variable == NullSize ? 0u : _variable

static size_t NullSize = -1;

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief Class for characters manipulations
		 * \note Design to always have a Null Terminating Character ('\0' for char) at the end of string
		 * \tparam CharType Type of each character
		 * \tparam EosChar End of string Character
		 */
		template<typename CharType, CharType EosChar>
		class BasicString
		{
		public:
			/**
			 * \brief Constructor (empty string)
			 */
			BasicString() = default;
			/**
			 * \brief Integer constructor
			 * \param _value Value to convert in string
			 */
			explicit BasicString(int _value);
			/**
			 * \brief Float constructor
			 * \param _value Value to convert in string
			 */
			explicit BasicString(float _value);
			/**
			 * \brief Constructor from C string and her size
			 * \param _text Pointer to a C string
			 * \param _size C string size
			 */
			BasicString(const CharType* _text, size_t _size);
			/**
			 * \brief Copy constructor
			 * \param _other_string string to copy
			 */
			BasicString(const BasicString& _other_string);
			/**
			 * \brief Destructor
			 */
			~BasicString();

			/**
			 * \brief Determine if string is empty
			 * \return Is string empty
			 */
			bool IsEmpty() const;
			/**
			 * \brief Determine if string is null
			 * \return Is string null
			 */
			bool IsNull() const;
			/**
			 * \brief Access to position in string
			 * \param _index 0-based index in string
			 * \return Pointer to data at desired position
			 */
			CharType* At(size_t _index) const;
			/**
			 * \brief Access to character in string
			 * \param _index 0-based index in string
			 * \return Character at desired position
			 */
			CharType operator[](size_t _index) const;
			/**
			 * \brief Copy string into another
			 * \param _other_string string to copy
			 */
			BasicString& operator=(const BasicString& _other_string);
			/**
			 * \brief Add string to another / Concatenation
			 * \param _other_string string to add
			 * \return New string with concatenation of the input Strings
			 */
			BasicString operator+(const BasicString& _other_string) const;
			/**
			 * \brief Add character to a string
			 * \param _character Character to add
			 * \return New string with concatenation of the input Strings
			 */
			BasicString operator+(CharType _character) const;
			/**
			 * \brief Add string to this string
			 * \param _other_string string to add
			 */
			void operator+=(const BasicString& _other_string);
			/**
			 * \brief Add a single character to the string
			 * \param _character Character to add
			 */
			void operator+=(CharType _character);
			/**
			 * \brief Compare content of Strings
			 * \param _other_string string to compare
			 * \return Comparison result
			 */
			bool operator==(const BasicString& _other_string) const;
			/**
			 * \brief Compare content of Strings
			 * \param _other_string string to compare
			 * \return Comparison result
			 */
			bool operator!=(const BasicString& _other_string) const;
			/**
			 * \brief Does string has content
			 */
			explicit operator bool() const;

			/**
			 * \brief Add string to this string
			 * \param _other_string string to add
			 */
			void Append(const BasicString& _other_string);
			/**
			 * \brief Add string to this string
			 * \param _character Character to add
			 */
			void Append(CharType _character);

			/**
			 * \brief Determine if this string contain an other string
			 * \param _string_to_find string to find in this string
			 * \return Does this string contain target string
			 */
			bool Contain(const BasicString& _string_to_find) const;
			/**
			 * \brief Return position of a sub-string to find in this string
			 * \param _string_to_find String to find in this string
			 * \return 0-based index of beginning of target string (-1u if does not contain target string)
			 */
			size_t First(const BasicString& _string_to_find) const;

			/**
			 * \brief Return C Style string pointer
			 * \return C Style string pointer
			 */
			const CharType* CStr() const { return data; }

			explicit operator CharType*() const { return data; }

			/**
			 * \brief Return length of the string without null terminated character
			 * \return Length of string
			 */
			size_t Length() const { return size; }

			/**
			 * \brief Return length of the string with null terminated character
			 * \return Length of string with '\0'
			 */
			size_t SafeLength() const { return size + 1; }
			/**
			 * \brief Reserve memory for this string
			 * \param _bytes_count Count of characters to reserve (must be greater than size of string)
			 * \return Is memory reserved
			 */
			bool Reserve(size_t _bytes_count);

			/**
			 * \brief Return a wide version of string
			 * \return String with wide char
			 * \note Can only be used to convert String (char) to WideString (wchar_t)
			 */
			template <typename = std::enable_if_t<std::is_same<CharType, char>::value>>
			BasicString<wchar_t, L'\0'> ToWideString();

			/**
			 * \brief Return a char version of string
			 * \return String with char
			 * \note Can only be used to convert WideString (wchar_t) to String (char)
			 */
			template <typename = std::enable_if_t<std::is_same<CharType, wchar_t>::value>>
			BasicString<char, '\0'> ToCharString();

		private:
			/**
			 * \brief Safely copy an other string to this string
			 * \param _source Other string to copy
			 * \param _size Count of characters to copy
			 * \param _start_index 0-based Index of this string to start copy
			 * \note Assume that space for this string is already allocated
			 */
			void CopyString(const BasicString& _source, size_t _size = NullSize, size_t _start_index = 0) const;
			/**
			 * \brief Free string memory and reset size
			 */
			void DeletePointer();
			/**
			 * \brief Verify the Null Terminating Character ('\0') and size of string
			 * \param _end_of_string_index If know, 0-based index of the Null Terminating Character ('\0')
			 */
			void VerifyString(size_t _end_of_string_index = NullSize);

			/**
			 * \brief Pointer to data
			 */
			CharType* data = nullptr;
			/**
			 * \brief Length of string without null terminated character
			 */
			size_t size = NullSize;
			/**
			 * \brief Size of allocated data
			 */
			size_t capacity = NullSize;
		};

		using String = BasicString<char, '\0'>;
		using WideString = BasicString<wchar_t, L'\0'>;
	}
}

#include "String.inl"