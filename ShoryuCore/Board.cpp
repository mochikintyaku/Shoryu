#include "Board.h"

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
		return layout_[(int)pos.dan_][(int)pos.suji_];
	}

	void Board::setPiece(Position pos, std::optional<Piece> newPiece)
	{
		layout_[(int)pos.dan_][(int)pos.suji_] = newPiece;
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