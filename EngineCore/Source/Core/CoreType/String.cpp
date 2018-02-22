#include "Core/CoreType/String.h"
#include <cstring>
#include <cstdlib>
#include <string>

Core::CoreType::String::String(const int _value)
{
	std::string string = std::to_string(_value);
	capacity = static_cast<unsigned>(string.size() + 1);
	data = new char[capacity];
	memcpy(data, string.c_str(), string.size());
	VerifyString();
}

Core::CoreType::String::String(const float _value)
{
	std::string string = std::to_string(_value);
	capacity = static_cast<unsigned>(string.size() + 1);
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
	return data == nullptr || size == 0;
}

bool Core::CoreType::String::IsNull() const
{
	return data == nullptr;
}

char* Core::CoreType::String::At(const unsigned _index) const
{
	if (_index > size)
		return nullptr;
	return data + _index;
}

char Core::CoreType::String::operator[](const unsigned _index) const
{
	if (_index > size)
		return 0;
	return data[_index];
}

Core::CoreType::String& Core::CoreType::String::operator=(const String& _other_string)
{
	if(_other_string.size + 1 > capacity)
	{
		DeletePointer();
		capacity = _other_string.size + 1;
		data = new char[capacity];
	}

	memcpy(data, _other_string.data, _other_string.size);

	VerifyString(_other_string.size);

	return *this;
}

Core::CoreType::String Core::CoreType::String::operator+(const String& _other_string) const
{
	if(_other_string.IsNull()) return *this;

	String string;

	string.capacity = size + _other_string.size + 1;
	string.data = new char[string.capacity];
	memcpy(string.data, data, size);
	memcpy(string.data + size, _other_string.data, _other_string.size);

	string.VerifyString();

	return string;
}

Core::CoreType::String Core::CoreType::String::operator+(const char _character) const
{
	String string;

	string.capacity = size + 2;
	string.data = new char[string.capacity];
	memcpy(string.data, data, size);
	string.data[size] = _character;

	string.VerifyString();

	return string;

}

void Core::CoreType::String::operator+=(const String& _other_string)
{
	Append(_other_string);
}

void Core::CoreType::String::operator+=(const char _character)
{
	Append(_character);
}

bool Core::CoreType::String::operator==(const String& _other_string) const
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

bool Core::CoreType::String::operator!=(const String& _other_string) const
{
	return !operator==(_other_string);
}

Core::CoreType::String::operator bool() const
{
	return size != 0;
}

void Core::CoreType::String::Append(const String& _other_string)
{
	const unsigned int new_size = size + _other_string.size;
	unsigned int first_string_size = size;
	if (first_string_size == NullSize)
		first_string_size = 0;

	if(capacity == NullSize || capacity < new_size + 1)
		Reserve(new_size + 1);

	memcpy(data + first_string_size, _other_string.data, _other_string.size);

	VerifyString(new_size);
}

void Core::CoreType::String::Append(const char _character)
{
	const unsigned int new_size = size + 1;

	if(capacity == NullSize || capacity < new_size + 1)
		Reserve(new_size + 1);

	data[size] = _character;

	VerifyString(new_size);
}

bool Core::CoreType::String::Contain(const String& _string_to_find) const
{
	return First(_string_to_find) != NullSize;
}

unsigned Core::CoreType::String::First(const String& _string_to_find) const
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
	return NullSize;
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

bool Core::CoreType::String::Reserve(const unsigned _bytes_count)
{
	if (_bytes_count <= REAL_SIZE(capacity) || _bytes_count <= REAL_SIZE(size))
		return false;

	capacity = _bytes_count;

	char* new_pointer = new char[capacity];
	if(REAL_SIZE(size))
		memcpy(new_pointer, data, size);
	delete data;
	data = new_pointer;
	data[REAL_SIZE(size)] = '\0';
	VerifyString();

	return true;
}

void Core::CoreType::String::CopyString(const String& _source, unsigned _size, const unsigned _start_index) const
{
	if (data == nullptr || (_source.size == NullSize && _size == NullSize))
		return;
	if (_size == NullSize)
		_size = _source.size;
	memcpy(data + _start_index, _source.data, _size);
}

void Core::CoreType::String::DeletePointer()
{
	delete data;
	delete widePointer;

	data = nullptr;
	widePointer = nullptr;

	size = 0;
}

void Core::CoreType::String::VerifyString(const unsigned _end_of_string_index)
{
	if(_end_of_string_index != NullSize)
	{
		data[_end_of_string_index] = '\0';
		size = _end_of_string_index;
		return;
	}

	if(capacity == NullSize)
	{
		size = NullSize;
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
