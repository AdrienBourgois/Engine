#pragma once
#include <vector>

template<typename T>
Core::CoreType::Container::Vector<T>::Vector(const size_t _capacity): capacity(_capacity)
{
	elements = new T[_capacity];
}

template<typename T>
Core::CoreType::Container::Vector<T>::Vector(const Vector& _other)
{
	Reserve(_other.size);
	size = _other.size;
	for (int i = 0; i < _other.size; ++i)
	{
		elements[i] = _other.elements[i];
	}
}

template<typename T>
Core::CoreType::Container::Vector<T>::Vector(Vector&& _other) noexcept
{
	capacity = _other.capacity;
	elements = _other.elements;
	size = _other.size;

	_other.capacity = 0;
	_other.size = 0;
	_other.elements = nullptr;
}

template<typename T>
Core::CoreType::Container::Vector<T>& Core::CoreType::Container::Vector<T>::operator=(const Vector& _other)
{
	Reserve(_other.size);
	size = _other.size;
	for (int i = 0; i < _other.size; ++i)
	{
		elements[i] = _other.elements[i];
	}

	return *this;
}

template<typename T>
Core::CoreType::Container::Vector<T>& Core::CoreType::Container::Vector<T>::operator=(Vector&& _other) noexcept
{
	capacity = _other.capacity;
	elements = _other.elements;
	size = _other.size;

	_other.capacity = 0;
	_other.size = 0;
	_other.elements = nullptr;

	return *this;
}

template<typename T>
Core::CoreType::Container::Vector<T>::~Vector()
{
	Deallocate();
}

template<typename T>
T& Core::CoreType::Container::Vector<T>::operator[](const size_t _index)
{
	return elements[_index];
}

template<typename T>
void Core::CoreType::Container::Vector<T>::PushBack(T _new_element)
{
	VerifyAllocation(size + 1);
	elements[size] = _new_element;
	++size;
}

template<typename T>
void Core::CoreType::Container::Vector<T>::operator+=(T _new_element)
{
	PushBack(_new_element);
}

template<typename T>
void Core::CoreType::Container::Vector<T>::Insert(T _new_element, size_t _index)
{
	VerifyAllocation(size + 1);
	for (int i = size; i < _index; --i)
		elements[i + 1] = elements[i];
	elements[_index = _new_element];
}

template<typename T>
void Core::CoreType::Container::Vector<T>::Erase(const size_t _index)
{
	if (size > _index)
		for (int i = _index; i < size; ++i)
		{
			elements[i].~T();
			elements[i] = elements[i + 1];
		}
	--size;
}

template<typename T>
void Core::CoreType::Container::Vector<T>::Clear()
{
	Deallocate();
}

template<typename T>
void Core::CoreType::Container::Vector<T>::ShrinkToFit()
{
	Reallocate(size);
}

template<typename T>
void Core::CoreType::Container::Vector<T>::Reserve(const size_t _capacity)
{
	Allocate(_capacity);
}

template<typename T>
size_t Core::CoreType::Container::Vector<T>::Size() const
{
	return size;
}

template<typename T>
size_t Core::CoreType::Container::Vector<T>::Capacity() const
{
	return capacity;
}

template<typename T>
void Core::CoreType::Container::Vector<T>::Allocate(const size_t _new_capacity)
{
	if (elements)
		Reallocate(_new_capacity);
	else
		capacity = _new_capacity;
	elements = new T[capacity];
}

template<typename T>
void Core::CoreType::Container::Vector<T>::Reallocate(const size_t _new_capacity)
{
	T* new_array = new T[_new_capacity];
	CopyData(new_array);
	const size_t temp_size = size;
	Deallocate();
	elements = new_array;
	capacity = _new_capacity;
	size = temp_size;
}

template<typename T>
void Core::CoreType::Container::Vector<T>::Deallocate()
{
	delete[] elements;
	elements = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
void Core::CoreType::Container::Vector<T>::VerifyAllocation(const size_t _capacity)
{
	if (capacity < _capacity)
		Reallocate(_capacity);
}

template<typename T>
void Core::CoreType::Container::Vector<T>::CopyData(T* _other)
{
	for (size_t i = 0; i < size; ++i)
	{
		_other[i] = elements[i];
	}
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::IsEmpty() const
{
	return !elements && !capacity;
}

template<typename T>
T* Core::CoreType::Container::Vector<T>::GetData() const
{
	return elements;
}


template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::Begin()
{
	return VectorIterator(elements);
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::End()
{
	return VectorIterator(elements + size);
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::begin()
{
	return Begin();
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::end()
{
	return End();
}

/* VectorIterator */

template<typename T>
Core::CoreType::Container::Vector<T>::VectorIterator::VectorIterator(T* _pointer) : pointer(_pointer) {}

template<typename T>
T& Core::CoreType::Container::Vector<T>::VectorIterator::operator*()
{
	return *pointer;
}

template<typename T>
T* Core::CoreType::Container::Vector<T>::VectorIterator::operator->()
{
	return pointer;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator==(const VectorIterator& _other)
{
	return pointer == _other.pointer;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator!=(const VectorIterator& _other)
{
	return pointer != _other.pointer;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::Next()
{
	return operator++();
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::operator++()
{
	++pointer;
	return *this;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::Previous()
{
	return operator--();
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::operator--()
{
	--pointer;
	return *this;
}

template<typename T>
T& Core::CoreType::Container::Vector<T>::VectorIterator::operator[](const size_t _index)
{
	return *(pointer + _index);
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::operator+=(const size_t _index)
{
	pointer += _index;
	return *this;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::operator-=(const size_t _index)
{
	pointer -= _index;
	return *this;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator<(const VectorIterator& _other)
{
	return pointer < _other.pointer;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator>(const VectorIterator& _other)
{
	return pointer > _other.pointer;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator<=(const VectorIterator& _other)
{
	return pointer <= _other.pointer;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator>=(const VectorIterator& _other)
{
	return pointer >= _other.pointer;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::VectorIterator::operator+(const size_t _delta)
{
	return VectorIterator(pointer + _delta);
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::VectorIterator::operator-(const size_t _delta)
{
	return VectorIterator(pointer - _delta);
}
