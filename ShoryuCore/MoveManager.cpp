#include "MoveManager.h"
#include "Board.h"

namespace shoryu::core
{
	MoveManager::MoveManager(Board& board)
		:stack_(), board_(board)
	{ }

	void MoveManager::execute(Move move)
	{
		// 1. 移動元（from）から駒を削除
		// 2. 移動先（to）に駒を配置
		// 3. 取った駒があれば、持ち駒に追加
		if (move.from.has_value())
		{
			board_.setPiece(move.from.value(), std::nullopt);
		}
		board_.setPiece(move.to, move.movedPieceAfter);
		if (move.capturedPiece.has_value())
		{
			// 持ち駒に追加する処理をここに書く
			// 例えば、PlayerクラスのaddCapturedPieceメソッドを呼び出すなど
		}

		stack_.push(move);
	}

	void MoveManager::undoLast()
	{
		if (stack_.empty())
			return;

		Move move = stack_.top();
		stack_.pop();

		// 1. 取った駒を持ち駒から削除（もし取った駒があれば）
		// 2. 移動先(to)の駒を削除（駒を取っていれば、取った駒に戻す）
		// 3. 移動元(from)のに駒を配置
		if (move.capturedPiece.has_value())
		{
			// 持ち駒から削除する処理をここに書く
			// 例えば、PlayerクラスのremoveCapturedPieceメソッドを呼び出すなど
		}
		if (move.capturedPiece.has_value())
		{
			board_.setPiece(move.to, move.capturedPiece);
		}
		else
		{
			board_.setPiece(move.to, std::nullopt);
		}
		if (move.from.has_value())
		{
			board_.setPiece(move.from.value(), move.movedPieceBefore);
		}
	}
}
