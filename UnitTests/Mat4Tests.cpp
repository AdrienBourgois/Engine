#include "stdafx.h"
#include "CppUnitTest.h"
#include "Maths/Mat4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Mat4Tests)
	{
	public:

		TEST_METHOD(DefaultInitialize)
		{
			Math::Mat4 default_mat;
			Assert::IsTrue(default_mat[0] == 0);
			Assert::IsTrue(default_mat[1] == 0);
			Assert::IsTrue(default_mat[2] == 0);
			Assert::IsTrue(default_mat[3] == 0);
			Assert::IsTrue(default_mat[4] == 0);
			Assert::IsTrue(default_mat[5] == 0);
			Assert::IsTrue(default_mat[6] == 0);
			Assert::IsTrue(default_mat[7] == 0);
			Assert::IsTrue(default_mat[8] == 0);
			Assert::IsTrue(default_mat[9] == 0);
			Assert::IsTrue(default_mat[10] == 0);
			Assert::IsTrue(default_mat[11] == 0);
			Assert::IsTrue(default_mat[12] == 0);
			Assert::IsTrue(default_mat[13] == 0);
			Assert::IsTrue(default_mat[14] == 0);
			Assert::IsTrue(default_mat[15] == 0);
		}

		TEST_METHOD(EqualOperator)
		{
			Assert::IsTrue(Math::Mat4::Identity == Math::Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
		}

		TEST_METHOD(MultiplyOperator)
		{
			Math::Mat4 mat1(21, 22, 23, 24,
				            25, 26, 27, 28,
				            29, 30, 31, 32,
				            33, 34, 35, 36);

			Math::Mat4 mat2(5,  6,  7,  8,
						    9,  10, 11, 12,
						    13, 14, 15, 16,
						    17, 18, 19, 20);

			Math::Mat4 mat_result(1010, 1100, 1190, 1280,
								 1186, 1292, 1398, 1504,
							 	 1362, 1484, 1606, 1728,
							 	 1538, 1676, 1814, 1952);

			Assert::IsTrue(mat1 * mat2 == mat_result);
		}

		TEST_METHOD(Inverse)
		{
			Math::Mat4 mat(1, 5, 9, 3,
						   5, 7, 8, 4,
						   2, 6, 8, 0,
						   2, 5, 3, 6);

			Math::Mat4 inverse(-0.1f , 0.375f, -0.1875f, -0.2f,
						       -0.26f, -0.225f, 0.4125f, 0.28f,
					           0.22f , 0.075f, -0.1375f, -0.16f,
						       0.14f , 0.025f, -0.2125f, 0.08f);

			Math::Mat4 result = mat.GetInverse();

			for (int i = 0; i < 16; ++i)
			{
				Assert::AreEqual(result[i], inverse[i], 0.00001f);
			}
		}

		TEST_METHOD(Transpose)
		{
			Math::Mat4 mat(21, 22, 23, 24,
				            25, 26, 27, 28,
				            29, 30, 31, 32,
				            33, 34, 35, 36);

			Assert::IsTrue(Math::Mat4(21, 25, 29, 33,
								      22, 26, 30, 34,
								      23, 27, 31, 35,
								      24, 28, 32, 36) == mat.GetTranspose());
		}
	};
}