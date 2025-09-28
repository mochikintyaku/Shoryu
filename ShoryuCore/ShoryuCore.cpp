#include "ShoryuCore.h"

namespace shoryu::core
{
	ShoryuCore::ShoryuCore()
		:board_(), moveManager_(board_)
	{ }


	ShoryuCore::~ShoryuCore()
	{ }

	void ShoryuCore::Initialize()
	{
		// 先手の駒を配置
		board_.setPiece(Position(Suji::_1, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_2, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_3, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_4, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_5, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_6, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_7, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_8, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_9, Dan::_7), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_2, Dan::_8), std::make_optional<Piece>(PieceType::Hisha, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_8, Dan::_8), std::make_optional<Piece>(PieceType::Kaku, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_1, Dan::_9), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_2, Dan::_9), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_3, Dan::_9), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_4, Dan::_9), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_5, Dan::_9), std::make_optional<Piece>(PieceType::Ou, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_6, Dan::_9), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_7, Dan::_9), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_8, Dan::_9), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Sente));
		board_.setPiece(Position(Suji::_9, Dan::_9), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Sente));

		// 後手の駒を配置
		board_.setPiece(Position(Suji::_1, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_2, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_3, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_4, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_5, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_6, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_7, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_8, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_9, Dan::_3), std::make_optional<Piece>(PieceType::Fu, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_2, Dan::_2), std::make_optional<Piece>(PieceType::Kaku, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_8, Dan::_2), std::make_optional<Piece>(PieceType::Hisha, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_1, Dan::_1), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_2, Dan::_1), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_3, Dan::_1), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_4, Dan::_1), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_5, Dan::_1), std::make_optional<Piece>(PieceType::Gyoku, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_6, Dan::_1), std::make_optional<Piece>(PieceType::Kin, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_7, Dan::_1), std::make_optional<Piece>(PieceType::Gin, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_8, Dan::_1), std::make_optional<Piece>(PieceType::Kei, PlayerSide::Gote));
		board_.setPiece(Position(Suji::_9, Dan::_1), std::make_optional<Piece>(PieceType::Kyo, PlayerSide::Gote));
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