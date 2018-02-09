#pragma once

#include "Core/CoreType/Container/Iterator/Iterators.h"

namespace Core
{
	namespace CoreType
	{
		namespace Container
		{
			template<typename T>
			class Vector
			{
			public:
				class VectorIterator : public Iterator::ContiguousIterator<T, VectorIterator>
				{
				public:
					explicit VectorIterator(Vector& _vector);
					explicit VectorIterator(Vector& _vector, size_t _index);
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

					VectorIterator operator+(VectorIterator _other) override;
					VectorIterator operator-(VectorIterator _other) override;
					VectorIterator operator+(size_t _delta) override;
					VectorIterator operator-(size_t _delta) override;
				private:
					Vector& vector = nullptr;
					size_t index = 0;
				};

				Vector() = default;
				explicit Vector(size_t _capacity);
				Vector(const Vector& _other) = default;
				Vector(Vector&& _other) noexcept = default;
				Vector& operator=(const Vector& _other) = default;
				Vector& operator=(Vector&& _other) noexcept = default;
				~Vector();

				T& operator[](size_t _index);

				void PushBack(T _new_element);
				void operator+=(T _new_element);
				void Insert(T _new_element, size_t _index);
				void Erase(size_t _index);
				void Clear();

				void ShrinkToFit();
				void Reserve(size_t _capacity);

				size_t Size() const;
				size_t Capacity() const;
				bool IsEmpty() const;

				VectorIterator Begin();
				VectorIterator End();

			private:
				void Allocate(size_t _new_capacity);
				void Reallocate(size_t _new_capacity);
				void Deallocate();
				void VerifyAllocation(size_t _capacity);
				void CopyData(T* _other);

				T* elements = nullptr;

				size_t size = 0;
				size_t capacity = 0;
			};
		}
	}
}

#include "Core/CoreType/Container/Vector.inl"
