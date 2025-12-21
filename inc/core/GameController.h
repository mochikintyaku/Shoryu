#pragma once
#include "Game.h"
#include "Move.h"
#include "LegalMoveFinder.h"
#include "ShoryuCoreExport.h"
#include <vector>
#include <optional>

namespace shoryu::core
{
	// ユーザー操作とModelの橋渡しを行うControllerクラス
	class SHORYU_API GameController
	{
	public:
		GameController();
		~GameController() = default;

		// コピー禁止、ムーブ許可
		GameController(const GameController&) = delete;
		GameController& operator=(const GameController&) = delete;
		GameController(GameController&&) = default;
		GameController& operator=(GameController&&) = default;

		// ゲームの初期化
		void startNewGame();
		void clear();

		// 盤面情報の取得（View層用）
		const Board& getBoard() const;
		const Hand& getSenteHand() const;
		const Hand& getGoteHand() const;
		PlayerSide getCurrentPlayer() const;
		size_t getMoveCount() const;

		// 合法手の取得
		std::vector<Position> getLegalMoves(Position from) const;

		// Move構築ヘルパー（Controller層の責務）
		Move createNormalMove(Position from, Position to) const;
		Move createPromotionMove(Position from, Position to) const;
		Move createDropMove(Position to, PieceType pieceType) const;

		// 指し手の実行と取り消し
		void executeMove(const Move& move);
		void undoLastMove();
		bool canUndo() const;

		// 高レベル操作
		void undoMultipleMoves(int count);

	private:
		Game game_;  // 値型で所有
	};
}
