#include "interop/ManagedTypes.h"

namespace shoryu::interop
{
	ManagedPosition::ManagedPosition(int suji, int dan)
		: Suji(suji), Dan(dan)
	{
	}

	ManagedPieceLayout::ManagedPieceLayout(array<ManagedPieceCode, 2>^ board)
		: Board(board)
	{
	}

	ManagedHandCounts::ManagedHandCounts(array<int>^ counts)
		: Counts(counts)
	{
	}
}
