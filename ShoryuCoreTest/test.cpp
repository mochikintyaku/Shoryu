#include "pch.h"
#include "Types.h"
#include "Square.h"

TEST(NORMAL, IsInsideTest) {
	using namespace shoryu::core;
	Position pos1{ 5, 5 };
	EXPECT_TRUE(isInside(pos1));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}