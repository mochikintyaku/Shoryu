#pragma once
#include "ShoryuCoreExport.h"
#include "ShoryuParams.h"

namespace shoryu::core
{
	class SHORYU_API Piece
	{
	public:
		Piece(PieceType type, PlayerSide owner);
		Piece();
		~Piece() = default;

		PieceType pieceType() const;
		void pieceType(PieceType type);
		PlayerSide owner() const;
		void owner(PlayerSide owner);

	private:
		PieceType pieceType_;
		PlayerSide owner_;
	};
}