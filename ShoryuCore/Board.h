#pragma once
#include <optional>
#include <array>
#include "ShoryuCoreExport.h"
#include "ShoryuParams.h"
#include "Piece.h"

namespace shoryu::core
{
	class SHORYU_API Board
	{
	public:
		typedef std::array<std::array<std::optional<Piece>, BoardSize>, BoardSize> PieceLayout;

		Board();
		~Board() = default;

		void Clear();
		const std::optional<Piece> getPiece(Position pos) const;
		void setPiece(Position pos, std::optional<Piece> newPiece);
		void setLayout(PieceLayout& newLayout);
		const PieceLayout& getLayout() const;

	private:
		PieceLayout layout_;
	};
}