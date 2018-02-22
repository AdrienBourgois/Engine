#pragma once

namespace Core
{
	namespace Interface
	{
		namespace Iterator
		{
			/**
			* \brief Base interface for utility classes that iterate over elements in containers
			* \tparam T Type of elements pointed
			* \tparam ChildClass Child class that inherit from this interface
			*/
			template<typename T, typename ChildClass>
			class IIterator
			{
			public:
				/**
				* \brief Default virtual Destructor
				*/
				virtual ~IIterator() = default;

				/**
				* \brief Get reference to object pointed to
				* \return Reference to element pointed
				*/
				virtual T& operator*() = 0;
				/**
				* \brief Dereference operator overload
				* \return Element pointed to
				*/
				virtual T* operator->() = 0;

				/**
				* \brief Compare operator overload
				* \param _other Other iterator to compare
				* \return Are Iterator point to same element
				*/
				virtual bool operator==(const ChildClass& _other) = 0;
				/**
				* \brief Compare operator overload
				* \param _other Other iterator to compare
				* \return Are Iterator point not to same element
				*/
				virtual bool operator!=(const ChildClass& _other) = 0;
			};

			/**
			* \brief Interface for utility classes that can iterate in a forward way over elements in containers
			* \tparam T Type of elements pointed
			* \tparam ChildClass Child class that inherit from this interface
			*/
			template<typename T, typename ChildClass>
			class IForwardIterator : public IIterator<T, ChildClass>
			{
				/**
				* \brief Iterator go to next element
				* \return Iterator to next element
				*/
				virtual ChildClass& Next() = 0;
				/**
				* \brief Iterator go to next element
				* \return Iterator to next element
				*/
				virtual ChildClass& operator++() = 0;
			};

			/**
			* \brief Interface for utility classes that can iterate in both ways over elements in containers
			* \tparam T Type of elements pointed
			* \tparam ChildClass Child class that inherit from this interface
			*/
			template<typename T, typename ChildClass>
			class IBidirectionnalIterator : public IForwardIterator<T, ChildClass>
			{
				/**
				* \brief Iterator go to previous element
				* \return Iterator to previous element
				*/
				virtual ChildClass& Previous() = 0;
				/**
				* \brief Iterator go to previous element
				* \return Iterator to previous element
				*/
				virtual ChildClass& operator--() = 0;
			};

			/**
			* \brief Interface for utility classes that can iterate randomly over elements in containers
			* \tparam T Type of elements pointed
			* \tparam ChildClass Child class that inherit from this interface
			*/
			template<typename T, typename ChildClass>
			class IRandomAccessIterator : public IBidirectionnalIterator<T, ChildClass>
			{
				/**
				* \brief Returns a reference to the element located n elements ahead of the element pointed by the iterator
				* \param _index Number of element ahead the element currently pointed
				* \return Reference to the requested element
				*/
				virtual T& operator[](size_t _index) = 0;

				/**
				* \brief Advance the iterator by n element positions
				* \param _index Number of element to offset
				* \return This iterator
				*/
				virtual ChildClass& operator+=(size_t _index) = 0;
				/**
				* \brief Decreases the iterator by n element positions
				* \param _index Number of element to offset
				* \return This iterator
				*/
				virtual ChildClass& operator-=(size_t _index) = 0;

				/**
				* \brief Compare iterators
				* \param _other Other iterator to compare
				* \return Comparison result
				*/
				virtual bool operator<(const ChildClass& _other) = 0;
				/**
				* \brief Compare iterators
				* \param _other Other iterator to compare
				* \return Comparison result
				*/
				virtual bool operator>(const ChildClass& _other) = 0;
				/**
				* \brief Compare iterators
				* \param _other Other iterator to compare
				* \return Comparison result
				*/
				virtual bool operator<=(const ChildClass& _other) = 0;
				/**
				* \brief Compare iterators
				* \param _other Other iterator to compare
				* \return Comparison result
				*/
				virtual bool operator>=(const ChildClass& _other) = 0;
			};

			/**
			* \brief Interface for utility classes that can iterate randomly over elements in containers with contiguous elements in memory
			* \tparam T Type of elements pointed
			* \tparam ChildClass Child class that inherit from this interface
			*/
			template<typename T, typename ChildClass>
			class IContiguousIterator : public IRandomAccessIterator<T, ChildClass>
			{
				/**
				* \brief Get iterator to element n elements ahead
				* \param _delta Number of element to offset
				* \return Iterator to new pointed element
				*/
				virtual ChildClass operator+(size_t _delta) = 0;
				/**
				* \brief Get iterator to element n elements behind
				* \param _delta Number of element to offset
				* \return Iterator to new pointed element
				*/
				virtual ChildClass operator-(size_t _delta) = 0;
			};
		}
	}
}
