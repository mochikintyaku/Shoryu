#include <iostream>
#include "utils.h"
#include "ShoryuCore.h"
#include <optional>

int main()
{
	using namespace shoryu::core;
	ShoryuCore core;
	core.Initialize();

	Move m1 = {
		.from = Position(Suji::_7, Dan::_7),
		.to = Position(Suji::_7, Dan::_6),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = Piece(PieceType::Fu, PlayerSide::Sente),
		.movedPieceAfter = Piece(PieceType::Fu, PlayerSide::Sente)
	};

	Move m2 = {
		.from = Position(Suji::_8, Dan::_3),
		.to = Position(Suji::_8, Dan::_4),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = Piece(PieceType::Fu, PlayerSide::Gote),
		.movedPieceAfter = Piece(PieceType::Fu, PlayerSide::Gote)
	};

	Move m3 = {
		.from = Position(Suji::_2, Dan::_7),
		.to = Position(Suji::_2, Dan::_6),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = Piece(PieceType::Fu, PlayerSide::Sente),
		.movedPieceAfter = Piece(PieceType::Fu, PlayerSide::Sente)
	};

	show(core.board().getLayout());
	core.play(m1);
	show(core.board().getLayout());
	core.play(m2);
	show(core.board().getLayout());
	core.play(m3);
	show(core.board().getLayout());
	core.undo();
	show(core.board().getLayout());
	core.undo();
	show(core.board().getLayout());
	core.undo();
	show(core.board().getLayout());

	return 0;
}