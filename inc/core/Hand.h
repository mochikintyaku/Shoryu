// ‚¿‹î‚ğŠÇ—‚·‚éƒNƒ‰ƒX
#pragma once
#include "Types.h"
#include <map>

namespace shoryu::core
{
	class Hand
	{
	public:
		Hand();
		~Hand() = default;
		void addPiece(PieceType type);
		void removePiece(PieceType type);
		int getPieceCount(PieceType type) const;
		bool hasPiece(PieceType type) const;

	private:
		std::map<PieceType, int> pieces_;  // ‹î‚Ìí—Ş‚²‚Æ‚Ì–‡”‚ğŠÇ—
	};
}