#include "interop/ManagedTypes.h"

namespace shoryu::interop
{
	ManagedPosition::ManagedPosition(int suji, int dan)
		: Suji(suji), Dan(dan)
	{
	}

	ManagedViewHand::ManagedViewHand(array<int>^ hands)
		: Hands(hands)
	{
	}

	ManagedViewBoardLayout::ManagedViewBoardLayout(array<ManagedViewSquare, 2>^ board)
		: Board(board)
	{
	}
}
