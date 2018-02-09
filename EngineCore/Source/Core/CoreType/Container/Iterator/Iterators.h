#pragma once

namespace Core
{
	namespace CoreType
	{
		namespace Container
		{
			namespace Iterator
			{
				/**
				 * \brief
				 * \tparam T Type of
				 * \tparam ChildClass
				 */
				template<typename T, typename ChildClass>
				class Iterator
				{
				public:
					virtual ~Iterator() = default;

					virtual T& operator*() = 0;
					virtual T* operator->() = 0;

					virtual bool operator==(const ChildClass& _other) = 0;
					virtual bool operator!=(const ChildClass& _other) = 0;
				};

				template<typename T, typename ChildClass>
				class ForwardIterator : public Iterator<T, ChildClass>
				{
					virtual ChildClass& Next() = 0;
					virtual ChildClass& operator++() = 0;
				};

				template<typename T, typename ChildClass>
				class BidirectionnalIterator : public ForwardIterator<T, ChildClass>
				{
					virtual ChildClass& Previous() = 0;
					virtual ChildClass& operator--() = 0;
				};

				template<typename T, typename ChildClass>
				class RandomAccessIterator : public BidirectionnalIterator<T, ChildClass>
				{
					virtual T& operator[](size_t _index) = 0;

					virtual ChildClass& operator+=(size_t _index) = 0;
					virtual ChildClass& operator-=(size_t _index) = 0;

					virtual bool operator<(const ChildClass& _other) = 0;
					virtual bool operator>(const ChildClass& _other) = 0;
					virtual bool operator<=(const ChildClass& _other) = 0;
					virtual bool operator>=(const ChildClass& _other) = 0;

					virtual ChildClass operator+(ChildClass _other) = 0;
					virtual ChildClass operator-(ChildClass _other) = 0;
				};

				template<typename T, typename ChildClass>
				class ContiguousIterator : public RandomAccessIterator<T, ChildClass>
				{
					virtual ChildClass operator+(size_t _delta) = 0;
					virtual ChildClass operator-(size_t _delta) = 0;
				};
			}
		}
	}
}
