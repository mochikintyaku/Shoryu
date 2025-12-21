#include "core/GameController.h"
#include "core/PieceTraits.h"
#include <cassert>

namespace shoryu::core
{
	GameController::GameController()
		: game_()
	{
		startNewGame();
	}

	void GameController::startNewGame()
	{
		game_.initializeStartPosition();
	}

	void GameController::clear()
	{
		game_.clear();
	}

	const Board& GameController::getBoard() const
	{
		return game_.getBoard();
	}

	const Hand& GameController::getSenteHand() const
	{
		return game_.getSenteHand();
	}

	const Hand& GameController::getGoteHand() const
	{
		return game_.getGoteHand();
	}

	PlayerSide GameController::getCurrentPlayer() const
	{
		return game_.getCurrentPlayer();
	}

	size_t GameController::getMoveCount() const
	{
		return game_.getMoveCount();
	}

	std::vector<Position> GameController::getLegalMoves(Position from) const
	{
		return findLegalMoves(game_.getBoard(), from);
	}

	Move GameController::createNormalMove(Position from, Position to) const
	{
		// 事前条件: from に駒が存在する
		assert(game_.getBoard().getPiece(from).has_value() 
		       && "Precondition violated: No piece at 'from' position");
		
		return Move(
			from,
			to,
			game_.getBoard().getPiece(to),
			game_.getBoard().getPiece(from),
			*game_.getBoard().getPiece(from)
		);
	}

	Move GameController::createPromotionMove(Position from, Position to) const
	{
		// 事前条件: from に駒が存在する
		assert(game_.getBoard().getPiece(from).has_value() 
		       && "Precondition violated: No piece at 'from' position");
		
		Piece originalPiece = *game_.getBoard().getPiece(from);
		
		// 事前条件: 駒が成れる種類である
		assert(canPromotePiece(originalPiece.pieceType()) 
		       && "Precondition violated: Piece cannot be promoted");
		
		return Move(
			from,
			to,
			game_.getBoard().getPiece(to),
			originalPiece,
			Piece(promoteType(originalPiece.pieceType()), originalPiece.owner())
		);
	}

	Move GameController::createDropMove(Position to, PieceType pieceType) const
	{
		// 事前条件: to が空マスである
		assert(!game_.getBoard().getPiece(to).has_value() 
		       && "Precondition violated: 'to' position must be empty for drop move");
		
		// 事前条件: 持ち駒に指定した駒がある
		const Hand& hand = (game_.getCurrentPlayer() == PlayerSide::Sente) 
		                   ? game_.getSenteHand() 
		                   : game_.getGoteHand();
		assert(hand.hasPiece(pieceType) 
		       && "Precondition violated: No piece in hand to drop");
		
		return Move(
			std::nullopt,
			to,
			std::nullopt,
			std::nullopt,
			Piece(pieceType, game_.getCurrentPlayer())
		);
	}

	void GameController::executeMove(const Move& move)
	{
		game_.executeMove(move);
	}

	void GameController::undoLastMove()
	{
		game_.undoLastMove();
	}

	bool GameController::canUndo() const
	{
		return game_.getMoveCount() > 0;
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