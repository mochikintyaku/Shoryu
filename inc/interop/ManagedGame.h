#pragma once
#include "TypeConverter.h"

namespace shoryu::interop
{
	public ref class ManagedGame
	{
	public:
		ManagedGame();
		~ManagedGame();
		!ManagedGame();

		void NewGame();
		void Clear();

		ManagedPieceLayout GetLayout();
		ManagedPieceCode GetPieceCodeAt(ManagedPosition pos);
		ManagedHandCounts GetHandCounts();
		ManagedPlayerSide GetCurrentPlayer();
		int GetMoveCount();

		array<ManagedPosition>^ GetLegalMoves(ManagedPosition from);

		void ExecuteNormalMove(ManagedPosition from, ManagedPosition to);
		void ExecutePromotionMove(ManagedPosition from, ManagedPosition to);
		void ExecuteDropMove(ManagedPosition to, ManagedPieceCode pc);

		void UndoLastMove();
		bool CanUndo();

		void UndoMultipleMoves(int count);

	private:
		System::IntPtr game_;
	};
}
