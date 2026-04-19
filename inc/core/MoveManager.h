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

		MoveManager(Board& board, Hand& hand);
		~MoveManager();
		void clear();
		void execute(Move cmd);
		void undoLast();

		// 手数（履歴の深さ）を取得
		size_t getMoveCount() const;

	private:
		Board& board_;
		Hand& hand_;
		MoveStack stack_;
	};
}