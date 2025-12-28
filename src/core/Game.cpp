#include "core/Game.h"
#include "core/Piece.h"
#include <optional>

namespace shoryu::core
{
	Game::Game()
		: board_()
		, senteHand_()
		, goteHand_()
		, moveManager_(board_, senteHand_, goteHand_)
		, currentPlayer_(PlayerSide::Sente)
	{
	}

	const Board& Game::getBoard() const
	{
		return board_;
	}

	const Hand& Game::getSenteHand() const
	{
		return senteHand_;
	}

	const Hand& Game::getGoteHand() const
	{
		return goteHand_;
	}

	PlayerSide Game::getCurrentPlayer() const
	{
		return currentPlayer_;
	}

	size_t Game::getMoveCount() const
	{
		return moveManager_.getMoveCount();
	}

	void Game::executeMove(const Move& move)
	{
		moveManager_.execute(move);
		togglePlayer();
	}

	void Game::undoLastMove()
	{
		if (getMoveCount() > 0)
		{
			moveManager_.undoLast();
			togglePlayer();
		}
	}

	void Game::togglePlayer()
	{
		currentPlayer_ = (currentPlayer_ == PlayerSide::Sente) ? PlayerSide::Gote : PlayerSide::Sente;
	}

	void Game::initializeStartPosition()
	{
		clear();

		// 先手の駒配置（下側）
		// 9段目（最下段）
		board_.setPiece(Position(1, 9), Piece(PieceType::Kyo, PlayerSide::Sente));
		board_.setPiece(Position(2, 9), Piece(PieceType::Kei, PlayerSide::Sente));
		board_.setPiece(Position(3, 9), Piece(PieceType::Gin, PlayerSide::Sente));
		board_.setPiece(Position(4, 9), Piece(PieceType::Kin, PlayerSide::Sente));
		board_.setPiece(Position(5, 9), Piece(PieceType::Ou, PlayerSide::Sente));
		board_.setPiece(Position(6, 9), Piece(PieceType::Kin, PlayerSide::Sente));
		board_.setPiece(Position(7, 9), Piece(PieceType::Gin, PlayerSide::Sente));
		board_.setPiece(Position(8, 9), Piece(PieceType::Kei, PlayerSide::Sente));
		board_.setPiece(Position(9, 9), Piece(PieceType::Kyo, PlayerSide::Sente));

		// 8段目
		board_.setPiece(Position(2, 8), Piece(PieceType::Kaku, PlayerSide::Sente));
		board_.setPiece(Position(8, 8), Piece(PieceType::Hisha, PlayerSide::Sente));

		// 7段目（歩）
		for (int suji = 1; suji <= 9; suji++)
		{
			board_.setPiece(Position(suji, 7), Piece(PieceType::Fu, PlayerSide::Sente));
		}

		// 後手の駒配置（上側）
		// 1段目（最上段）
		board_.setPiece(Position(1, 1), Piece(PieceType::Kyo, PlayerSide::Gote));
		board_.setPiece(Position(2, 1), Piece(PieceType::Kei, PlayerSide::Gote));
		board_.setPiece(Position(3, 1), Piece(PieceType::Gin, PlayerSide::Gote));
		board_.setPiece(Position(4, 1), Piece(PieceType::Kin, PlayerSide::Gote));
		board_.setPiece(Position(5, 1), Piece(PieceType::Gyoku, PlayerSide::Gote));
		board_.setPiece(Position(6, 1), Piece(PieceType::Kin, PlayerSide::Gote));
		board_.setPiece(Position(7, 1), Piece(PieceType::Gin, PlayerSide::Gote));
		board_.setPiece(Position(8, 1), Piece(PieceType::Kei, PlayerSide::Gote));
		board_.setPiece(Position(9, 1), Piece(PieceType::Kyo, PlayerSide::Gote));

		// 2段目
		board_.setPiece(Position(8, 2), Piece(PieceType::Kaku, PlayerSide::Gote));
		board_.setPiece(Position(2, 2), Piece(PieceType::Hisha, PlayerSide::Gote));

		// 3段目（歩）
		for (int suji = 1; suji <= 9; suji++)
		{
			board_.setPiece(Position(suji, 3), Piece(PieceType::Fu, PlayerSide::Gote));
		}

		currentPlayer_ = PlayerSide::Sente;
	}

	void Game::clear()
	{
		board_.Clear();
		senteHand_ = Hand();
		goteHand_ = Hand();
		currentPlayer_ = PlayerSide::Sente;
	}
}
