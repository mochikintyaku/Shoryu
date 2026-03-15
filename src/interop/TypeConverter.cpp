#include "interop/TypeConverter.h"

namespace shoryu::interop
{
	ManagedPosition TypeConverter::ToManaged(shoryu::core::Position pos)
	{
		return ManagedPosition(pos.suji_, pos.dan_);
	}

	ManagedPieceCode TypeConverter::ToManaged(shoryu::core::PieceCode pc)
	{
		return static_cast<ManagedPieceCode>(static_cast<int>(pc));
	}

	ManagedPieceLayout TypeConverter::ToManaged(const shoryu::core::PieceLayout& layout)
	{
		auto board = gcnew array<ManagedPieceCode, 2>(ManagedPieceLayout::BoardSize, ManagedPieceLayout::BoardSize);

		for (int row = 0; row < ManagedPieceLayout::BoardSize; ++row)
		{
			for (int col = 0; col < ManagedPieceLayout::BoardSize; ++col)
			{
				board[row, col] = ToManaged(layout[row][col]);
			}
		}

		return ManagedPieceLayout(board);
	}

	ManagedHandCounts TypeConverter::ToManaged(const std::array<int, shoryu::core::NumHandPieceType * 2>& counts)
	{
		auto managed = gcnew array<int>(ManagedHandCounts::CountsLength);

		for (int i = 0; i < ManagedHandCounts::CountsLength; ++i)
		{
			managed[i] = counts[static_cast<size_t>(i)];
		}

		return ManagedHandCounts(managed);
	}

	shoryu::core::Position TypeConverter::ToNative(ManagedPosition pos)
	{
		return shoryu::core::Position(pos.Suji, pos.Dan);
	}

	shoryu::core::PieceCode TypeConverter::ToNative(ManagedPieceCode pc)
	{
		return static_cast<shoryu::core::PieceCode>(static_cast<int>(pc));
	}
}