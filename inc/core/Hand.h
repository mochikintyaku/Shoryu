// 持ち駒を管理するクラス
#pragma once
#include "Types.h"
#include <array>

namespace shoryu::core
{
	class Hand
	{
	public:
		Hand();
		~Hand() = default;

		// 成り駒が渡された場合は自動的に不成に戻して持ち駒化する。
		void add(PieceCode pc);
		void remove(PieceCode pc);
		int count(PieceCode pc) const;
		bool has(PieceCode pc) const;
		void clear();

		const std::array<int, NumPieceType>& getAllCounts() const;

	private:
		std::array<int, NumPieceType> counts_;
	};
}