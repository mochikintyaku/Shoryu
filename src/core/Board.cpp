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

	const std::optional<Piece> Board::getPiece(Position pos) const
	{
		int rowIdx = DantoRowIndex(pos.dan_);
		int colIdx = SujitoColumnIndex(pos.suji_);
		return layout_[rowIdx][colIdx];
	}

	void Board::setPiece(Position pos, std::optional<Piece> newPiece)
	{
		int rowIdx = DantoRowIndex(pos.dan_);
		int colIdx = SujitoColumnIndex(pos.suji_);
		layout_[rowIdx][colIdx] = newPiece;
	}

	void Board::setLayout(PieceLayout& newLayout)
	{
		layout_ = newLayout;
	}

	const Board::PieceLayout& Board::getLayout() const
	{
		return layout_;
	}
}