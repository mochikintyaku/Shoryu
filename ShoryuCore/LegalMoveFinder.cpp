#include "LegalMoveFinder.h"
#include "vector"
#include "MoveTable.h"
#include "Board.h"
#include "Square.h"
#include "PieceTraits.h"

namespace shoryu::core
{
	std::vector<Position> findLegalMoves(const Board& board, Position from)
	{
		std::vector<Position> legalMoves;

		if (isInside(from) == false)
			return legalMoves;

		const auto pieceOpt = board.getPiece(from);
		if (pieceOpt.has_value() == false)
			return legalMoves; // 指定位置に駒がない場合、空のリストを返す

		const auto& fromPiece = pieceOpt.value();
		const auto it = moveTable.find(fromPiece.pieceType());
		if (it == moveTable.end())
			return legalMoves;

		const MoveSpec& moveSpec = it->second;
		int sideFactor = ((fromPiece.owner()) == PlayerSide::Gote) ? -1 : 1;

		// ステップ移動の処理
		for (const auto& step : moveSpec.stepMoves)
		{
			int newSuji = from.suji_ + step.dx * sideFactor;
			int newDan = from.dan_ + step.dy * sideFactor;
			Position newPos(newSuji, newDan);
			if (isInside(newPos))
			{
				legalMoves.push_back(newPos);
			}
		}

		// スライド移動の処理
		for (const auto& slide : moveSpec.slideMoves)
		{
			int dx = slide.dx * sideFactor;
			int dy = slide.dy * sideFactor;

			Position searchPos(from.suji_ + dx, from.dan_ + dy);
			while (isInside(searchPos))
			{
				Position newPos = searchPos;
				const auto pieceOpt = board.getPiece(newPos);
				if (pieceOpt == std::nullopt)
				{
					legalMoves.push_back(newPos);
					searchPos.suji_ + dx;
					searchPos.dan_ + dy;
					continue;
				}
				
				const auto& destPiece = pieceOpt.value();
				if (isAlly(destPiece, fromPiece))
				{
					break;
				}
				else
				{
					legalMoves.push_back(newPos);
					break;
				}
			}
		}

		return legalMoves;
	}
}
