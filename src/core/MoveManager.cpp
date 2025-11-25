#include "core/MoveManager.h"
#include "core/Board.h"
#include "core/Hand.h"

namespace shoryu::core
{
	MoveManager::MoveManager(Board& board, Hand& sente, Hand& gote)
		:stack_(), board_(board), senteHand_(sente), goteHand_(gote)
	{ }

	MoveManager::~MoveManager()
	{ }

	void MoveManager::execute(Move move)
	{
		// 1. 移動元（from）から駒を削除
		// 2. 移動先（to）に駒を配置
		// 3. 取った駒があれば、持ち駒に追加
		if (move.from)
		{
			board_.setPiece(*move.from, std::nullopt);
		}
		board_.setPiece(move.to, move.movedPieceAfter);
		if (move.capturedPiece)
		{
			PlayerSide owner = move.movedPieceAfter.owner();
			if (owner == PlayerSide::Sente)
			{
				senteHand_.addPiece(move.capturedPiece->pieceType());
			}
			else
			{
				goteHand_.addPiece(move.capturedPiece->pieceType());
			}
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
		if (move.capturedPiece)
		{
			PlayerSide owner = move.movedPieceAfter.owner();
			if (owner == PlayerSide::Sente)
			{
				senteHand_.removePiece(move.capturedPiece->pieceType());
			}
			else
			{
				goteHand_.removePiece(move.capturedPiece->pieceType());
			}
		}
		if (move.capturedPiece)
		{
			board_.setPiece(move.to, move.capturedPiece);
		}
		else
		{
			board_.setPiece(move.to, std::nullopt);
		}
		if (move.from)
		{
			board_.setPiece(*move.from, move.movedPieceBefore);
		}
	}
}
