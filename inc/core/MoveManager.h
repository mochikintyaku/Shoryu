#pragma once
#include "Move.h"
#include <stack>

namespace shoryu::core
{
	class Board;
	class Hand;

	class MoveManager
	{
	public:
		typedef std::stack<Move> MoveStack;

		MoveManager(Board& board, Hand& sente, Hand& gote);
		~MoveManager();
		void execute(Move cmd);
		void undoLast();

		// è”i—š—ğ‚Ì[‚³j‚ğæ“¾
		size_t getMoveCount() const;

	private:
		Board& board_;
		Hand& senteHand_;
		Hand& goteHand_;
		MoveStack stack_;
	};
}