#pragma once
#include <map>
#include "PieceTraits.h"
#include "Types.h"

namespace shoryu::core
{
	// 先手基準の定義（dy=-1 が「前」）
	inline const std::map<PieceCode, MoveSpec> senteMoveTable =
	{
		{
			PieceCode::SenteFu, {
			.stepMoves = { {0, -1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteKyo, {
			.stepMoves = {},
			.slideMoves = { {0, -1} }
			}
		},
		{
			PieceCode::SenteKei, {
			.stepMoves = { {-1, -2}, {1, -2} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteGin, {
			.stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteKin, {
			.stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteKaku, {
			.stepMoves = {},
			.slideMoves = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} }
			}
		},
		{
			PieceCode::SenteHisya, {
			.stepMoves = {},
			.slideMoves = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }
			}
		},
		{
			PieceCode::Ou, {
			.stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1}, {-1, 1}, {1, 1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteTokin, {
			.stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteNariKyo, {
			.stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteNariKei, {
			.stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteNariGin, {
			.stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
			.slideMoves = {}
			}
		},
		{
			PieceCode::SenteUma, {
			.stepMoves = { {0, -1}, {-1, 0}, {1, 0}, {0, 1} },
			.slideMoves = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} }
			}
		},
		{
			PieceCode::SenteRyu, {
			.stepMoves = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} },
			.slideMoves = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }
			}
		},
	};

	inline MoveSpec flipMoveSpecY(const MoveSpec& src)
	{
		MoveSpec dst;
		dst.stepMoves.reserve(src.stepMoves.size());
		for (const auto& s : src.stepMoves)
			dst.stepMoves.push_back({ s.dx, -s.dy });

		dst.slideMoves.reserve(src.slideMoves.size());
		for (const auto& d : src.slideMoves)
			dst.slideMoves.push_back({ d.dx, -d.dy });

		return dst;
	}

	// pc が後手駒なら dy を反転した MoveSpec を返す（先手基準テーブルを使い回す）
	inline MoveSpec getMoveTable(PieceCode pc)
	{
		if (isEmpty(pc))
			return {};

		const bool gote = isGotePiece(pc);
		const PieceCode senteKey = gote ? flipOwner(pc) : pc;

		auto it = senteMoveTable.find(senteKey);
		if (it == senteMoveTable.end())
			return {};

		return gote ? flipMoveSpecY(it->second) : it->second;
	}
}