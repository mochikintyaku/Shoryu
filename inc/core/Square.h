#pragma once
#include "Types.h"

namespace shoryu::core
{
	constexpr static int BoardSize = 9;

	inline int SujitoColumnIndex(int suji)
	{
		return BoardSize - suji;
	}

	inline int DantoRowIndex(int dan)
	{
		return dan - 1;
	}

	inline int ColumnIndexToSuji(int col)
	{
		return BoardSize - col;
	}

	inline int RowIndexToDan(int row)
	{
		return row + 1;
	}

	inline bool isInside(Position pos)
	{
		if ((pos.suji_ < 1) || (pos.suji_ > 9))
		{
			return false;
		}
		if ((pos.dan_ < 1) || (pos.dan_ > 9))
		{
			return false;
		}

		return true;
	}
}
