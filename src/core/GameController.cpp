#include "core/GameController.h"
#include "core/Game.h"
#include "core/Move.h"
#include "core/LegalMoveFinder.h"
#include "core/PieceTraits.h"
#include <cassert>

namespace shoryu::core
{
	GameController::GameController()
		: game_(std::make_unique<Game>())
	{
		startNewGame();
	}

	GameController::~GameController() = default;

	GameController::GameController(GameController&&) noexcept = default;
	GameController& GameController::operator=(GameController&&) noexcept = default;

	void GameController::startNewGame()
	{
		game_->initializeStartPosition();
	}

	void GameController::clear()
	{
		game_->clear();
	}

	ViewBoardLayout GameController::getViewBoardLayout() const
	{
		ViewBoardLayout viewLayout;
		const auto& board = game_->getBoard();
		
		for (int dan = 1; dan <= BoardSize; ++dan)
		{
			for (int suji = 1; suji <= BoardSize; ++suji)
			{
				Position pos(suji, dan);
				auto square = board.getSquare(pos);
				
				int rowIdx = Board::DanToRowIndex(dan);
				int colIdx = Board::SujiToColumnIndex(suji);
				
				if (!square)
				{
					viewLayout[rowIdx][colIdx] = ViewSquare{ .hasPiece = false };
				}
				else
				{
					viewLayout[rowIdx][colIdx] = ViewSquare{
						.hasPiece = true,
						.owner = square->owner(),
						.pieceType = square->pieceType()
					};
				}
			}
		}
		
		return viewLayout;
	}

	ViewHand GameController::getSenteViewHand() const
	{
		const auto& hand = game_->getSenteHand();
		ViewHand viewHand;
		
		viewHand.hands[0] = hand.getPieceCount(PieceType::Fu);
		viewHand.hands[1] = hand.getPieceCount(PieceType::Kyo);
		viewHand.hands[2] = hand.getPieceCount(PieceType::Kei);
		viewHand.hands[3] = hand.getPieceCount(PieceType::Gin);
		viewHand.hands[4] = hand.getPieceCount(PieceType::Kin);
		viewHand.hands[5] = hand.getPieceCount(PieceType::Kaku);
		viewHand.hands[6] = hand.getPieceCount(PieceType::Hisha);
		
		return viewHand;
	}

	ViewHand GameController::getGoteViewHand() const
	{
		const auto& hand = game_->getGoteHand();
		ViewHand viewHand;
		
		viewHand.hands[0] = hand.getPieceCount(PieceType::Fu);
		viewHand.hands[1] = hand.getPieceCount(PieceType::Kyo);
		viewHand.hands[2] = hand.getPieceCount(PieceType::Kei);
		viewHand.hands[3] = hand.getPieceCount(PieceType::Gin);
		viewHand.hands[4] = hand.getPieceCount(PieceType::Kin);
		viewHand.hands[5] = hand.getPieceCount(PieceType::Kaku);
		viewHand.hands[6] = hand.getPieceCount(PieceType::Hisha);
		
		return viewHand;
	}

	PlayerSide GameController::getCurrentPlayer() const
	{
		return game_->getCurrentPlayer();
	}

	size_t GameController::getMoveCount() const
	{
		return game_->getMoveCount();
	}

	std::vector<Position> GameController::getLegalMoves(Position from) const
	{
		return findLegalMoves(game_->getBoard(), from);
	}

	void GameController::executeNormalMove(Position from, Position to)
	{
		// 事前条件: from に駒が存在する
		assert(game_->getBoard().getSquare(from).has_value() 
		       && "Precondition violated: No piece at 'from' position");
		
		// Move 構造体を内部で構築
		Move move(
			from,
			to,
			game_->getBoard().getSquare(to),	// capturedPiece
			game_->getBoard().getSquare(from),	// movedPieceBefore
			*game_->getBoard().getSquare(from)	// movedPieceAfter
		);
		
		// Game に実行を委譲
		game_->executeMove(move);
	}

	void GameController::executePromotionMove(Position from, Position to)
	{
		// 事前条件: from に駒が存在する
		assert(game_->getBoard().getSquare(from).has_value() 
		       && "Precondition violated: No piece at 'from' position");
		
		Piece originalPiece = *game_->getBoard().getSquare(from);
		
		// 事前条件: 駒が成れる種類である
		assert(canPromotePiece(originalPiece.pieceType()) 
		       && "Precondition violated: Piece cannot be promoted");
		
		// Move 構造体を内部で構築（成った後の駒）
		Move move(
			from,
			to,
			game_->getBoard().getSquare(to),	// capturedPiece
			originalPiece,						// movedPieceBefore
			Piece(promoteType(originalPiece.pieceType()), originalPiece.owner())	// movedPieceAfter
		);
		
		// Game に実行を委譲
		game_->executeMove(move);
	}

	void GameController::executeDropMove(Position to, PieceType pieceType)
	{
		// 事前条件: to が空マスである
		assert(!game_->getBoard().getSquare(to).has_value() 
		       && "Precondition violated: 'to' position must be empty for drop move");
		
		// 事前条件: 持ち駒に指定した駒がある
		const Hand& hand = (game_->getCurrentPlayer() == PlayerSide::Sente) 
		                   ? game_->getSenteHand() 
		                   : game_->getGoteHand();
		assert(hand.hasPiece(pieceType) 
		       && "Precondition violated: No piece in hand to drop");
		
		// Move 構造体を内部で構築（持ち駒を打つ）
		Move move(
			std::nullopt,		// from
			to,
			std::nullopt,		// capturedPiece
			std::nullopt,		// movedPieceBefore
			Piece(pieceType, game_->getCurrentPlayer())		// movedPieceAfter
		);
		
		// Game に実行を委譲
		game_->executeMove(move);
	}

	void GameController::undoLastMove()
	{
		game_->undoLastMove();
	}

	bool GameController::canUndo() const
	{
		return game_->getMoveCount() > 0;
	}

	void GameController::undoMultipleMoves(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			if (!canUndo()) break;
			undoLastMove();
		}
	}
}