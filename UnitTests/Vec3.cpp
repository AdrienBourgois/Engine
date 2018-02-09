#include "stdafx.h"
#include "CppUnitTest.h"
#include "Maths/Vec3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Vec3)
	{
	public:

		TEST_METHOD(DefaultInitialize)
		{
			Assert::IsTrue(DefaultVec.x == 0);
			Assert::IsTrue(DefaultVec.y == 0);
		}

		TEST_METHOD(Initialize)
		{
			Assert::IsTrue(Math::Vec3(0.0f) == Math::Vec3(0.0f));
		}

		TEST_METHOD(InitializeOverload)
		{
			Assert::IsTrue(Math::Vec3(3.0f) == Math::Vec3(3.0f, 3.0f, 3.0f));
		}

		TEST_METHOD(Copy)
		{
			Assert::IsTrue(Math::Vec3(VecTest) == Math::Vec3(12.5f, 7.3f, 6.8f));
		}

		TEST_METHOD(NotEqualOperator)
		{
			Assert::IsTrue(VecTest != Math::Vec3(7.0f, 8.2f, 1.5f));
		}

		TEST_METHOD(EqualOperator)
		{
			Assert::IsTrue(Math::Vec3(VecTest) == Math::Vec3(12.5f, 7.3f, 6.8f));
		}

		TEST_METHOD(PlusOperator)
		{
			Assert::IsTrue((VecTest + VecTest2) == Math::Vec3(18.0f, 9.1f, 8.3f));
		}

		TEST_METHOD(PlusEqualOperator)
		{
			Math::Vec3 BaseVec = Math::Vec3(VecTest2);
			BaseVec += VecTest;
			Assert::IsTrue(BaseVec == Math::Vec3(18.0f, 9.1f, 8.3f));
		}

		TEST_METHOD(MinusOperator)
		{
			Assert::IsTrue((VecTest - VecTest2) == Math::Vec3(7.0f, 5.5f, 5.3f));
		}

		TEST_METHOD(MinusEqualOperator)
		{
			Math::Vec3 BaseVec = Math::Vec3(VecTest);
			BaseVec -= VecTest2;
			Assert::IsTrue(BaseVec == Math::Vec3(7.0f, 5.5f, 5.3f));
		}

		TEST_METHOD(BoolOperatorEqual)
		{
			Math::Vec3 VecBool(1);
			bool boolean = false;
			if (VecBool)
				boolean = true;
			else
				boolean = false;

			Assert::IsTrue(boolean);
		}

		TEST_METHOD(BoolOperatorNotEqual)
		{
			Math::Vec3 VecBool(0);
			bool boolean = false;
			if (VecBool)
				boolean = true;
			else
				boolean = false;

			Assert::IsFalse(boolean);
		}

		TEST_METHOD(Length)
		{
			double length = VecTest.Length();
			Assert::AreEqual(length, 15.9931, 0.001);
		}

		TEST_METHOD(Normalize)
		{
			Math::Vec3 normalizedVec = VecTest.Normalized();
			double x = normalizedVec.x;
			double y = normalizedVec.y;
			double z = normalizedVec.z;
			Assert::AreEqual(x, 0.781586, 0.001);
			Assert::AreEqual(y, 0.456446, 0.001);
			Assert::AreEqual(z, 0.425183, 0.001);
		}

		TEST_METHOD(DotProduct)
		{
			double result = VecTest.Dot(VecTest2);
			Assert::AreEqual(result, 92.09, 0.01);
		}

	private:
		Math::Vec3 DefaultVec = Math::Vec3();
		Math::Vec3 VecTest = Math::Vec3(12.5f, 7.3f, 6.8f);
		Math::Vec3 VecTest2 = Math::Vec3(5.5f, 1.8f, 1.5f);
	};
}