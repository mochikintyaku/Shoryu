#include "core/Piece.h"

namespace shoryu::core
{
	Piece::Piece(PieceType pieceType, PlayerSide owner)
		: pieceType_(pieceType), owner_(owner)
	{ }

	Piece::Piece()
		: pieceType_(PieceType::Fu), owner_(PlayerSide::Sente)

	{ }

	PieceType Piece::pieceType() const { return pieceType_; }
	void Piece::pieceType(PieceType type) { pieceType_ = type; }
	PlayerSide Piece::owner() const { return owner_; }
	void Piece::owner(PlayerSide owner) { owner_ = owner; }
}