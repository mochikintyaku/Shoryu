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

		// ���̃N���X�𐶐����Ă���execute()�����s����Ԃ�
		// Board�������ς�����\��������̂ŁA
		// ���s���O�ɑ���O�̃}�X�̏�Ԃ��擾����B
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
		// execute()���s��łȂ��ƁApre_piece_�̒l���m�肵�Ȃ�
		if (executed_ == false)
		{
			throw std::logic_error("DropPieceCommand: Hasn't executed yet.");
		}

		return pre_piece_;
	}
}
