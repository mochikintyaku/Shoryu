#include "core/Hand.h"

namespace shoryu::core
{
	Hand::Hand()
		: pieces_()
	{
	}

	bool Hand::isHandKind(PieceCode pc)
	{
		// 盤上から持ち駒になり得るのは「歩香桂銀金角飛」のみ（王/玉は除外）
		switch (pc)
		{
		case PieceCode::SenteFu:
		case PieceCode::SenteKyo:
		case PieceCode::SenteKei:
		case PieceCode::SenteGin:
		case PieceCode::SenteKin:
		case PieceCode::SenteKaku:
		case PieceCode::SenteHisya:
		case PieceCode::GoteFu:
		case PieceCode::GoteKyo:
		case PieceCode::GoteKei:
		case PieceCode::GoteGin:
		case PieceCode::GoteKin:
		case PieceCode::GoteKaku:
		case PieceCode::GoteHisya:
			return true;
		default:
			return false;
		}
	}

	PieceCode Hand::normalizeKey(PieceCode pc)
	{
		// Empty は呼び出し側で弾く想定
		// 成り駒は「元の駒 + 10（符号同じ）」規則なので 10 引いて戻す
		const int v = static_cast<int>(pc);
		const int absV = (v < 0) ? -v : v;
		if (absV >= 11)
		{
			const int sign = (v < 0) ? -1 : 1;
			pc = static_cast<PieceCode>(v - sign * 10);
		}
		return pc;
	}

	void Hand::add(PieceCode pc)
	{
		if (pc == PieceCode::Empty)
			return;

		pc = normalizeKey(pc);
		if (!isHandKind(pc))
			return;

		pieces_[pc]++;
	}

	void Hand::remove(PieceCode pc)
	{
		if (pc == PieceCode::Empty)
			return;

		pc = normalizeKey(pc);
		if (!isHandKind(pc))
			return;

		auto it = pieces_.find(pc);
		if (it != pieces_.end() && it->second > 0)
		{
			it->second--;
		}
	}

	int Hand::count(PieceCode pc) const
	{
		if (pc == PieceCode::Empty)
			return 0;

		pc = normalizeKey(pc);
		if (!isHandKind(pc))
			return 0;

		auto it = pieces_.find(pc);
		return (it != pieces_.end()) ? it->second : 0;
	}

	bool Hand::has(PieceCode pc) const
	{
		return count(pc) > 0;
	}
}
