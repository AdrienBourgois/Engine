#pragma once

template<typename T>
Core::CoreType::Container::Vector<T>::Vector(const size_t _capacity): capacity(_capacity)
{
	elements = new T[_capacity];
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
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::Begin()
{
	return VectorIterator(*this);
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::End()
{
	return VectorIterator(*this, IsEmpty() ? 0 : size);
}

/* VectorIterator */

template<typename T>
Core::CoreType::Container::Vector<T>::VectorIterator::VectorIterator(Vector<T>& _vector) : vector(_vector) {}

template<typename T>
Core::CoreType::Container::Vector<T>::VectorIterator::VectorIterator(Vector<T>& _vector, const size_t _index) : vector(_vector), index(_index) {}

template<typename T>
T& Core::CoreType::Container::Vector<T>::VectorIterator::operator*()
{
	return vector[index];
}

template<typename T>
T* Core::CoreType::Container::Vector<T>::VectorIterator::operator->()
{
	return &vector[index];
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator==(const VectorIterator& _other)
{
	return &_other.vector == &vector && _other.index == index;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator!=(const VectorIterator& _other)
{
	return &_other.vector != &vector || _other.index != index;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::Next()
{
	return operator++();
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::operator++()
{
	++index;
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
	--index;
	return *this;
}

template<typename T>
T& Core::CoreType::Container::Vector<T>::VectorIterator::operator[](size_t _index)
{
	return vector[index];
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::operator+=(const size_t _index)
{
	index += _index;
	return *this;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator& Core::CoreType::Container::Vector<T>::VectorIterator::operator-=(const size_t _index)
{
	index -= _index;
	return *this;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator<(const VectorIterator& _other)
{
	return &_other.vector == &vector && _other.index < index;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator>(const VectorIterator& _other)
{
	return &_other.vector == &vector && _other.index > index;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator<=(const VectorIterator& _other)
{
	return &_other.vector == &vector && _other.index <= index;
}

template<typename T>
bool Core::CoreType::Container::Vector<T>::VectorIterator::operator>=(const VectorIterator& _other)
{
	return &_other.vector == &vector && _other.index >= index;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::VectorIterator::operator+(VectorIterator _other)
{
	index += _other.index;
	return *this;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::VectorIterator::operator-(VectorIterator _other)
{
	index -= _other.index;
	return *this;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::VectorIterator::operator+(const size_t _delta)
{
	index += _delta;
	return *this;
}

template<typename T>
typename Core::CoreType::Container::Vector<T>::VectorIterator Core::CoreType::Container::Vector<T>::VectorIterator::operator-(const size_t _delta)
{
	index -= _delta;
	return *this;
}
