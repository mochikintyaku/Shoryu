#pragma once
#include "ShoryuCoreExport.h"
#include "ShoryuParams.h"

namespace shoryu::core
{
	class SHORYU_API Piece
	{
	public:
		Piece(PieceType type, PlayerSide owner);
		~Piece() = default;

		PieceType pieceType() const;
		PlayerSide owner() const;

	private:
		PieceType pieceType_;
		PlayerSide owner_;
	};
}