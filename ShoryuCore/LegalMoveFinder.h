#pragma once
#include <vector>
#include "ShoryuParams.h"

namespace shoryu::core
{
	class Board;

	std::vector<Position> findLegalMoves(const Board& board, Position from);
}