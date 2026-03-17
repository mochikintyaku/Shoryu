#pragma once

namespace shoryu::interop
{
	public value struct ManagedPosition
	{
		int Suji;
		int Dan;

		ManagedPosition(int suji, int dan);
	};

	// core::PieceCode と同じ値を持つ（所有者込み: 先手=正 / 後手=負）
	public enum class ManagedPieceCode : int
	{
		Empty = 0,

		SenteFu = 1,
		SenteKyo = 2,
		SenteKei = 3,
		SenteGin = 4,
		SenteKin = 5,
		SenteKaku = 6,
		SenteHisya = 7,
		Ou = 8,

		SenteTokin = 11,
		SenteNariKyo = 12,
		SenteNariKei = 13,
		SenteNariGin = 14,
		SenteUma = 16,
		SenteRyu = 17,

		GoteFu = -1,
		GoteKyo = -2,
		GoteKei = -3,
		GoteGin = -4,
		GoteKin = -5,
		GoteKaku = -6,
		GoteHisya = -7,
		Gyoku = -8,

		GoteTokin = -11,
		GoteNariKyo = -12,
		GoteNariKei = -13,
		GoteNariGin = -14,
		GoteUma = -16,
		GoteRyu = -17
	};

	public value struct ManagedPieceLayout
	{
		literal int BoardSize = 9;

		// [row, col] の 9x9（core::PieceLayout と同等）
		array<ManagedPieceCode, 2>^ Board;

		ManagedPieceLayout(array<ManagedPieceCode, 2>^ board);
	};

	public value struct ManagedHandCounts
	{
		literal int NumHandPieceType = 7;
		literal int CountsLength = NumHandPieceType * 2;

		// 長さ=14（0..6:先手 歩香桂銀金角飛 / 7..13:後手 歩香桂銀金角飛）
		array<int>^ Counts;

		ManagedHandCounts(array<int>^ counts);
	};

	public enum class ManagedPlayerSide
	{
		Sente = 1,
		Gote = -1
	};
}
