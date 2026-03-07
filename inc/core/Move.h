#pragma once
#include "Types.h"
#include <optional>

namespace shoryu::core
{
	struct Move
	{
		const std::optional<Position> from;	// 移動元
		const Position to;	// 移動先
		const PieceCode capturedPiece; // 取った駒(なければPieceCode::Empty)
		const PieceCode movedPieceBefore; // 移動前の駒
		const PieceCode movedPieceAfter;  // 移動後の駒(成っていれば成った後の駒)

		// 完全コンストラクタ
		Move(std::optional<Position> from_,
		     Position to_,
		     PieceCode capturedPiece_,
		     PieceCode movedPieceBefore_,
		     PieceCode movedPieceAfter_)
			: from(from_)
			, to(to_)
			, capturedPiece(capturedPiece_)
			, movedPieceBefore(movedPieceBefore_)
			, movedPieceAfter(movedPieceAfter_)
		{
		}
	};
}