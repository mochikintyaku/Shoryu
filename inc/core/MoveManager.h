#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)
#include "Move.h"
#include "ShoryuCoreExport.h"
#include <memory>
#include <stack>

namespace shoryu::core
{
	class Board;
	class Hand;

	class SHORYU_API MoveManager
	{
	public:
		typedef std::stack<Move> MoveStack;

		MoveManager(Board& board, Hand& sente, Hand& gote);
		~MoveManager();
		void execute(Move cmd);
		void undoLast();

	private:
		Board& board_;
		Hand& senteHand_;
		Hand& goteHand_;
		MoveStack stack_;
	};
}
#pragma warning(pop)