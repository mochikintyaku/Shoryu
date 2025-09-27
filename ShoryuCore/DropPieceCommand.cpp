#include "DropPieceCommand.h"
#include "Board.h"
#include <stdexcept>


namespace shoryu
{
	DropPieceCommand::DropPieceCommand(Board& board, Position pos, std::optional<Piece> post)
		: board_(board), pos_(pos), pre_piece_(std::nullopt), post_piece_(post), executed_(false)
	{ }

	void DropPieceCommand::execute()
	{
		if (executed_)
		{
			throw std::logic_error("DropPieceCommand: Already executed.");
		}

		// このクラスを生成してからexecute()を実行する間に
		// Boardが書き変えられる可能性があるので、
		// 実行直前に操作前のマスの状態を取得する。
		pre_piece_ = board_.getPiece(pos_);
		board_.setPiece(pos_, post_piece_);

		executed_ = true;
	}

	void DropPieceCommand::undo()
	{
		if (executed_ == false)
		{
			throw std::logic_error("DropPieceCommand: Hasn't executed yet.");
		}

		board_.setPiece(pos_, pre_piece_);

		executed_ = false;
	}

	std::optional<Piece> DropPieceCommand::PrePiece() const
	{
		// execute()実行後でないと、pre_piece_の値が確定しない
		if (executed_ == false)
		{
			throw std::logic_error("DropPieceCommand: Hasn't executed yet.");
		}

		return pre_piece_;
	}
}
