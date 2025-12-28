#pragma once
#include <optional>
#include <array>
#include "Types.h"
#include "Piece.h"

namespace shoryu::core
{
	class Board
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

		// 座標変換ユーティリティ
		static int SujiToColumnIndex(int suji);
		static int DanToRowIndex(int dan);
		static int ColumnIndexToSuji(int col);
		static int RowIndexToDan(int row);

		// 盤面判定
		static bool isInside(Position pos);

	private:
		PieceLayout layout_;
	};
}