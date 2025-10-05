#pragma once
#include "Types.h"
#include "Piece.h"
#include <optional>

namespace shoryu::core
{
	struct Move
	{
		std::optional<Position> from;	// ˆÚ“®Œ³
		Position to;	// ˆÚ“®æ
		std::optional<Piece> capturedPiece; // æ‚Á‚½‹î(‚È‚¯‚ê‚Înullopt)
		std::optional<Piece> movedPieceBefore; // ˆÚ“®‘O‚Ì‹î
		Piece movedPieceAfter;  // ˆÚ“®Œã‚Ì‹î(¬‚Á‚Ä‚¢‚ê‚Î¬‚Á‚½Œã‚Ì‹î)
	};
}