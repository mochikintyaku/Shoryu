#include "pch.h"
#include "CppUnitTest.h"
#include "Types.h"
#include "Square.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShoryuCoreTest
{
	TEST_CLASS(ShoryuCoreTest)
	{
	public:

		TEST_METHOD(test_isInside)
		{
			using namespace shoryu::core;
			Position pos(4, 4);
			Assert::IsTrue(isInside(pos));
		}
	};
}
