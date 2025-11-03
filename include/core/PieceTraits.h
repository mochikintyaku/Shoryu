#pragma once
#include "Types.h"
#include "Piece.h"

namespace shoryu::core
{
	inline bool isNormalPiece(PieceType p)
	{
		return (static_cast<int>(p) >= static_cast<int>(PieceType::Fu)) &&
			(static_cast<int>(p) <= static_cast<int>(PieceType::Gyoku));
	}

	inline bool isPromotedPiece(PieceType p)
	{
		return (static_cast<int>(p) >= static_cast<int>(PieceType::Tokin)) &&
			(static_cast<int>(p) <= static_cast<int>(PieceType::Ryu));
	}

	inline bool canPromotePiece(PieceType p)
	{
		auto it = PromoteMap.find(p);
		if (it == PromoteMap.end())
		{
			return false;
		}

		return true;
	}

	inline bool isAlly(const Piece& a, const Piece& b)
	{
		return a.owner() == b.owner();
	}

	inline bool isEnemy(const Piece& a, const Piece& b)
	{
		return a.owner() != b.owner();
	}
}