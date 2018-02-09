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

		TEST_METHOD(Reserve)
		{
			Core::CoreType::Container::Vector<int> vec;
			vec.Reserve(20);
			Assert::IsTrue(vec.Capacity() >= 20);
		}

		TEST_METHOD(Insert)
		{
			Core::CoreType::Container::Vector<int> vec;
			Assert::IsTrue(vec.Size() == 0);
			vec.PushBack(0);
			vec.PushBack(1);
			vec.PushBack(2);
			vec.PushBack(3);
			Assert::IsTrue(vec.Size() == 4);
		}

		TEST_METHOD(Get)
		{
			Core::CoreType::Container::Vector<int> vec;
			vec.PushBack(0);
			vec.PushBack(1);
			vec.PushBack(2);
			vec.PushBack(3);
			Assert::IsTrue(vec[2] == 2);
		}

		TEST_METHOD(Iterator)
		{
			Core::CoreType::Container::Vector<int> vec;
			vec.PushBack(0);
			vec.PushBack(1);
			auto it = vec.Begin();
			Assert::IsTrue(*it == 0);
			++it;
			Assert::IsTrue(*it == 1);
		}

		TEST_METHOD(IteratorLoop)
		{
			Core::CoreType::Container::Vector<int> vec;
			vec.PushBack(0);
			vec.PushBack(1);
			vec.PushBack(2);
			vec.PushBack(3);
			size_t count = 0;
			auto it = vec.Begin();
			const auto it_end = vec.End();
			for (; it != it_end; ++it)
				++count;
			Assert::IsTrue(count == vec.Size());
		}
	};
}