#include "core/MoveManager.h"
#include "core/Board.h"
#include "core/Hand.h"
#include "core/PieceTraits.h"

namespace shoryu::core
{
	MoveManager::MoveManager(Board& board, Hand& sente, Hand& gote)
		:stack_(), board_(board), senteHand_(sente), goteHand_(gote)
	{ }

	MoveManager::~MoveManager()
	{ }

	void MoveManager::execute(Move move)
	{
		// 1. 移動元（from）から駒を削除、または持ち駒を減らす
		if (move.from)
		{
			// 盤面から駒を移動
			board_.setPiece(*move.from, std::nullopt);
		}
		else
		{
			// 持ち駒を打つ場合、持ち駒を減らす
			PlayerSide owner = move.movedPieceAfter.owner();
			PieceType pieceType = move.movedPieceAfter.pieceType();
			if (owner == PlayerSide::Sente)
			{
				senteHand_.removePiece(pieceType);
			}
			else
			{
				goteHand_.removePiece(pieceType);
			}
		}

		// 2. 移動先（to）に駒を配置
		board_.setPiece(move.to, move.movedPieceAfter);

		// 3. 取った駒があれば、持ち駒に追加
		if (move.capturedPiece)
		{
			PlayerSide owner = move.movedPieceAfter.owner();
			// 取った駒は成っていたら元に戻す
			PieceType capturedType = demoteType(move.capturedPiece->pieceType());
			if (owner == PlayerSide::Sente)
			{
				senteHand_.addPiece(capturedType);
			}
			else
			{
				goteHand_.addPiece(capturedType);
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

		// 1. 持ち駒から駒を削除（駒を取っていた場合）
		if (move.capturedPiece)
		{
			PlayerSide owner = move.movedPieceAfter.owner();
			PieceType capturedType = demoteType(move.capturedPiece->pieceType());
			if (owner == PlayerSide::Sente)
			{
				senteHand_.removePiece(capturedType);
			}
			else
			{
				goteHand_.removePiece(capturedType);
			}
		}

		// 2. 移動先(to)の駒を削除（駒を取っていれば、そこに戻す）
		if (move.capturedPiece)
		{
			board_.setPiece(move.to, move.capturedPiece);
		}
		else
		{
			board_.setPiece(move.to, std::nullopt);
		}

		// 3. 移動元(from)に駒を配置、または持ち駒に戻す
		if (move.from)
		{
			board_.setPiece(*move.from, move.movedPieceBefore);
		}
		else
		{
			// 持ち駒を打った手を戻す場合、持ち駒に戻す
			PlayerSide owner = move.movedPieceAfter.owner();
			PieceType pieceType = move.movedPieceAfter.pieceType();
			if (owner == PlayerSide::Sente)
			{
				senteHand_.addPiece(pieceType);
			}
			else
			{
				goteHand_.addPiece(pieceType);
			}
		}
	}

	size_t MoveManager::getMoveCount() const
	{
		return stack_.size();
	}
}
