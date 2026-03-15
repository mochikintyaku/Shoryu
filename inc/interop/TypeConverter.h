#pragma once
#include "core/Types.h"
#include "ManagedTypes.h"

namespace shoryu::interop
{
	public ref class TypeConverter abstract sealed
	{
	public:
		static ManagedPosition ToManaged(shoryu::core::Position pos);
		static ManagedPieceCode ToManaged(shoryu::core::PieceCode pc);
		static ManagedPieceLayout ToManaged(const shoryu::core::PieceLayout& layout);
		static ManagedHandCounts ToManaged(const std::array<int, shoryu::core::NumHandPieceType * 2>& counts);

		static shoryu::core::Position ToNative(ManagedPosition pos);
		static shoryu::core::PieceCode ToNative(ManagedPieceCode pc);
	};
}