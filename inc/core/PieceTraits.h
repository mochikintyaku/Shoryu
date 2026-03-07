#pragma once
#include "Types.h"
#include <cassert>

namespace shoryu::core
{
	// --- basic ---
	inline constexpr bool isEmpty(PieceCode pc)
	{
		return pc == PieceCode::Empty;
	}

	inline constexpr bool hasPiece(PieceCode pc)
	{
		return pc != PieceCode::Empty;
	}

	inline constexpr bool isSentePiece(PieceCode pc)
	{
		return static_cast<int>(pc) > 0;
	}

	inline constexpr bool isGotePiece(PieceCode pc)
	{
		return static_cast<int>(pc) < 0;
	}

	inline constexpr PlayerSide ownerOf(PieceCode pc)
	{
		// 前提: Empty ではない
		assert(pc != PieceCode::Empty && "ownerOf(pc): pc must not be Empty");
		return isSentePiece(pc) ? PlayerSide::Sente : PlayerSide::Gote;
	}

	inline constexpr PieceCode flipOwner(PieceCode pc)
	{
		return static_cast<PieceCode>(-static_cast<int>(pc));
	}

	// --- promotion ---
	inline constexpr bool isPromotedPiece(PieceCode pc)
	{
		const int v = static_cast<int>(pc);
		const int absV = (v < 0) ? -v : v;
		return absV >= 11;
	}

	inline constexpr PieceCode demote(PieceCode pc)
	{
		if (isEmpty(pc) || !isPromotedPiece(pc))
			return pc;

		const int v = static_cast<int>(pc);
		const int sign = (v < 0) ? -1 : 1;
		return static_cast<PieceCode>(v - sign * 10);
	}

	inline constexpr bool canPromotePiece(const PieceCode pc)
	{
		if (isEmpty(pc))
			return false;

		// すでに成り駒なら成れない
		if (isPromotedPiece(pc))
			return false;

		// 「歩香桂銀角飛」だけ成れる
		switch (pc)
		{
		case PieceCode::SenteFu:
		case PieceCode::SenteKyo:
		case PieceCode::SenteKei:
		case PieceCode::SenteGin:
		case PieceCode::SenteKaku:
		case PieceCode::SenteHisya:
		case PieceCode::GoteFu:
		case PieceCode::GoteKyo:
		case PieceCode::GoteKei:
		case PieceCode::GoteGin:
		case PieceCode::GoteKaku:
		case PieceCode::GoteHisya:
			return true;
		default:
			return false;
		}
	}

	inline constexpr PieceCode promote(const PieceCode pc)
	{
		if (!canPromotePiece(pc))
			return pc;

		const int v = static_cast<int>(pc);
		const int sign = (v < 0) ? -1 : 1;
		return static_cast<PieceCode>(v + sign * 10);
	}

	// --- side relation ---
	inline constexpr bool isAlly(PieceCode a, PieceCode b)
	{
		return hasPiece(a) && hasPiece(b) && (isSentePiece(a) == isSentePiece(b));
	}

	inline constexpr bool isEnemy(PieceCode a, PieceCode b)
	{
		return hasPiece(a) && hasPiece(b) && (isSentePiece(a) != isSentePiece(b));
	}

	// --- hand helpers ---
	// 盤上の駒が「持ち駒として存在し得る」種類か（成りは demote して判定）
	inline constexpr bool isHandPiece(PieceCode pc)
	{
		if (isEmpty(pc))
			return false;

		const PieceCode base = demote(pc);
		switch (base)
		{
		case PieceCode::SenteFu:
		case PieceCode::SenteKyo:
		case PieceCode::SenteKei:
		case PieceCode::SenteGin:
		case PieceCode::SenteKin:
		case PieceCode::SenteKaku:
		case PieceCode::SenteHisya:
		case PieceCode::GoteFu:
		case PieceCode::GoteKyo:
		case PieceCode::GoteKei:
		case PieceCode::GoteGin:
		case PieceCode::GoteKin:
		case PieceCode::GoteKaku:
		case PieceCode::GoteHisya:
			return true;
		default:
			return false;
		}
	}

	// 元の PieceCode を「持ち駒として管理するキー（不成）」へ正規化
	inline constexpr PieceCode toHandKey(PieceCode pc)
	{
		return demote(pc);
	}
}