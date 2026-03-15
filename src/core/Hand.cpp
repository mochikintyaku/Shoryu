#include "core/Hand.h"
#include "core/PieceTraits.h"

namespace shoryu::core
{
	Hand::Hand()
		: counts_{}
	{
	}

	void Hand::clear()
	{
		counts_.fill(0);
	}

	const std::array<int, NumHandPieceType * 2>& Hand::getAllCounts() const
	{
		return counts_;
	}

	void Hand::add(PieceCode pc)
	{
		assert(isHandPiece(pc) && "Hand::add(pc): pc must be a hand piece");
		if (!isHandPiece(pc))
			return;

		const int index = handPieceIndex(pc);
		counts_[index]++;
	}

	void Hand::remove(PieceCode pc)
	{
		assert(isHandPiece(pc) && "Hand::remove(pc): pc must be a hand piece");
		if (!isHandPiece(pc))
			return;

		const int index = handPieceIndex(pc);

		assert(counts_[index] > 0 && "Hand::remove(pc): piece count must be > 0");
		if (counts_[index] <= 0)
			return;

		counts_[index]--;
	}

	int Hand::count(PieceCode pc) const
	{
		assert(isHandPiece(pc) && "Hand::count(pc): pc must be a hand piece");
		if (!isHandPiece(pc))
			return 0;

		const int index = handPieceIndex(pc);
		return counts_[index];
	}

	bool Hand::has(PieceCode pc) const
	{
		return count(pc) > 0;
	}
}
