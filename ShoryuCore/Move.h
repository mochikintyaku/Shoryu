#pragma once
#include "Types.h"
#include "Piece.h"
#include <optional>

namespace shoryu::core
{
	struct Move
	{
		std::optional<Position> from;	// �ړ���
		Position to;	// �ړ���
		std::optional<Piece> capturedPiece; // �������(�Ȃ����nullopt)
		std::optional<Piece> movedPieceBefore; // �ړ��O�̋�
		Piece movedPieceAfter;  // �ړ���̋�(�����Ă���ΐ�������̋�)
	};
}