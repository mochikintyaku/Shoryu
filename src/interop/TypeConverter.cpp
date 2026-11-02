#include "interop/TypeConverter.h"

namespace shoryu::interop
{
	ManagedPosition TypeConverter::ToManaged(shoryu::core::Position pos)
	{
		return ManagedPosition(pos.suji_, pos.dan_);
	}

	ManagedPieceCode TypeConverter::ToManaged(shoryu::core::PieceCode pc)
	{
		return static_cast<ManagedPieceCode>(static_cast<int>(pc));
	}

	ManagedPlayerSide TypeConverter::ToManaged(shoryu::core::PlayerSide side)
	{
		return static_cast<ManagedPlayerSide>(static_cast<int>(side));
	}


	shoryu::core::Position TypeConverter::ToNative(ManagedPosition pos)
	{
		return shoryu::core::Position(pos.Suji, pos.Dan);
	}

	shoryu::core::PieceCode TypeConverter::ToNative(ManagedPieceCode pc)
	{
		return static_cast<shoryu::core::PieceCode>(static_cast<int>(pc));
	}
}