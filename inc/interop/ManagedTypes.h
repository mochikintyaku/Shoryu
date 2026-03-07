#pragma once

namespace shoryu::interop
{
	public value struct ManagedPosition
	{
		int Suji;
		int Dan;

		ManagedPosition(int suji, int dan);
	};

	public enum class ManagedPieceType
	{
		Fu = 0,  // •à  =0
		Kyo,     // Ô
		Kei,     // Œj”n
		Gin,     // ‹â«
		Kin,     // ‹à«
		Kaku,    // Šps
		Hisha,   // ”òÔ
		Ou,      // ‰¤«
		Gyoku,   // ‹Ê«
		Tokin,   // ‚Æ‹à  =9
		NariKyo, // ¬
		NariKei, // ¬Œj
		NariGin, // ¬‹â
		Uma,     // ”n
		Ryu      // —³
	};

	public enum class ManagedPlayerSide
	{
		Sente = 0,
		Gote
	};

	public value struct ManagedViewSquare
	{
		bool HasPiece;
		ManagedPieceType PieceType;
		ManagedPlayerSide Owner; // HasPiece == false ‚Ì‚Æ‚«‚Í–³‹‚³‚ê‚é‘z’è
	};

	public value struct ManagedViewHand
	{
		array<int>^ Hands; // array‚Ìindex‚ÍManagedPieceType‚Ì’è‹`‡‚É‘Î‰

		ManagedViewHand(array<int>^ hands);
	};

	public value struct ManagedViewBoardLayout
	{
		array<ManagedViewSquare, 2>^ Board;

		ManagedViewBoardLayout(array<ManagedViewSquare, 2>^ board);
	};
}
