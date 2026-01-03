#include "gtest/gtest.h"
#include "core/MoveManager.h"
#include "core/Board.h"
#include "core/Hand.h"

using namespace shoryu::core;

namespace MoveManagerTest
{
	TEST(BasicTest, ExecuteAndUndoMove)
	{
		Board board;
		Hand senteHand;
		Hand goteHand;
		MoveManager moveManager(board, senteHand, goteHand);
		// 初期配置: 先手の歩(5,7)に配置
		Position from(5, 7);
		Piece fu(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(from, fu);
		// (5,7)から(5,6)へ移動する手を実行
		Position to(5, 6);
		Piece movedPieceAfter(PieceType::Fu, PlayerSide::Sente);
		Move move(
			from,
			to,
			std::nullopt,
			fu,
			movedPieceAfter
		);
		moveManager.execute(move);
		// 移動後の状態を確認
		EXPECT_EQ(board.getSquare(from), std::nullopt); // 移動元は空
		auto pieceAtTo = board.getSquare(to);
		ASSERT_TRUE(pieceAtTo.has_value());
		EXPECT_EQ(pieceAtTo->pieceType(), PieceType::Fu); // 移動先に歩がある
		EXPECT_EQ(pieceAtTo->owner(), PlayerSide::Sente);
		// 手を戻す
		moveManager.undoLast();
		// 戻した後の状態を確認
		auto pieceAtFromAfterUndo = board.getSquare(from);
		ASSERT_TRUE(pieceAtFromAfterUndo.has_value());
		EXPECT_EQ(pieceAtFromAfterUndo->pieceType(), PieceType::Fu); // 移動元に歩が戻る
		EXPECT_EQ(pieceAtFromAfterUndo->owner(), PlayerSide::Sente);
		EXPECT_EQ(board.getSquare(to), std::nullopt); // 移動先は空に戻る
	}
} // namespace MoveManagerTest