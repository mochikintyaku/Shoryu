#include "RemovePieceCommand.h"
#include <stdexcept>

namespace shoryu
{
	RemovePieceCommand::RemovePieceCommand(Board& board, Position pos)
		: dropCommand(board, pos, std::nullopt), executed_(false)
	{ }

	void RemovePieceCommand::execute()
	{
		if (executed_)
		{
			throw std::logic_error("RemovePieceCommand: Already executed.");
		}

		dropCommand.execute();

		executed_ = true;
	}

	void RemovePieceCommand::undo()
	{
		if (executed_ == false)
		{
			throw std::logic_error("RemovePieceCommand: Hasn't executed yet.");
		}

		dropCommand.undo();
		
		executed_ = false;
	}

	std::optional<Piece> RemovePieceCommand::removedPiece() const
	{
		if (executed_ == false)
		{
			throw std::logic_error("RemovePieceCommand: Hasn't executed yet.");
		}

		return dropCommand.PrePiece();
	}
}
