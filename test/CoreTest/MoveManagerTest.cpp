#include "gtest/gtest.h"
#include "core/MoveManager.h"
#include "core/Board.h"
#include "core/Hand.h"
#include "core/PieceTraits.h"

using namespace shoryu::core;

namespace MoveManagerTest
{
	TEST(BasicTest, ExecuteAndUndoMove)
	{
		Board board;
		Hand hand;
		MoveManager moveManager(board, hand);
		// 初期配置: 先手の歩(5,7)に配置
		Position from(5, 7);
		board.setPiece(from, PieceCode::SenteFu);
		// (5,7)から(5,6)へ移動する手を実行
		Position to(5, 6);
		Move move(
			from,
			to,
			PieceCode::Empty,
			PieceCode::SenteFu,
			PieceCode::SenteFu
		);
		moveManager.execute(move);
		// 移動後の状態を確認
		EXPECT_EQ(board.getPiece(from), PieceCode::Empty); // 移動元は空
		const PieceCode pieceAtTo = board.getPiece(to);
		EXPECT_TRUE(!isEmpty(pieceAtTo));
		EXPECT_EQ(pieceAtTo, PieceCode::SenteFu); // 移動先に歩がある
		// 手を戻す
		moveManager.undoLast();
		// 戻した後の状態を確認
		const PieceCode pieceAtFromAfterUndo = board.getPiece(from);
		EXPECT_TRUE(!isEmpty(pieceAtFromAfterUndo));
		EXPECT_EQ(pieceAtFromAfterUndo, PieceCode::SenteFu); // 移動元に歩が戻る
		EXPECT_TRUE(isEmpty(board.getPiece(to))); // 移動先は空に戻る
	}
} // namespace MoveManagerTest