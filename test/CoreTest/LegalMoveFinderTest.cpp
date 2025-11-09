#include "gtest/gtest.h"
#include "core/LegalMoveFinder.h"
#include "core/Board.h"
#include "core/Piece.h"
#include "core/Types.h"
#include <vector>
#include <algorithm>

using namespace shoryu::core;

TEST(LegalMoveFinderTest, EmptySquare)
{
	Board board;
	Position pos(5, 5);

	std::vector<Position> moves = findLegalMoves(board, pos);
	EXPECT_TRUE(moves.empty());
}

// 先手・歩兵
TEST(LegalMoveFinderTest, Sente_Fu)
{
	Board board;
	Piece piece(PieceType::Fu, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 1);
	EXPECT_EQ(moves[0], Position(5, 4));
}

// 先手・香車
TEST(LegalMoveFinderTest, Sente_Kyo)
{
	Board board;
	Piece piece(PieceType::Kyo, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 4);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
}

// 先手・桂馬
TEST(LegalMoveFinderTest, Sente_Kei)
{
	Board board;
	Piece piece(PieceType::Kei, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 2);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 3)), moves.end());
}

// 先手・銀将
TEST(LegalMoveFinderTest, Sente_Gin)
{
	Board board;
	Piece piece(PieceType::Gin, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 5);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
}

// 先手・金将
TEST(LegalMoveFinderTest, Sente_Kin)
{
	Board board;
	Piece piece(PieceType::Kin, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 6);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
}

// 先手・角行
TEST(LegalMoveFinderTest, Sente_Kaku)
{
	Board board;
	Piece piece(PieceType::Kaku, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 16);
	// 右上方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 1)), moves.end());
	// 左上方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
	// 右下方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 7)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 8)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
	// 左下方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
}

// 先手・飛車
TEST(LegalMoveFinderTest, Sente_Hisha)
{
	Board board;
	Piece piece(PieceType::Hisha, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 16);
	// 上方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
	// 下方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 9)), moves.end());
	// 左方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
	// 右方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 5)), moves.end());
}

// 先手・王将
TEST(LegalMoveFinderTest, Sente_Ou)
{
	Board board;
	Piece piece(PieceType::Ou, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 8);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
}

// 先手・玉将
TEST(LegalMoveFinderTest, Sente_Gyoku)
{
	Board board;
	Piece piece(PieceType::Gyoku, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 8);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
}

// 先手・と金
TEST(LegalMoveFinderTest, Sente_Tokin)
{
	Board board;
	Piece piece(PieceType::Tokin, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 6);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
}

// 先手・成香
TEST(LegalMoveFinderTest, Sente_NariKyo)
{
	Board board;
	Piece piece(PieceType::NariKyo, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 6);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
}

// 先手・成桂
TEST(LegalMoveFinderTest, Sente_NariKei)
{
	Board board;
	Piece piece(PieceType::NariKei, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 6);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
}

// 先手・成銀
TEST(LegalMoveFinderTest, Sente_NariGin)
{
	Board board;
	Piece piece(PieceType::NariGin, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 6);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
}

// 先手・馬
TEST(LegalMoveFinderTest, Sente_Uma)
{
	Board board;
	Piece piece(PieceType::Uma, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 20);
	// 右上方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 1)), moves.end());
	// 左上方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
	// 右下方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 7)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 8)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
	// 左下方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
	// 縦横１マス
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
}

// 先手・竜
TEST(LegalMoveFinderTest, Sente_Ryu)
{
	Board board;
	Piece piece(PieceType::Ryu, PlayerSide::Sente);
	board.setPiece(Position(5, 5), piece);
	
	std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
	ASSERT_EQ(moves.size(), 20);
	// 上方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
	// 下方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 9)), moves.end());
	// 左方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
	// 右方向
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 5)), moves.end());
	// 斜め１マス
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
}