#include "String.h"
#include <cstring>

CoreType::String::String(const char* _text, unsigned int _size)
{
	pointer = new char[_size];
	size = _size - 1;
	memcpy(pointer, _text, _size);
}

CoreType::String::String(const String& _other_string)
{
	size = _other_string.size;
	pointer = new char[size + 1];
	memcpy(pointer, _other_string.pointer, size + 1);
}

CoreType::String::~String()
{
	DeletePointer();
}

void CoreType::String::operator=(String _other_string)
{
	DeletePointer();
	size = _other_string.size;
	pointer = new char[size + 1];
	memcpy(pointer, _other_string.pointer, size + 1);
}

CoreType::String CoreType::String::operator+(String _other_string) const
{
	String string;

	string.size = size + _other_string.size;
	string.pointer = new char[string.size + 1];
	memcpy(string.pointer, pointer, size);
	memcpy(string.pointer + size, _other_string.pointer, _other_string.size + 1);

	return string;
}

void CoreType::String::operator+=(String _other_string)
{
	Append(_other_string);
}

bool CoreType::String::operator==(String _other_string) const
{
	for (unsigned int i = 0; i < size && i < _other_string.size; ++i)
	{
		if (pointer[i] != _other_string.pointer[i])
			return false;
	}
	return true;
}

void CoreType::String::Append(String _other_string)
{
	unsigned int new_size = size + _other_string.size;
	char* new_pointer = new char[new_size + 1];
	memcpy(new_pointer, pointer, size);
	memcpy(new_pointer + size, _other_string.pointer, _other_string.size + 1);
	pointer = new_pointer;
	size = new_size;
}

void CoreType::String::DeletePointer()
{
	if (pointer)
		delete pointer;

	size = 0;
}
