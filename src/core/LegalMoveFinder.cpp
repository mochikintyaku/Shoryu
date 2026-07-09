#include "core/LegalMoveFinder.h"
#include "vector"
#include "core/MoveTable.h"
#include "core/Board.h"
#include "core/PieceTraits.h"

namespace shoryu::core
{
	std::vector<Position> findLegalMoves(const Board& board, Position from)
	{
		std::vector<Position> legalMoves;

		if (Board::isInside(from) == false)
			return legalMoves;

		// 指定位置に駒がない場合、空のリストを返す
		const PieceCode fromPiece = board.getPieceCode(from);
		if (isEmpty(fromPiece))
			return legalMoves; 

		const MoveSpec& moveSpec = getMoveTable(fromPiece);

		// ステップ移動の処理
		for (const auto& step : moveSpec.stepMoves)
		{
			// ステップ移動の場合のPositionを計算
			int newSuji = from.suji_ + step.dx;
			int newDan = from.dan_ + step.dy;
			Position newPos(newSuji, newDan);
			if (!Board::isInside(newPos))
				continue;

			const PieceCode destPiece = board.getPieceCode(newPos);
			if (!isEmpty(destPiece))
				if (isAlly(fromPiece, destPiece))
					continue;
			
			legalMoves.push_back(newPos);
		}

		// スライド移動の処理
		for (const auto& slide : moveSpec.slideMoves)
		{
			int dx = slide.dx;
			int dy = slide.dy;

			Position searchPos(from.suji_ + dx, from.dan_ + dy);
			while (Board::isInside(searchPos))
			{
				Position newPos = searchPos;
				const PieceCode destPiece = board.getPieceCode(newPos);
				if (isEmpty(destPiece))
				{
					legalMoves.push_back(newPos);
					searchPos.suji_ += dx;
					searchPos.dan_ += dy;
					continue;
				}
				
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
