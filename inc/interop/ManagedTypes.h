#pragma once

namespace shoryu::interop
{
	public value struct ManagedPosition
	{
		int Suji;
		int Dan;

		ManagedPosition(int suji, int dan);
	};

	public enum class ManagedPieceCode : int
	{
		Empty = 0,
		// 先手の駒
		SenteFu = 1,
		SenteKyo = 2,
		SenteKei = 3,
		SenteGin = 4,
		SenteKin = 5,
		SenteKaku = 6,
		SenteHisya = 7,
		Ou = 8,
		SenteTokin = 9,
		SenteNariKyo = 10,
		SenteNariKei = 11,
		SenteNariGin = 12,
		SenteUma = 13,
		SenteRyu = 14,
		// 後手の駒
		GoteFu = 15,
		GoteKyo = 16,
		GoteKei = 17,
		GoteGin = 18,
		GoteKin = 19,
		GoteKaku = 20,
		GoteHisya = 21,
		Gyoku = 22,
		GoteTokin = 23,
		GoteNariKyo = 24,
		GoteNariKei = 25,
		GoteNariGin = 26,
		GoteUma = 27,
		GoteRyu = 28
	};

	public enum class ManagedPlayerSide
	{
		Sente = 0,
		Gote = 1
	};
}
