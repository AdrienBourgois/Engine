#include "Core/CoreType/String.h"
#include <cstring>
#include <stdlib.h>
#include <string>

Core::CoreType::String::String()
{}

Core::CoreType::String::String(const int _value)
{
	std::string string = std::to_string(_value);
	capacity = static_cast<unsigned>(string.size());
	data = new char[capacity];
	memcpy(data, string.c_str(), string.size());
	VerifyString();
}

Core::CoreType::String::String(const float _value)
{
	std::string string = std::to_string(_value);
	size = static_cast<unsigned>(string.size());
	capacity = size + 1;
	data = new char[capacity];
	memcpy(data, string.c_str(), string.size());
	VerifyString();
}

Core::CoreType::String::String(const char* _text, const unsigned int _size)
{
	if (_size != 0)
	{
		capacity = _size;
		data = new char[capacity];
		memcpy(data, _text, _size);
		VerifyString();
	}
}

Core::CoreType::String::String(const String& _other_string)
{
	capacity = _other_string.size + 1;
	size = _other_string.size;
	data = new char[capacity];
	memcpy(data, _other_string.data, size);

	VerifyString();
}

Core::CoreType::String::~String()
{
	DeletePointer();
}

bool Core::CoreType::String::IsEmpty() const
{
	if(data == nullptr || size == 0)
		return true;
	return false;
}

bool Core::CoreType::String::IsNull() const
{
	if (data == nullptr)
		return true;
	return false;
}

char* Core::CoreType::String::At(const unsigned _range) const
{
	if (_range > size)
		return nullptr;
	return data + _range;
}

char Core::CoreType::String::operator[](const unsigned _range) const
{
	if (_range > size)
		return 0;
	return data[_range];
}

void Core::CoreType::String::operator=(const String _other_string)
{
	if(_other_string.size + 1 > capacity)
	{
		DeletePointer();
		capacity = _other_string.size + 1;
		data = new char[capacity];
	}

	memcpy(data, _other_string.data, _other_string.size);

	VerifyString();
}

Core::CoreType::String Core::CoreType::String::operator+(const String _other_string) const
{
	String string;

	string.capacity = size + _other_string.size + 1;
	string.data = new char[string.capacity];
	memcpy(string.data, data, size);
	memcpy(string.data + size, _other_string.data, _other_string.size);

	string.VerifyString();

	return string;
}

void Core::CoreType::String::operator+=(const String _other_string)
{
	Append(_other_string);
}

void Core::CoreType::String::operator+=(char _character)
{
	Append(String(&_character, 1));
}

bool Core::CoreType::String::operator==(const String _other_string) const
{
	if(size != _other_string.size)
		return false;

	for (unsigned int i = 0; i < size && i < _other_string.size; ++i)
	{
		if (data[i] != _other_string.data[i])
			return false;
	}
	return true;
}

bool Core::CoreType::String::operator!=(const String _other_string) const
{
	return !operator==(_other_string);
}

Core::CoreType::String::operator bool() const
{
	if (size)
		return true;

	return false;
}

void Core::CoreType::String::Append(const String _other_string)
{
	const unsigned int new_size = size + _other_string.size;
	const unsigned int first_string_size = size;

	if(capacity < new_size + 1)
	{
		capacity = new_size + 1;
		char* new_pointer = new char[capacity];
		memcpy(new_pointer, data, size);
		DeletePointer();
		data = new_pointer;
	}

	memcpy(data + first_string_size, _other_string.data, _other_string.size);

	VerifyString();
}

bool Core::CoreType::String::Contain(const String _string_to_find) const
{
	if(First(_string_to_find) == -1)
		return false;
	return true;
}

unsigned Core::CoreType::String::First(const String _string_to_find) const
{
	if(_string_to_find.size > size)
		return false;

	for (unsigned int i = 0; i < size; ++i)
	{
		if(data[i] == _string_to_find[0])
		{
			bool temp_found = true;
			for (unsigned int j = 0; j < size && j < _string_to_find.size; ++j)
			{
				if(data[i + j] != _string_to_find[j])
				{
					temp_found = false;
					break;
				}
			}
			if(temp_found)
					return i;
		}
	}
	return -1;
}

wchar_t const* Core::CoreType::String::ToWideString()
{
	if(!widePointer)
	{
		widePointer = new wchar_t[size + 1];
		size_t out_size = 0;
		mbstowcs_s(&out_size, widePointer, size + 1, data, size);
	}

	return widePointer;
}

void Core::CoreType::String::DeletePointer()
{
	if (data)
		delete data;
	if (widePointer)
		delete widePointer;

	data = nullptr;
	widePointer = nullptr;

	size = 0;
}

void Core::CoreType::String::VerifyString()
{
	if(capacity == -1)
	{
		size = -1;
		return;
	}

	bool eos_found = false;
	for (unsigned int i = 0; i < capacity; ++i)
	{
		if (data[i] == '\0')
		{
			size = i;
			eos_found = true;
			break;
		}
	}

	if(!eos_found)
	{
		data[capacity - 1] = '\0';
		size = capacity - 1;
	}
}
