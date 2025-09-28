#pragma once
#include "ShoryuParams.h"
#include "Piece.h"
#include <optional>

namespace shoryu::core
{
	struct Move
	{
		Position from;	// �ړ���
		Position to;	// �ړ���
		std::optional<Piece> capturedPiece; // �������(�Ȃ����nullopt)
		Piece movedPieceBefore; // �ړ��O�̋�
		Piece movedPieceAfter;  // �ړ���̋�(�����Ă���ΐ�������̋�)
	};
}
