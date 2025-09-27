#include "PromotePieceCommand.h"
#include "Board.h"
#include <stdexcept>

namespace shoryu::core
{
	PromotePieceCommand::PromotePieceCommand(Board& board, Position pos)
		: board_(board), pos_(pos), normal_piece_(std::nullopt), promoted_piece_(std::nullopt)
	{ }

	void PromotePieceCommand::execute()
	{
		if (board_.getPiece(pos_).has_value() == false)
		{
			throw std::runtime_error("PromotePieceCommand: No piece found at the given position.");
		}

		auto piece = board_.getPiece(pos_);
		if (canPromote(piece.value()) == false)
		{
			throw std::runtime_error("PromotePieceCommand: This piece cannot promote.");
		}

		// ‘€ì‘O‚Ì‹î‚ð‹L˜^
		normal_piece_ = piece;

		auto promotedPieceType = PromoteMap.find(piece.value().pieceType())->second;
		promoted_piece_ = Piece(promotedPieceType, piece.value().owner());
		board_.setPiece(pos_, promoted_piece_);
	}

	void PromotePieceCommand::undo()
	{
		board_.setPiece(pos_, normal_piece_);
	}
}