#include "core/LegalMoveFinder.h"
#include "vector"
#include "core/MoveTable.h"
#include "core/Board.h"
#include "core/Square.h"
#include "core/PieceTraits.h"

namespace shoryu::core
{
	std::vector<Position> findLegalMoves(const Board& board, Position from)
	{
		std::vector<Position> legalMoves;

		if (isInside(from) == false)
			return legalMoves;

		// 指定位置に駒がない場合、空のリストを返す
		if (auto opt = board.getPiece(from); !opt)
			return legalMoves; 

		const Piece fromPiece = *board.getPiece(from);
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
			if (isInside(newPos) == false)
				continue;

			if (auto opt = board.getPiece(newPos); opt)
				if (isAlly(fromPiece, *opt))
					continue;
			
			legalMoves.push_back(newPos);
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
					searchPos.suji_ += dx;
					searchPos.dan_ += dy;
					continue;
				}
				
				const auto& destPiece = *pieceOpt;
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
