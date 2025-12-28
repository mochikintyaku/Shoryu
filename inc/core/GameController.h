#pragma once
#include "ShoryuCoreExport.h"
#include "Types.h"
#include "ViewDto.h"
#include <vector>
#include <memory>

namespace shoryu::core
{
	// 前方宣言
	class Game;

	// ユーザー操作とModelの橋渡しを行うControllerクラス
	class SHORYU_API GameController
	{
	public:
		GameController();
		~GameController();

		// コピー禁止、ムーブ許可
		GameController(const GameController&) = delete;
		GameController& operator=(const GameController&) = delete;
		GameController(GameController&&) noexcept;
		GameController& operator=(GameController&&) noexcept;

		// ゲームの初期化
		void startNewGame();
		void clear();

		// 盤面情報の取得（View層用）
		ViewBoardLayout getViewBoardLayout() const;
		ViewHand getSenteViewHand() const;
		ViewHand getGoteViewHand() const;
		PlayerSide getCurrentPlayer() const;
		size_t getMoveCount() const;

		// 合法手の取得
		std::vector<Position> getLegalMoves(Position from) const;

		// 指し手の実行（ユーザー操作）- Move構造体は内部実装として隠蔽
		void executeNormalMove(Position from, Position to);
		void executePromotionMove(Position from, Position to);
		void executeDropMove(Position to, PieceType pieceType);

		// 指し手の取り消し
		void undoLastMove();
		bool canUndo() const;

		// 高レベル操作
		void undoMultipleMoves(int count);

	private:
		std::unique_ptr<Game> game_;  // ポインタで所有（Pimpl イディオム）
	};
}
