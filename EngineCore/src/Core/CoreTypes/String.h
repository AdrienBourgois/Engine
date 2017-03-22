#pragma once

#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif

template <typename T = char, size_t N>
char (& StringSizeHelper(T (&array)[N]))[N]{return N;}
#define stringsize(array) (sizeof(StringSizeHelper(array)))

#define S(_text) CoreType::String(_text, stringsize(_text))

#define MACRO_TO_STRING(macro) S(#macro).CStr()
#define MTOS(macro) MACRO_TO_STRING(macro)

namespace CoreType
{
	class ENGINEDLL_API String
	{
	public:
		String() = default;
		String(const char* _text, unsigned int size);
		String(const String& _other_string);
		~String();

		void operator=(String _new_string);
		String operator+(String _other_string) const;
		void operator+=(String _other_string);
		bool operator==(String _other_string) const;
		explicit operator bool() const;

		void Append(String _string);

		const char* const CStr() const { return pointer; }
		unsigned int Length() const { return size; }
		unsigned int SafeLength() const { return size + 1; }

	private:
		void DeletePointer();

		char* pointer = nullptr;
		unsigned int size;
	};
}