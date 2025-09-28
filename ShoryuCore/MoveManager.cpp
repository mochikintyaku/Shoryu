#include "MoveManager.h"
#include "Board.h"

namespace shoryu::core
{
	MoveManager::MoveManager(Board& board)
		:stack_(), board_(board)
	{ }

	void MoveManager::execute(Move move)
	{
		// 1. �ړ����ifrom�j�������폜
		// 2. �ړ���ito�j�ɋ��z�u
		// 3. ����������΁A������ɒǉ�
		if (move.from.has_value())
		{
			board_.setPiece(move.from.value(), std::nullopt);
		}
		board_.setPiece(move.to, move.movedPieceAfter);
		if (move.capturedPiece.has_value())
		{
			// ������ɒǉ����鏈���������ɏ���
			// �Ⴆ�΁APlayer�N���X��addCapturedPiece���\�b�h���Ăяo���Ȃ�
		}

		stack_.push(move);
	}

	void MoveManager::undoLast()
	{
		if (stack_.empty())
			return;

		Move move = stack_.top();
		stack_.pop();

		// 1. ���������������폜�i��������������΁j
		// 2. �ړ���(to)�̋���폜�i�������Ă���΁A�������ɖ߂��j
		// 3. �ړ���(from)�̂ɋ��z�u
		if (move.capturedPiece.has_value())
		{
			// �������폜���鏈���������ɏ���
			// �Ⴆ�΁APlayer�N���X��removeCapturedPiece���\�b�h���Ăяo���Ȃ�
		}
		if (move.capturedPiece.has_value())
		{
			board_.setPiece(move.to, move.capturedPiece);
		}
		else
		{
			board_.setPiece(move.to, std::nullopt);
		}
		if (move.from.has_value())
		{
			board_.setPiece(move.from.value(), move.movedPieceBefore);
		}
	}
}
