#pragma once
#include "Board.h"
#include "Hand.h"
#include "MoveManager.h"
#include "Types.h"
#include <array>
#include <vector>

namespace shoryu::core
{
	// 将棋の1局全体を管理するModelクラス兼公開APIをもつContollerクラス
	class Game
	{
	public:
		Game();
		~Game() = default;

		// ゲームの初期化
		void newGame();
		void clear();

		// 盤面情報の取得
		PieceLayout getLayout() const;
		std::array<int, NumHandPieceType*2> getHandCounts() const;
		PlayerSide getCurrentPlayer() const;
		size_t getMoveCount() const;

		// 合法手の取得
		std::vector<Position> getLegalMoves(Position from) const;

		// 指し手の実行
		void executeNormalMove(Position from, Position to);
		void executePromotionMove(Position from, Position to);
		void executeDropMove(Position to, PieceCode pc);

		// 指し手の取り消し
		void undoLastMove();
		bool canUndo() const;

		// 高レベル操作
		void undoMultipleMoves(int count);

	private:
		void initializeStartPosition();
		void togglePlayer();

		Board board_;
		Hand hand_;
		MoveManager moveManager_;
		PlayerSide currentPlayer_;
	};
}