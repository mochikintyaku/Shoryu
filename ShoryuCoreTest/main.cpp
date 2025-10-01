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
		.from = Position(7, 7),
		.to = Position(7, 6),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = Piece(PieceType::Fu, PlayerSide::Sente),
		.movedPieceAfter = Piece(PieceType::Fu, PlayerSide::Sente)
	};

	Move m2 = {
		.from = Position(8, 3),
		.to = Position(8, 4),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = Piece(PieceType::Fu, PlayerSide::Gote),
		.movedPieceAfter = Piece(PieceType::Fu, PlayerSide::Gote)
	};

	Move m3 = {
		.from = Position(2, 7),
		.to = Position(2, 6),
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