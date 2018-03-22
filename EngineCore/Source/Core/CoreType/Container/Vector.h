#pragma once

#include "Core/Interface/Iterators.h"

namespace Core
{
	namespace CoreType
	{
		namespace Container
		{
			/**
			 * \brief Container that ensure to keep elements continuously in memory
			 * \tparam T Type of elements in this container
			 */
			template<typename T>
			class Vector
			{
			public:
				/**
				 * \brief Iterator for the Vector class
				 */
				class VectorIterator : public Interface::Iterator::IContiguousIterator<T, VectorIterator>
				{
				public:
					/**
					 * \brief Constructor
					 * \param _pointer Element to point to
					 */
					explicit VectorIterator(T* _pointer);
					/**
					 * \brief Default destructor
					 */
					~VectorIterator() = default;

					T& operator*() override;
					T* operator->() override;

					bool operator==(const VectorIterator& _other) override;
					bool operator!=(const VectorIterator& _other) override;

					VectorIterator& Next() override;
					VectorIterator& operator++() override;

					VectorIterator& Previous() override;
					VectorIterator& operator--() override;

					T& operator[](size_t _index) override;

					VectorIterator& operator+=(size_t _index) override;
					VectorIterator& operator-=(size_t _index) override;

					bool operator<(const VectorIterator& _other) override;
					bool operator>(const VectorIterator& _other) override;
					bool operator<=(const VectorIterator& _other) override;
					bool operator>=(const VectorIterator& _other) override;

					VectorIterator operator+(size_t _delta) override;
					VectorIterator operator-(size_t _delta) override;

				private:
					/**
					 * \brief Pointer to element
					 */
					T* pointer;
				};

				/**
				 * \brief Default constructor
				 */
				Vector() = default;
				/**
				 * \brief Constructor with memory allocated
				 * \param _capacity Base capacity
				 * \note The desired capacity is a minimum. The Vector can allocate a higher number of elements to avoid too many allocations in the future
				 */
				explicit Vector(size_t _capacity);
				/**
				 * \brief Destructor
				 */
				~Vector();

				/**
				 * \brief Copy constructor
				 * \param _other Vector to copy
				 */
				Vector(const Vector& _other);
				/**
				 * \brief Move constructor
				 * \param _other Vector who sees his data stolen
				 */
				Vector(Vector&& _other) noexcept;
				/**
				 * \brief Copy assignment operator
				 * \param _other Vector to copy
				 * \return Reference to this Vector
				 */
				Vector& operator=(const Vector& _other);
				/**
				 * \brief Move assignment operator
				 * \param _other Vector who sees himself stealing his data
				 * \return Reference to this Vector
				 */
				Vector& operator=(Vector&& _other) noexcept;

				/**
				 * \brief Access an element with his index
				 * \param _index Index of element requested
				 * \return Reference to element requested
				 */
				T& operator[](size_t _index);

				/**
				 * \brief Add element at the end of the Vector
				 * \param _new_element Element to add
				 */
				void PushBack(T _new_element);
				/**
				 * \brief Add element at the end of the Vector
				 * \param _new_element Element to add
				 */
				void operator+=(T _new_element);
				/**
				 * \brief Add element at the desired index of the Vector
				 * \param _new_element Element to add
				 * \param _index Index where the element will be inserted
				 */
				void Insert(T _new_element, size_t _index);
				/**
				 * \brief Erase the element at the desired index
				 * \param _index Index of element to erase
				 */
				void Erase(size_t _index);
				/**
				 * \brief Erase all elements of the Vector
				 */
				void Clear();

				/**
				 * \brief Shrink the capacity of the Vector to fit the count of elements
				 */
				void ShrinkToFit();
				/**
				 * \brief Allocate memory for future elements
				 * \param _capacity New capacity of the Vector
				 * \note The desired capacity is a minimum. The Vector can allocate a higher number of elements to avoid too many allocations in the future
				 */
				void Reserve(size_t _capacity);

				/**
				 * \brief Return count of elements used in Vector / Size of the Vector
				 * \return Size of the Vector
				 */
				size_t Size() const;
				/**
				 * \brief Return size (count of elements) of memory allocated
				 * \return Capacity of the Vector
				 */
				size_t Capacity() const;
				/**
				 * \brief Define if the Vector is empty, has any elements and don't have any memory allocated
				 * \return Is Vector empty
				 */
				bool IsEmpty() const;

				/**
				 * \brief Return pointer to the array used by the Vector to store elements
				 * \return Pointer to array
				 */
				T* GetData() const;

				/**
				 * \brief Return an iterator to the first element in the Vector
				 * \return Iterator to the first element
				 */
				VectorIterator Begin();
				/**
				 * \brief Return an iterator to the past-the-end element of the Vector
				 * \return Iterator to the past-the-end element
				 */
				VectorIterator End();

				// ReSharper disable CppInconsistentNaming
				/**
				 * \brief Return an iterator to the first element in the Vector
				 * \return Iterator to the first element
				 * \note Call Begin() - Use of lower case to match for-loop range restrictions
				 */
				VectorIterator begin();
				/**
				 * \brief Return an iterator to the past-the-end element of the Vector
				 * \return Iterator to the past-the-end element
				 * \note Call End() - Use of lower case to match for-loop range restrictions
				 */
				VectorIterator end();
				// ReSharper restore CppInconsistentNaming

			private:
				/**
				 * \brief Allocate memory
				 * \param _new_capacity Size (in elements) of memory allocated
				 * \note Use this function internally instead of Reallocate(). Allocate() test current state to reallocated already used elements if they exists
				 */
				void Allocate(size_t _new_capacity);
				/**
				 * \brief Allocate memory and move elements
				 * \param _new_capacity Size (in elements) of memory allocated
				 */
				void Reallocate(size_t _new_capacity);
				/**
				 * \brief Free the memory
				 */
				void Deallocate();
				/**
				 * \brief Test current capacity and reallocate memory if needed
				 * \param _capacity Target capacity
				 */
				void VerifyAllocation(size_t _capacity);
				/**
				 * \brief Copy elements of current memory range to another range
				 * \param _other Pointer to range of data where copy elements
				 */
				void CopyData(T* _other);

				/**
				 * \brief Array of elements stored
				 */
				T* elements = nullptr;

				/**
				 * \brief Count of elements used in the Vector
				 */
				size_t size = 0;
				/**
				 * \brief Count of elements allocated in the Vector
				 */
				size_t capacity = 0;
			};
		}
	}
}

#include "Core/CoreType/Container/Vector.inl"
