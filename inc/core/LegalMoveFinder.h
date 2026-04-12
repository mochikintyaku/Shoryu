#pragma once
#include <vector>
#include "Types.h"

namespace shoryu::core
{
	class Board;

	std::vector<Position> findLegalMoves(const Board& board, Position from);
}