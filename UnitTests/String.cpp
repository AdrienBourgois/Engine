#include "stdafx.h"
#include "CppUnitTest.h"
#include "Core/CoreType/String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(String)
	{
	public:

		TEST_METHOD(EmptyString)
		{
			Assert::IsTrue(S("").IsEmpty());
			Assert::IsTrue(emptyString.IsEmpty());
			Assert::IsFalse(string1.IsEmpty());
		}

		TEST_METHOD(NullString)
		{
			Assert::IsFalse(S("").IsNull());
			Assert::IsTrue(emptyString.IsNull());
			Assert::IsFalse(string1.IsNull());
		}

		TEST_METHOD(Equal)
		{
			Assert::IsTrue(string1 == S("String"));
			Assert::IsFalse(string1 == S("String "));
		}

		TEST_METHOD(Length)
		{
			Assert::IsTrue(string1.Length() == 6);
			Assert::IsTrue(string1.SafeLength() == 7);
		}

		TEST_METHOD(Append)
		{
			Core::CoreType::String result_string = string1;
			result_string.Append(string2);
			Assert::IsTrue(result_string == S("String to test"));
		}

		TEST_METHOD(Contain)
		{
			Assert::IsTrue(string1.Contain(string3));
		}

		TEST_METHOD(First)
		{
			Assert::IsTrue(string1.First(string3) == 3);
		}

	private:
		Core::CoreType::String emptyString;
		Core::CoreType::String string1 = S("String");
		Core::CoreType::String string2 = S(" to test");
		Core::CoreType::String string3 = S("ing");
	};
}