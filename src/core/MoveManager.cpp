#include "core/MoveManager.h"
#include "core/Board.h"
#include "core/Hand.h"
#include "core/PieceTraits.h"

namespace shoryu::core
{
	MoveManager::MoveManager(Board& board, Hand& hand)
		:stack_(), board_(board),hand_(hand)
	{ }

	MoveManager::~MoveManager()
	{ }

	void MoveManager::clear()
	{
		while (!stack_.empty())
		{
			stack_.pop();
		}
	}

	void MoveManager::execute(Move move)
	{
		// 1. 移動元(from)を削除、または持ち駒から減らす
		if (move.from)
		{
			// 盤上の移動
			board_.setPiece(*move.from, PieceCode::Empty);
		}
		else
		{
			// 駒を打つ場合、持ち駒から減らす
			hand_.remove(move.movedPieceAfter);
		}

		// 2. 移動先(to)に駒を配置
		board_.setPiece(move.to, move.movedPieceAfter);

		// 3. 駒を取っている場合、持ち駒に追加
		if (!isEmpty(move.capturedPiece))
		{
			// 取った駒は相手の駒なので、所有者を反転して持ち駒化
			PieceCode capturedPcAsHand = flipOwner(move.capturedPiece);
			hand_.add(capturedPcAsHand);
		}

		stack_.push(move);
	}

	void MoveManager::undoLast()
	{
		if (stack_.empty())
			return;

		Move move = stack_.top();
		stack_.pop();

		// 1. 持ち駒を削除(駒を取っていた場合)
		if (!isEmpty(move.capturedPiece))
		{
			// 取った駒は相手の駒なので、所有者を反転して持ち駒から削除
			PieceCode capturedPcAsHand = flipOwner(move.capturedPiece);
			hand_.remove(capturedPcAsHand);
		}

		// 2. 移動先(to)の駒を削除(駒を取っていれば、元に戻す)
		if (!isEmpty(move.capturedPiece))
		{
			board_.setPiece(move.to, move.capturedPiece);
		}
		else
		{
			board_.setPiece(move.to, PieceCode::Empty);
		}

		// 3. 移動元(from)に駒を配置、または持ち駒に戻す
		if (move.from)
		{
			board_.setPiece(*move.from, move.movedPieceBefore);
		}
		else
		{
			// 駒を打っていた場合、持ち駒に戻す
			hand_.add(move.movedPieceAfter);
		}
	}

	size_t MoveManager::getMoveCount() const
	{
		return stack_.size();
	}
}
