#include "gtest/gtest.h"
#include "core/Piece.h"
#include "core/Board.h"
#include "core/Types.h"

using namespace shoryu::core;

TEST(PieceTest, DefaultConstructor) {
    Piece piece;
    EXPECT_NO_THROW(piece);
}

TEST(BoardTest, Initialization) {
    Board board;
    Position pos(1, 1);
    auto piece = board.getPiece(pos);
    EXPECT_FALSE(piece.has_value()); // ‰Šúó‘Ô‚Í‹ó
}