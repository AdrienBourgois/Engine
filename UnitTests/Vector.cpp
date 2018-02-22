#include "stdafx.h"
#include "CppUnitTest.h"
#include "Core/CoreType/Container/Vector.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Vector)
	{
	public:

		const size_t base_vector_size = 50;
		const size_t testing_count = 10;

		Core::CoreType::Container::Vector<int> GetTestVector() const
		{
			Core::CoreType::Container::Vector<int> vec;
			vec.Reserve(base_vector_size);

			for (int i = 0; i < static_cast<int>(base_vector_size); ++i)
			{
				vec.PushBack(i);
			}

			return vec;
		}

		TEST_CLASS_INITIALIZE(Initialize)
		{
			Logger::WriteMessage("Start Testing Core::CoreType::Container::Vector class");
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			Logger::WriteMessage("Finalize Testing Core::CoreType::Container::Vector class");
		}

		TEST_METHOD(Reserve)
		{
			Core::CoreType::Container::Vector<int> vec = GetTestVector();
			vec.Reserve(base_vector_size + 20);
			Assert::IsTrue(vec.Capacity() >= base_vector_size + 20);
		}

		TEST_METHOD(Insert)
		{
			Core::CoreType::Container::Vector<int> vec = GetTestVector();
			for (int i = 0; i < static_cast<int>(testing_count); ++i)
			{
				vec.PushBack(i);
			}
			Assert::IsTrue(vec.Size() == base_vector_size + testing_count);
		}

		TEST_METHOD(Get)
		{
			Core::CoreType::Container::Vector<int> vec = GetTestVector();
			for (int i = 0; i < static_cast<int>(base_vector_size); ++i)
			{
				Assert::IsTrue(vec[i] == i);
			}
		}

		TEST_METHOD(Iterator)
		{
			Core::CoreType::Container::Vector<int> vec = GetTestVector();
			auto it = vec.Begin();
			Assert::IsTrue(*it == 0);
			for (int i = 1; i < static_cast<int>(base_vector_size); ++i)
			{
				++it;
				Assert::IsTrue(*it == i);
			}
		}

		TEST_METHOD(IteratorLoop)
		{
			Core::CoreType::Container::Vector<int> vec = GetTestVector();
			size_t count = 0;
			auto it = vec.Begin();
			const auto it_end = vec.End();
			for (; it != it_end; ++it)
				++count;
			Assert::IsTrue(count == vec.Size());
		}
	};
}