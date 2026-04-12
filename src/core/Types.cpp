#include "core/Types.h"

namespace shoryu::core
{
	Position::Position(int suji, int dan)
		: suji_(suji), dan_(dan)
	{
	}

	bool Position::operator==(const Position& other) const
	{
		return (this->suji_ == other.suji_) && (this->dan_ == other.dan_);
	}

	bool Position::operator!=(const Position& other) const
	{
		return !(*this == other);
	}
}
