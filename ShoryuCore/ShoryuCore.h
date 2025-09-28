#pragma once
#include "MoveManager.h"
#include "Board.h"
#include "ShoryuCoreExport.h"

namespace shoryu::core
{
	class SHORYU_API ShoryuCore
	{
	public:
		ShoryuCore();
		~ShoryuCore();
		void Initialize();
		void play(Move m);
		void undo();
		Board& board();
	private:
		Board board_;
		MoveManager moveManager_;
	};
}