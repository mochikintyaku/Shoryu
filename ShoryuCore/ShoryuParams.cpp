#include "ShoryuParams.h"
#include "Piece.h"


namespace shoryu::core
{
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