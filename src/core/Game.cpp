#include "core/Game.h"
#include "core/LegalMoveFinder.h"
#include "core/PieceTraits.h"
#include <cassert>

namespace shoryu::core
{
	Game::Game()
		: board_()
		, hand_()
		, moveManager_(board_, hand_)
		, currentPlayer_(PlayerSide::Sente)
	{
		NewGame();
	}

	void Game::NewGame()
	{
		initializeStartPosition();
	}

	void Game::initializeStartPosition()
	{
		clear();

		// 先手（下側: dan=7..9）
		board_.setPiece(Position(1, 9), PieceCode::SenteKyo);
		board_.setPiece(Position(2, 9), PieceCode::SenteKei);
		board_.setPiece(Position(3, 9), PieceCode::SenteGin);
		board_.setPiece(Position(4, 9), PieceCode::SenteKin);
		board_.setPiece(Position(5, 9), PieceCode::Ou);
		board_.setPiece(Position(6, 9), PieceCode::SenteKin);
		board_.setPiece(Position(7, 9), PieceCode::SenteGin);
		board_.setPiece(Position(8, 9), PieceCode::SenteKei);
		board_.setPiece(Position(9, 9), PieceCode::SenteKyo);

		board_.setPiece(Position(2, 8), PieceCode::SenteKaku);
		board_.setPiece(Position(8, 8), PieceCode::SenteHisya);

		for (int suji = 1; suji <= BoardSize; ++suji)
		{
			board_.setPiece(Position(suji, 7), PieceCode::SenteFu);
		}

		// 後手（上側: dan=1..3）
		board_.setPiece(Position(1, 1), PieceCode::GoteKyo);
		board_.setPiece(Position(2, 1), PieceCode::GoteKei);
		board_.setPiece(Position(3, 1), PieceCode::GoteGin);
		board_.setPiece(Position(4, 1), PieceCode::GoteKin);
		board_.setPiece(Position(5, 1), PieceCode::Gyoku);
		board_.setPiece(Position(6, 1), PieceCode::GoteKin);
		board_.setPiece(Position(7, 1), PieceCode::GoteGin);
		board_.setPiece(Position(8, 1), PieceCode::GoteKei);
		board_.setPiece(Position(9, 1), PieceCode::GoteKyo);

		board_.setPiece(Position(8, 2), PieceCode::GoteKaku);
		board_.setPiece(Position(2, 2), PieceCode::GoteHisya);

		for (int suji = 1; suji <= BoardSize; ++suji)
		{
			board_.setPiece(Position(suji, 3), PieceCode::GoteFu);
		}

		currentPlayer_ = PlayerSide::Sente;
	}

	void Game::clear()
	{
		board_.Clear();
		hand_ = Hand();
		moveManager_.clear();
		currentPlayer_ = PlayerSide::Sente;
	}

	PieceLayout Game::getLayout() const
	{
		return board_.getLayout();
	}

	std::array<int, NumHandPieceType> Game::getSenteHand() const
	{
		std::array<int, NumHandPieceType> counts{};
		counts[0] = hand_.count(PieceCode::SenteFu);
		counts[1] = hand_.count(PieceCode::SenteKyo);
		counts[2] = hand_.count(PieceCode::SenteKei);
		counts[3] = hand_.count(PieceCode::SenteGin);
		counts[4] = hand_.count(PieceCode::SenteKin);
		counts[5] = hand_.count(PieceCode::SenteKaku);
		counts[6] = hand_.count(PieceCode::SenteHisya);
		return counts;
	}

	std::array<int, NumHandPieceType> Game::getGoteHand() const
	{
		std::array<int, NumHandPieceType> counts{};
		counts[0] = hand_.count(PieceCode::GoteFu);
		counts[1] = hand_.count(PieceCode::GoteKyo);
		counts[2] = hand_.count(PieceCode::GoteKei);
		counts[3] = hand_.count(PieceCode::GoteGin);
		counts[4] = hand_.count(PieceCode::GoteKin);
		counts[5] = hand_.count(PieceCode::GoteKaku);
		counts[6] = hand_.count(PieceCode::GoteHisya);
		return counts;
	}

	PlayerSide Game::getCurrentPlayer() const
	{
		return currentPlayer_;
	}

	size_t Game::getMoveCount() const
	{
		return moveManager_.getMoveCount();
	}

	std::vector<Position> Game::getLegalMoves(Position from) const
	{
		return findLegalMoves(board_, from);
	}

	void Game::executeNormalMove(Position from, Position to)
	{
		assert(!isEmpty(board_.getPiece(from)) && "executeNormalMove: No piece at 'from'");

		const PieceCode movedBefore = board_.getPiece(from);
		const PieceCode captured = board_.getPiece(to);

		const Move move(from, to, captured, movedBefore, movedBefore);
		moveManager_.execute(move);
		togglePlayer();
	}

	void Game::executePromotionMove(Position from, Position to)
	{
		assert(!isEmpty(board_.getPiece(from)) && "executePromotionMove: No piece at 'from'");

		const PieceCode movedBefore = board_.getPiece(from);
		assert(canPromotePiece(movedBefore) && "executePromotionMove: Piece cannot be promoted");

		const PieceCode captured = board_.getPiece(to);
		const PieceCode movedAfter = promote(movedBefore);

		const Move move(from, to, captured, movedBefore, movedAfter);
		moveManager_.execute(move);
		togglePlayer();
	}

	void Game::executeDropMove(Position to, PieceCode pc)
	{
		assert(isEmpty(board_.getPiece(to)) && "executeDropMove: 'to' position must be empty");

		assert(isHandPiece(pc) && "executeDropMove: pc must be a hand piece");
		assert(ownerOf(pc) == currentPlayer_ && "executeDropMove: pc owner mismatch");

		assert(hand_.has(pc) && "executeDropMove: No piece in hand to drop");

		const Move move(std::nullopt, to, PieceCode::Empty, PieceCode::Empty, pc);
		moveManager_.execute(move);
		togglePlayer();
	}

	void Game::undoLastMove()
	{
		if (!canUndo())
			return;

		moveManager_.undoLast();
		togglePlayer();
	}

	bool Game::canUndo() const
	{
		return getMoveCount() > 0;
	}

	void Game::undoMultipleMoves(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			if (!canUndo())
				break;

			undoLastMove();
		}
	}

	void Game::togglePlayer()
	{
		currentPlayer_ = (currentPlayer_ == PlayerSide::Sente) ? PlayerSide::Gote : PlayerSide::Sente;
	}
}
