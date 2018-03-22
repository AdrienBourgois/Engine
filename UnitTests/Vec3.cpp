#include "stdafx.h"
#include "CppUnitTest.h"
#include "Maths/Vec3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Vec3)
	{
	public:

		TEST_CLASS_INITIALIZE(Initialize)
		{
			Logger::WriteMessage("Start Testing Math::Vec3 class");
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			Logger::WriteMessage("Finalize Testing Math::Vec3 class");
		}

		TEST_METHOD(DefaultInitialize)
		{
			Assert::IsTrue(defaultVec.x == 0);
			Assert::IsTrue(defaultVec.y == 0);
		}

		TEST_METHOD(InitializeOverload)
		{
			Assert::IsTrue(Math::Vec3(3.0f) == Math::Vec3(3.0f, 3.0f, 3.0f));
		}

		TEST_METHOD(Copy)
		{
			Assert::IsTrue(Math::Vec3(vecTest) == Math::Vec3(12.5f, 7.3f, 6.8f));
		}

		TEST_METHOD(NotEqualOperator)
		{
			Assert::IsTrue(vecTest != Math::Vec3(7.0f, 8.2f, 1.5f));
		}

		TEST_METHOD(EqualOperator)
		{
			Assert::IsTrue(Math::Vec3(vecTest) == Math::Vec3(12.5f, 7.3f, 6.8f));
		}

		TEST_METHOD(PlusOperator)
		{
			Assert::IsTrue((vecTest + vecTest2) == Math::Vec3(18.0f, 9.1f, 8.3f));
		}

		TEST_METHOD(PlusEqualOperator)
		{
			Math::Vec3 base_vec = Math::Vec3(vecTest2);
			base_vec += vecTest;
			Assert::IsTrue(base_vec == Math::Vec3(18.0f, 9.1f, 8.3f));
		}

		TEST_METHOD(MinusOperator)
		{
			Assert::IsTrue((vecTest - vecTest2) == Math::Vec3(7.0f, 5.5f, 5.3f));
		}

		TEST_METHOD(MinusEqualOperator)
		{
			Math::Vec3 base_vec = Math::Vec3(vecTest);
			base_vec -= vecTest2;
			Assert::IsTrue(base_vec == Math::Vec3(7.0f, 5.5f, 5.3f));
		}

		TEST_METHOD(BoolOperatorEqual)
		{
			const Math::Vec3 vec_bool(1);
			const bool boolean = static_cast<bool>(vec_bool);
			Assert::IsTrue(boolean);
		}

		TEST_METHOD(BoolOperatorNotEqual)
		{
			const Math::Vec3 vec_bool(0);
			const bool boolean = static_cast<bool>(vec_bool);
			Assert::IsFalse(boolean);
		}

		TEST_METHOD(Length)
		{
			const double length = vecTest.Length();
			Assert::AreEqual(length, 15.9931, 0.001);
		}

		TEST_METHOD(Normalize)
		{
			const Math::Vec3 normalized_vec = vecTest.Normalized();
			const double x = normalized_vec.x;
			const double y = normalized_vec.y;
			const double z = normalized_vec.z;
			Assert::AreEqual(x, 0.781586, 0.001);
			Assert::AreEqual(y, 0.456446, 0.001);
			Assert::AreEqual(z, 0.425183, 0.001);
		}

		TEST_METHOD(DotProduct)
		{
			const double result = vecTest.Dot(vecTest2);
			Assert::AreEqual(result, 92.09, 0.01);
		}

	private:
		Math::Vec3 defaultVec = Math::Vec3();
		Math::Vec3 vecTest = Math::Vec3(12.5f, 7.3f, 6.8f);
		Math::Vec3 vecTest2 = Math::Vec3(5.5f, 1.8f, 1.5f);
	};
}