#include "stdafx.h"
#include "CppUnitTest.h"
#include "Maths/Vec2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Vec2)
	{
	public:

		TEST_METHOD(DefaultInitialize)
		{
			Assert::IsTrue(DefaultVec.x == 0);
			Assert::IsTrue(DefaultVec.y == 0);
		}

		TEST_METHOD(Initialize)
		{
			Assert::IsTrue(Math::Vec2(0.0f) == Math::Vec2(0.0f));
		}

		TEST_METHOD(InitializeOverload)
		{
			Assert::IsTrue(Math::Vec2(3.0f) == Math::Vec2(3.0f, 3.0f));
		}

		TEST_METHOD(Copy)
		{
			Assert::IsTrue(Math::Vec2(VecTest) == Math::Vec2(12.5f, 7.3f));
		}

		TEST_METHOD(NotEqualOperator)
		{
			Assert::IsTrue(VecTest != Math::Vec2(7.0f, 8.2f));
		}

		TEST_METHOD(EqualOperator)
		{
			Assert::IsTrue(Math::Vec2(VecTest) == Math::Vec2(12.5f, 7.3f));
		}

		TEST_METHOD(PlusOperator)
		{
			Assert::IsTrue((VecTest + VecTest2) == Math::Vec2(18.0f, 9.1f));
		}

		TEST_METHOD(PlusEqualOperator)
		{
			Math::Vec2 BaseVec = Math::Vec2(1.2f, 3.3f);
			BaseVec += VecTest;
			Assert::IsTrue(BaseVec == Math::Vec2(13.7f, 10.6f));
		}

		TEST_METHOD(MinusOperator)
		{
			Assert::IsTrue((VecTest - VecTest2) == Math::Vec2(7.0f, 5.5f));
		}

		TEST_METHOD(MinusEqualOperator)
		{
			Math::Vec2 BaseVec = Math::Vec2(1.2f, 3.3f);
			BaseVec -= VecTest;
			Assert::IsTrue(BaseVec == Math::Vec2(-11.3f, -4.0f));
		}

		TEST_METHOD(BoolOperatorEqual)
		{
			Math::Vec2 VecBool(1);
			bool boolean;
			if (VecBool)
				boolean = true;
			else
				boolean = false;

			Assert::IsTrue(boolean);
		}

		TEST_METHOD(BoolOperatorNotEqual)
		{
			Math::Vec2 VecBool(0);
			bool boolean;
			if (VecBool)
				boolean = true;
			else
				boolean = false;

			Assert::IsFalse(boolean);
		}

		TEST_METHOD(Length)
		{
			double length = VecTest.Length();
			Assert::AreEqual(length, 14.475496537252186, 0.001);
		}

		TEST_METHOD(Normalize)
		{
			Math::Vec2 normalizedVec = VecTest.Normalized();
			double x = normalizedVec.x;
			double y = normalizedVec.y;
			Assert::AreEqual(x, 0.863528, 0.001);
			Assert::AreEqual(y, 0.5043, 0.001);
		}

		TEST_METHOD(DotProduct)
		{
			double result = VecTest.Dot(VecTest2);
			Assert::AreEqual(result, 81.89, 0.01);
		}

	private:
		Math::Vec2 DefaultVec = Math::Vec2();
		Math::Vec2 VecTest = Math::Vec2(12.5f, 7.3f);
		Math::Vec2 VecTest2 = Math::Vec2(5.5f, 1.8f);
	};
}