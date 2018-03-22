#include "stdafx.h"
#include "CppUnitTest.h"
#include "Maths/Vec2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Vec2)
	{
	public:

		TEST_CLASS_INITIALIZE(Initialize)
		{
			Logger::WriteMessage("Start Testing Math::Vec2 class");
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			Logger::WriteMessage("Finalize Testing Math::Vec2 class");
		}

		TEST_METHOD(DefaultInitialize)
		{
			Assert::IsTrue(defaultVec.x == 0);
			Assert::IsTrue(defaultVec.y == 0);
		}

		TEST_METHOD(InitializeOverload)
		{
			Assert::IsTrue(Math::Vec2(3.0f) == Math::Vec2(3.0f, 3.0f));
		}

		TEST_METHOD(Copy)
		{
			Assert::IsTrue(Math::Vec2(vecTest) == Math::Vec2(12.5f, 7.3f));
		}

		TEST_METHOD(NotEqualOperator)
		{
			Assert::IsTrue(vecTest != Math::Vec2(7.0f, 8.2f));
		}

		TEST_METHOD(EqualOperator)
		{
			Assert::IsTrue(Math::Vec2(vecTest) == Math::Vec2(12.5f, 7.3f));
		}

		TEST_METHOD(PlusOperator)
		{
			Assert::IsTrue((vecTest + vecTest2) == Math::Vec2(18.0f, 9.1f));
		}

		TEST_METHOD(PlusEqualOperator)
		{
			Math::Vec2 BaseVec = Math::Vec2(1.2f, 3.3f);
			BaseVec += vecTest;
			Assert::IsTrue(BaseVec == Math::Vec2(13.7f, 10.6f));
		}

		TEST_METHOD(MinusOperator)
		{
			Assert::IsTrue((vecTest - vecTest2) == Math::Vec2(7.0f, 5.5f));
		}

		TEST_METHOD(MinusEqualOperator)
		{
			Math::Vec2 base_vec = Math::Vec2(1.2f, 3.3f);
			base_vec -= vecTest;
			Assert::IsTrue(base_vec == Math::Vec2(-11.3f, -4.0f));
		}

		TEST_METHOD(BoolOperatorEqual)
		{
			const Math::Vec2 vec_bool(1);
			const bool boolean = static_cast<bool>(vec_bool);
			Assert::IsTrue(boolean);
		}

		TEST_METHOD(BoolOperatorNotEqual)
		{
			const Math::Vec2 vec_bool(0);
			const bool boolean = static_cast<bool>(vec_bool);
			Assert::IsFalse(boolean);
		}

		TEST_METHOD(Length)
		{
			const double length = vecTest.Length();
			Assert::AreEqual(length, 14.475496537252186, 0.001);
		}

		TEST_METHOD(Normalize)
		{
			const Math::Vec2 normalized_vec = vecTest.Normalized();
			const double x = normalized_vec.x;
			const double y = normalized_vec.y;
			Assert::AreEqual(x, 0.863528, 0.001);
			Assert::AreEqual(y, 0.5043, 0.001);
		}

		TEST_METHOD(DotProduct)
		{
			const double result = vecTest.Dot(vecTest2);
			Assert::AreEqual(result, 81.89, 0.01);
		}

	private:
		Math::Vec2 defaultVec = Math::Vec2();
		Math::Vec2 vecTest = Math::Vec2(12.5f, 7.3f);
		Math::Vec2 vecTest2 = Math::Vec2(5.5f, 1.8f);
	};
}