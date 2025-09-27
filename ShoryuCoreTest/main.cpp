#include <iostream>
#include "utils.h"
#include "Board.h"
#include "CommandManager.h"
#include "DropPieceCommand.h"
#include "RemovePieceCommand.h"
#include "PromotePieceCommand.h"
#include "MovePieceCommand.h"
#include <memory>

int main()
{
	using namespace shoryu::core;
	Board board;
	CommandManager manager;

	auto cmd1 = std::make_unique<DropPieceCommand>(board, Position(Suji::Suji1, Dan::Dan3), Piece(PieceType::Fu, PlayerSide::Sente));
	auto cmd2 = std::make_unique<DropPieceCommand>(board, Position(Suji::Suji6, Dan::Dan9), Piece(PieceType::Kin, PlayerSide::Sente));
	auto cmd3 = std::make_unique<PromotePieceCommand>(board, Position(Suji::Suji1, Dan::Dan3));
	auto cmd4 = std::make_unique<DropPieceCommand>(board, Position(Suji::Suji1, Dan::Dan3), Piece(PieceType::Kaku, PlayerSide::Gote));
	auto cmd5 = std::make_unique<RemovePieceCommand>(board, Position(Suji::Suji1, Dan::Dan3));
	auto cmd6 = std::make_unique<MovePieceCommand>(board, Position(Suji::Suji6, Dan::Dan9), Position(Suji::Suji5, Dan::Dan8));

	show(board.getLayout());
	manager.invoke(std::move(cmd1));
	show(board.getLayout());
	manager.invoke(std::move(cmd2));
	show(board.getLayout());
	manager.invoke(std::move(cmd3));
	show(board.getLayout());
	manager.invoke(std::move(cmd4));
	show(board.getLayout());
	manager.invoke(std::move(cmd5));
	show(board.getLayout());
	manager.invoke(std::move(cmd6));
	show(board.getLayout());
	manager.undoLast();
	show(board.getLayout());
	manager.undoLast();
	show(board.getLayout());
	manager.undoLast();
	show(board.getLayout());

	return 0;
}