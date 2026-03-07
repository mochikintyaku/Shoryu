#pragma once
#include <optional>
#include <array>
#include "Types.h"

namespace shoryu::core
{
	class Board
	{
	public:
		typedef std::array<std::array<PieceCode, BoardSize>, BoardSize> PieceLayout;

		Board();
		~Board() = default;

		void Clear();
		PieceCode getSquare(Position pos) const;
		void setSquare(Position pos, PieceCode pieceCode);
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