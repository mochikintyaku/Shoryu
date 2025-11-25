#include "core/Hand.h"

namespace shoryu::core
{
	Hand::Hand()
		: pieces_()
	{
	}

	void Hand::addPiece(PieceType type)
	{
		pieces_[type]++;
	}

	void Hand::removePiece(PieceType type)
	{
		auto it = pieces_.find(type);
		if (it != pieces_.end() && it->second > 0)
		{
			it->second--;
		}
	}

	int Hand::getPieceCount(PieceType type) const
	{
		auto it = pieces_.find(type);
		if (it != pieces_.end())
		{
			return it->second;
		}
		return 0;
	}

	bool Hand::hasPiece(PieceType type) const
	{
		auto it = pieces_.find(type);
		return (it != pieces_.end() && it->second > 0);
	}
}
