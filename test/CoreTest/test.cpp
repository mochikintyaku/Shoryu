#include "gtest/gtest.h"
#include "core/Piece.h"
#include "core/Board.h"
#include "core/Types.h"

using namespace shoryu::core;

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}