#pragma once
#include "Board.h"
#include "Hand.h"
#include "MoveManager.h"
#include "Types.h"

namespace shoryu::core
{
	// 将棋の1局全体を管理するModelクラス
	class Game
	{
	public:
		Game();
		~Game() = default;

		// 盤面の取得（読み取り専用）
		const Board& getBoard() const;

		// 持ち駒の取得（読み取り専用）
		const Hand& getSenteHand() const;
		const Hand& getGoteHand() const;

		// 現在の手番の取得
		PlayerSide getCurrentPlayer() const;

		// 手数の取得（MoveManagerの履歴から取得）
		size_t getMoveCount() const;

		// 指し手の実行と取り消し
		void executeMove(const Move& move);
		void undoLastMove();

		// 盤面の初期化
		void initializeStartPosition();
		void clear();

	private:
		void togglePlayer();

		Board board_;
		Hand senteHand_;
		Hand goteHand_;
		MoveManager moveManager_;
		PlayerSide currentPlayer_;
	};
}