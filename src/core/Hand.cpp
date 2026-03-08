#include "core/Hand.h"
#include "core/PieceTraits.h"

namespace shoryu::core
{
	Hand::Hand()
		: pieces_()
	{
	}

	void Hand::add(PieceCode pc)
	{
		assert(isHandPiece(pc) && "Hand::add(pc): pc must be a hand piece");
		if (!isHandPiece(pc))
			return;

		pc = toHandKey(pc);
		pieces_[pc]++;
	}

	void Hand::remove(PieceCode pc)
	{
		assert(isHandPiece(pc) && "Hand::remove(pc): pc must be a hand piece");
		if (!isHandPiece(pc))
			return;

		pc = toHandKey(pc);

		auto it = pieces_.find(pc);
		assert(it != pieces_.end() && "Hand::remove(pc): piece not found in hand");
		if (it == pieces_.end())
			return;

		assert(it->second > 0 && "Hand::remove(pc): piece count must be > 0");
		if (it->second <= 0)
			return;

		it->second--;
	}

	int Hand::count(PieceCode pc) const
	{
		assert(isHandPiece(pc) && "Hand::count(pc): pc must be a hand piece");
		if (!isHandPiece(pc))
			return 0;

		pc = toHandKey(pc);
		auto it = pieces_.find(pc);
		return (it != pieces_.end()) ? it->second : 0;
	}

	bool Hand::has(PieceCode pc) const
	{
		return count(pc) > 0;
	}
}
