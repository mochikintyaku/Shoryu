#include "core/ShoryuCore.h"

namespace shoryu::core
{
	ShoryuCore::ShoryuCore()
		:board_(), senteHand_(), goteHand_(), moveManager_(board_, senteHand_, goteHand_)
	{ }


	ShoryuCore::~ShoryuCore()
	{ }

	void ShoryuCore::Initialize()
	{
		// 先手の駒を配置
		board_.setPiece(Position(1, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(2, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(3, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(4, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(5, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(6, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(7, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(8, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(9, 7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(2, 8), std::make_optional<Piece>(PieceType::Hisha, PlayerSide::Sente));
		board_.setPiece(Position(8, 8), std::make_optional<Piece>(PieceType::Kaku, PlayerSide::Sente));
		board_.setPiece(Position(1, 9), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Sente));
		board_.setPiece(Position(2, 9), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Sente));
		board_.setPiece(Position(3, 9), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Sente));
		board_.setPiece(Position(4, 9), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Sente));
		board_.setPiece(Position(5, 9), std::make_optional<Piece>(PieceType::Ou, PlayerSide::Sente));
		board_.setPiece(Position(6, 9), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Sente));
		board_.setPiece(Position(7, 9), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Sente));
		board_.setPiece(Position(8, 9), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Sente));
		board_.setPiece(Position(9, 9), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Sente));

		// 後手の駒を配置
		board_.setPiece(Position(1, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(2, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(3, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(4, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(5, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(6, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(7, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(8, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(9, 3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(2, 2), std::make_optional<Piece>(PieceType::Kaku, PlayerSide::Gote));
		board_.setPiece(Position(8, 2), std::make_optional<Piece>(PieceType::Hisha, PlayerSide::Gote));
		board_.setPiece(Position(1, 1), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Gote));
		board_.setPiece(Position(2, 1), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Gote));
		board_.setPiece(Position(3, 1), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Gote));
		board_.setPiece(Position(4, 1), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Gote));
		board_.setPiece(Position(5, 1), std::make_optional<Piece>(PieceType::Gyoku, PlayerSide::Gote));
		board_.setPiece(Position(6, 1), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Gote));
		board_.setPiece(Position(7, 1), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Gote));
		board_.setPiece(Position(8, 1), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Gote));
		board_.setPiece(Position(9, 1), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Gote));
	}

	void ShoryuCore::play(Move m)
	{
		moveManager_.execute(m);
	}

	void ShoryuCore::undo()
	{
		moveManager_.undoLast();
	}

	Board& ShoryuCore::board()
	{
		return board_;
	}
}