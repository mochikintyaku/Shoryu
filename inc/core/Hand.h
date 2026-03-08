// 持ち駒を管理するクラス
#pragma once
#include "Types.h"
#include <map>

namespace shoryu::core
{
	class Hand
	{
	public:
		Hand();
		~Hand() = default;

		// 所有者込み PieceCode（先手=正 / 後手=負）で管理する。
		// 成り駒が渡された場合は自動的に不成に戻して持ち駒化する。
		void add(PieceCode pc);
		void remove(PieceCode pc);
		int count(PieceCode pc) const;
		bool has(PieceCode pc) const;

	private:
		// キーは「所有者付き・不成の PieceCode」のみ
		std::map<PieceCode, int> pieces_;
	};
}