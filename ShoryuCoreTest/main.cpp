#include <iostream>
#include "utils.h"
#include "Board.h"
#include "MoveManager.h"
#include <optional>

int main()
{
	using namespace shoryu::core;
	Board board;
	MoveManager manager(board);

	Move m1 = {
		.from = std::nullopt,
		.to = Position(Suji::Suji7, Dan::Dan6),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = std::nullopt,
		.movedPieceAfter = Piece(PieceType::Fu, PlayerSide::Sente)
	};

	Move m2 = {
		.from = std::nullopt,
		.to = Position(Suji::Suji6, Dan::Dan9),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = std::nullopt,
		.movedPieceAfter = Piece(PieceType::Kin, PlayerSide::Gote)
	};

	Move m3 = {
		.from = Position(Suji::Suji7, Dan::Dan6),
		.to = Position(Suji::Suji8, Dan::Dan5),
		.capturedPiece = std::nullopt,
		.movedPieceBefore = Piece(PieceType::Fu, PlayerSide::Sente),
		.movedPieceAfter = Piece(PieceType::Tokin, PlayerSide::Sente)
	};

	show(board.getLayout());
	manager.execute(m1);
	show(board.getLayout());
	manager.execute(m2);
	show(board.getLayout());
	manager.execute(m3);
	show(board.getLayout());
	manager.undoLast();
	show(board.getLayout());
	manager.undoLast();
	show(board.getLayout());
	manager.undoLast();
	show(board.getLayout());

	return 0;
}