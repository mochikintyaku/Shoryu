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

	class SHORYU_API MoveManager
	{
	public:
		typedef std::stack<const Move> MoveStack;

		MoveManager(Board& board);
		~MoveManager() = default;
		void execute(Move cmd);
		void undoLast();

	private:
		Board& board_;
		MoveStack stack_;
	};
}
#pragma warning(pop)