#include "ShoryuParams.h"
#include "Piece.h"


namespace shoryu::core
{
	int SujitoColumnIndex(int suji)
	{
		return BoardSize - suji;
	}

	int DantoRowIndex(int dan)
	{
		return dan - 1;
	}

	int ColumnIndexToSuji(int col)
	{
		return BoardSize - col;
	}

	int RowIndexToDan(int row)
	{
		return row + 1;
	}

	bool isNormalPiece(PieceType p)
	{
		return static_cast<int>(p) >= static_cast<int>(PieceType::Fu) &&
			static_cast<int>(p) <= static_cast<int>(PieceType::Gyoku);
	}

	bool isPromotedPiece(PieceType p)
	{
		return static_cast<int>(p) >= static_cast<int>(PieceType::Tokin) &&
			static_cast<int>(p) <= static_cast<int>(PieceType::Ryu);
	}

	bool canPromote(const Piece& piece)
	{
		auto pieceType = piece.pieceType();
		auto it = PromoteMap.find(pieceType);
		if (it == PromoteMap.end())
		{
			return false;
		}

		return true;
	}
}