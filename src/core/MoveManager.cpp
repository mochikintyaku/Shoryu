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
		// 1. 移動元(from)から駒を削除、または持ち駒から減らす
		if (move.from)
		{
			// 盤面からの移動
			board_.setSquare(*move.from, std::nullopt);
		}
		else
		{
			// 持ち駒を打つ場合、持ち駒から減らす
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

		// 2. 移動先(to)に駒を配置
		board_.setSquare(move.to, move.movedPieceAfter);

		// 3. 駒を取っていれば、持ち駒に追加
		if (move.capturedPiece)
		{
			PlayerSide owner = move.movedPieceAfter.owner();
			// 取った駒は成っていても元に戻す
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

		// 1. 持ち駒を削除(駒を取っていた場合)
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

		// 2. 移動先(to)の駒を削除(駒を取っていれば、そこに戻す)
		if (move.capturedPiece)
		{
			board_.setSquare(move.to, move.capturedPiece);
		}
		else
		{
			board_.setSquare(move.to, std::nullopt);
		}

		// 3. 移動元(from)に駒を配置、または持ち駒に戻す
		if (move.from)
		{
			board_.setSquare(*move.from, move.movedPieceBefore);
		}
		else
		{
			// 持ち駒を打っていた場合、持ち駒に戻す
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
