#include "Piece.h"

namespace shoryu::core
{
	Piece::Piece(PieceType pieceType, PlayerSide owner)
		: pieceType_(pieceType), owner_(owner)
	{ }

	PieceType Piece::pieceType() const { return pieceType_; }
	PlayerSide Piece::owner() const { return owner_; }
}