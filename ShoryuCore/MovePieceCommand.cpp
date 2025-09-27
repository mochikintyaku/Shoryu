#include "MovePieceCommand.h"

#include <stdexcept>

namespace shoryu::core
{
	MovePieceCommand::MovePieceCommand(Board& board, Position from, Position to)
		:board_(board), from_(from), to_(to), removeCommand_(std::nullopt), dropCommand_(std::nullopt), executed_(false)
	{ }

	void MovePieceCommand::execute()
	{
		if (executed_)
		{
			throw std::logic_error("DropPieceCommand: Already executed.");
		}

		removeCommand_.emplace(board_, from_);
		auto& remove = removeCommand_.value();
		remove.execute();
		auto piece = remove.removedPiece();
		dropCommand_.emplace(board_, to_, piece);
		auto& drop = dropCommand_.value();
		drop.execute();

		executed_ = true;
	}

	void MovePieceCommand::undo()
	{
		if (executed_ == false)
		{
			throw std::logic_error("DropPieceCommand: Hasn't executed yet.");
		}

		auto& remove = removeCommand_.value();
		auto& drop = dropCommand_.value();

		drop.undo();
		remove.undo();

		executed_ = false;
	}
}