#pragma once

#include <cstring>
#include <string>

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar>::BasicString(const int _value)
{
	std::string string = std::to_string(_value);
	capacity = string.size() + 1;
	data = new CharType[capacity];
	memcpy(data, string.c_str(), string.size());
	VerifyString();
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar>::BasicString(const float _value)
{
	std::string string = std::to_string(_value);
	capacity = string.size() + 1;
	data = new CharType[capacity];
	memcpy(data, string.c_str(), string.size());
	VerifyString();
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar>::BasicString(const CharType* _text, const size_t _size)
{
	if (_size != 0)
	{
		capacity = _size;
		data = new CharType[capacity];
		memcpy(data, _text, _size);
		VerifyString();
	}
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar>::BasicString(const BasicString& _other_string)
{
	capacity = _other_string.size + 1;
	size = _other_string.size;
	data = new CharType[capacity];
	memcpy(data, _other_string.data, size);

	VerifyString();
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar>::~BasicString()
{
	DeletePointer();
}

template<typename CharType, CharType EosChar>
bool Core::CoreType::BasicString<CharType, EosChar>::IsEmpty() const
{
	return data == nullptr || size == 0;
}

template<typename CharType, CharType EosChar>
bool Core::CoreType::BasicString<CharType, EosChar>::IsNull() const
{
	return data == nullptr;
}

template<typename CharType, CharType EosChar>
CharType* Core::CoreType::BasicString<CharType, EosChar>::At(const size_t _index) const
{
	if (_index > size)
		return nullptr;
	return data + _index;
}

template<typename CharType, CharType EosChar>
CharType Core::CoreType::BasicString<CharType, EosChar>::operator[](const size_t _index) const
{
	if (_index > size)
		return 0;
	return data[_index];
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar>& Core::CoreType::BasicString<CharType, EosChar>::operator=(const BasicString& _other_string)
{
	if (_other_string.size + 1 > capacity)
	{
		DeletePointer();
		capacity = _other_string.size + 1;
		data = new CharType[capacity];
	}

	memcpy(data, _other_string.data, _other_string.size);

	VerifyString(_other_string.size);

	return *this;
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar> Core::CoreType::BasicString<CharType, EosChar>::operator+(const BasicString& _other_string) const
{
	if (_other_string.IsNull()) return *this;

	BasicString<CharType, EosChar> string;

	string.capacity = size + _other_string.size + 1;
	string.data = new CharType[string.capacity];
	memcpy(string.data, data, size);
	memcpy(string.data + size, _other_string.data, _other_string.size);

	string.VerifyString();

	return string;
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar> Core::CoreType::BasicString<CharType, EosChar>::operator+(const CharType _character) const
{
	BasicString<CharType, EosChar> string;

	string.capacity = size + 2;
	string.data = new CharType[string.capacity];
	memcpy(string.data, data, size);
	string.data[size] = _character;

	string.VerifyString();

	return string;
}

template<typename CharType, CharType EosChar>
void Core::CoreType::BasicString<CharType, EosChar>::operator+=(const BasicString& _other_string)
{
	Append(_other_string);
}

template<typename CharType, CharType EosChar>
void Core::CoreType::BasicString<CharType, EosChar>::operator+=(const CharType _character)
{
	Append(_character);
}

template<typename CharType, CharType EosChar>
bool Core::CoreType::BasicString<CharType, EosChar>::operator==(const BasicString& _other_string) const
{
	if (size != _other_string.size)
		return false;

	for (size_t i = 0; i < size && i < _other_string.size; ++i)
	{
		if (data[i] != _other_string.data[i])
			return false;
	}
	return true;
}

template<typename CharType, CharType EosChar>
bool Core::CoreType::BasicString<CharType, EosChar>::operator!=(const BasicString& _other_string) const
{
	return !operator==(_other_string);
}

template<typename CharType, CharType EosChar>
Core::CoreType::BasicString<CharType, EosChar>::operator bool() const
{
	return size != 0;
}

template<typename CharType, CharType EosChar>
void Core::CoreType::BasicString<CharType, EosChar>::Append(const BasicString& _other_string)
{
	const size_t new_size = size + _other_string.size;
	size_t first_string_size = size;
	if (first_string_size == NullSize)
		first_string_size = 0;

	if (capacity == NullSize || capacity < new_size + 1)
		Reserve(new_size + 1);

	memcpy(data + first_string_size, _other_string.data, _other_string.size);

	VerifyString(new_size);
}

template<typename CharType, CharType EosChar>
void Core::CoreType::BasicString<CharType, EosChar>::Append(const CharType _character)
{
	const size_t new_size = size + 1;

	if (capacity == NullSize || capacity < new_size + 1)
		Reserve(new_size + 1);

	data[size] = _character;

	VerifyString(new_size);
}

template<typename CharType, CharType EosChar>
bool Core::CoreType::BasicString<CharType, EosChar>::Contain(const BasicString& _string_to_find) const
{
	return First(_string_to_find) != NullSize;
}

template<typename CharType, CharType EosChar>
size_t Core::CoreType::BasicString<CharType, EosChar>::First(const BasicString& _string_to_find) const
{
	if (_string_to_find.size > size)
		return false;

	for (size_t i = 0; i < size; ++i)
	{
		if (data[i] == _string_to_find[0])
		{
			bool temp_found = true;
			for (size_t j = 0; j < size && j < _string_to_find.size; ++j)
			{
				if (data[i + j] != _string_to_find[j])
				{
					temp_found = false;
					break;
				}
			}
			if (temp_found)
				return i;
		}
	}
	return NullSize;
}

template<typename CharType, CharType EosChar>
bool Core::CoreType::BasicString<CharType, EosChar>::Reserve(const size_t _bytes_count)
{
	if (_bytes_count <= REAL_SIZE(capacity) || _bytes_count <= REAL_SIZE(size))
		return false;

	capacity = _bytes_count;

	CharType* new_pointer = new CharType[capacity];
	if (REAL_SIZE(size))
		memcpy(new_pointer, data, size);
	delete data;
	data = new_pointer;
	data[REAL_SIZE(size)] = EosChar;
	VerifyString();

	return true;
}

template<typename CharType, CharType EosChar>
void Core::CoreType::BasicString<CharType, EosChar>::CopyString(const BasicString& _source, size_t _size, const size_t _start_index) const
{
	if (data == nullptr || (_source.size == NullSize && _size == NullSize))
		return;
	if (_size == NullSize)
		_size = _source.size;
	memcpy(data + _start_index, _source.data, _size);
}

template<typename CharType, CharType EosChar>
void Core::CoreType::BasicString<CharType, EosChar>::DeletePointer()
{
	delete data;
	data = nullptr;
	size = 0;
}

template<typename CharType, CharType EosChar>
void Core::CoreType::BasicString<CharType, EosChar>::VerifyString(const size_t _end_of_string_index)
{
	if (_end_of_string_index != NullSize)
	{
		data[_end_of_string_index] = EosChar;
		size = _end_of_string_index;
		return;
	}

	if (capacity == NullSize)
	{
		size = NullSize;
		return;
	}

	bool eos_found = false;
	for (size_t i = 0; i < capacity; ++i)
	{
		if (data[i] == EosChar)
		{
			size = i;
			eos_found = true;
			break;
		}
	}

	if (!eos_found)
	{
		data[capacity - 1] = EosChar;
		size = capacity - 1;
	}
}

template<typename CharType, CharType EosChar>
template<typename>
Core::CoreType::BasicString<wchar_t, L'\0'> Core::CoreType::BasicString<CharType, EosChar>::ToWideString()
{
	wchar_t* wide_pointer = new wchar_t[size + 1];
	size_t out_size = 0;
	mbstowcs_s(&out_size, wide_pointer, size + 1, data, size);

	return WideString(wide_pointer, out_size);
}

template<typename CharType, CharType EosChar>
template<typename>
Core::CoreType::BasicString<char, '\0'> Core::CoreType::BasicString<CharType, EosChar>::ToCharString()
{
	char* char_pointer = new char[size + 1];
	size_t out_size = 0;
	wcstombs_s(&out_size, char_pointer, size + 1, data, size);

	return String(char_pointer, out_size);
}