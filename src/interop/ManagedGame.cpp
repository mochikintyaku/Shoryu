#include "interop/ManagedGame.h"
#include "core/Game.h"

namespace
{
	shoryu::core::Game* GetGame(System::IntPtr p)
	{
		return static_cast<shoryu::core::Game*>(p.ToPointer());
	}
}

namespace shoryu::interop
{
	ManagedGame::ManagedGame()
		: game_(System::IntPtr(new shoryu::core::Game()))
	{
	}

	ManagedGame::~ManagedGame()
	{
		this->!ManagedGame();
	}

	ManagedGame::!ManagedGame()
	{
		auto g = GetGame(game_);
		delete g;
		game_ = System::IntPtr::Zero;
	}

	void ManagedGame::NewGame()
	{
		GetGame(game_)->newGame();
	}

	void ManagedGame::Clear()
	{
		GetGame(game_)->clear();
	}

	ManagedPieceLayout ManagedGame::GetLayout()
	{
		return TypeConverter::ToManaged(GetGame(game_)->getLayout());
	}

	ManagedPieceCode ManagedGame::GetPieceCodeAt(ManagedPosition pos)
	{
		return TypeConverter::ToManaged(GetGame(game_)->getPieceCodeAt(TypeConverter::ToNative(pos)));
	}

	ManagedHandCounts ManagedGame::GetHandCounts()
	{
		return TypeConverter::ToManaged(GetGame(game_)->getHandCounts());
	}

	ManagedPlayerSide ManagedGame::GetCurrentPlayer()
	{
		return TypeConverter::ToManaged(GetGame(game_)->getCurrentPlayer());
	}

	int ManagedGame::GetMoveCount()
	{
		return static_cast<int>(GetGame(game_)->getMoveCount());
	}

	array<ManagedPosition>^ ManagedGame::GetLegalMoves(ManagedPosition from)
	{
		auto moves = GetGame(game_)->getLegalMoves(TypeConverter::ToNative(from));

		auto managed = gcnew array<ManagedPosition>(static_cast<int>(moves.size()));
		for (int i = 0; i < managed->Length; ++i)
		{
			managed[i] = TypeConverter::ToManaged(moves[static_cast<size_t>(i)]);
		}

		return managed;
	}

	void ManagedGame::ExecuteNormalMove(ManagedPosition from, ManagedPosition to)
	{
		GetGame(game_)->executeNormalMove(TypeConverter::ToNative(from), TypeConverter::ToNative(to));
	}

	void ManagedGame::ExecutePromotionMove(ManagedPosition from, ManagedPosition to)
	{
		GetGame(game_)->executePromotionMove(TypeConverter::ToNative(from), TypeConverter::ToNative(to));
	}

	void ManagedGame::ExecuteDropMove(ManagedPosition to, ManagedPieceCode pc)
	{
		GetGame(game_)->executeDropMove(TypeConverter::ToNative(to), TypeConverter::ToNative(pc));
	}

	void ManagedGame::UndoLastMove()
	{
		GetGame(game_)->undoLastMove();
	}

	bool ManagedGame::CanUndo()
	{
		return GetGame(game_)->canUndo();
	}

	void ManagedGame::UndoMultipleMoves(int count)
	{
		GetGame(game_)->undoMultipleMoves(count);
	}
}