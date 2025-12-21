#pragma once
#include "Types.h"
#include "Piece.h"
#include <optional>

namespace shoryu::core
{
	struct Move
	{
		const std::optional<Position> from;	// 移動元
		const Position to;	// 移動先
		const std::optional<Piece> capturedPiece; // 取った駒(なければnullopt)
		const std::optional<Piece> movedPieceBefore; // 移動前の駒
		const Piece movedPieceAfter;  // 移動後の駒(成っていれば成った後の駒)

		// 完全コンストラクタ
		Move(std::optional<Position> from_,
		     Position to_,
		     std::optional<Piece> capturedPiece_,
		     std::optional<Piece> movedPieceBefore_,
		     Piece movedPieceAfter_)
			: from(from_)
			, to(to_)
			, capturedPiece(capturedPiece_)
			, movedPieceBefore(movedPieceBefore_)
			, movedPieceAfter(movedPieceAfter_)
		{
		}
	};
}