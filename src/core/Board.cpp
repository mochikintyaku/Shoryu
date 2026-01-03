#include "core/Board.h"

namespace shoryu::core
{
	Board::Board()
	{
		for (auto& dan : layout_)
		{
			for (auto& square : dan)
			{
				square = std::nullopt;
			}
		}
	}

	void Board::Clear()
	{
		for (auto& dan : layout_)
		{
			for (auto& square : dan)
			{
				square = std::nullopt;
			}
		}
	}

	Square Board::getSquare(Position pos) const
	{
		int rowIdx = DanToRowIndex(pos.dan_);
		int colIdx = SujiToColumnIndex(pos.suji_);
		return layout_[rowIdx][colIdx];
	}

	void Board::setSquare(Position pos, Square square)
	{
		int rowIdx = DanToRowIndex(pos.dan_);
		int colIdx = SujiToColumnIndex(pos.suji_);
		layout_[rowIdx][colIdx] = square;
	}

	void Board::setLayout(PieceLayout& newLayout)
	{
		layout_ = newLayout;
	}

	const Board::PieceLayout& Board::getLayout() const
	{
		return layout_;
	}

	// 座標変換ユーティリティの実装
	int Board::SujiToColumnIndex(int suji)
	{
		return BoardSize - suji;
	}

	int Board::DanToRowIndex(int dan)
	{
		return dan - 1;
	}

	int Board::ColumnIndexToSuji(int col)
	{
		return BoardSize - col;
	}

	int Board::RowIndexToDan(int row)
	{
		return row + 1;
	}

	// 盤面判定の実装
	bool Board::isInside(Position pos)
	{
		if ((pos.suji_ < 1) || (pos.suji_ > BoardSize))
		{
			return false;
		}
		if ((pos.dan_ < 1) || (pos.dan_ > BoardSize))
		{
			return false;
		}
		return true;
	}
}