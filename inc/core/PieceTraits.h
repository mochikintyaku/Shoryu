#pragma once
#include "Types.h"
#include <cassert>

namespace shoryu::core
{
	constexpr bool InPieceCodeRange(PieceCode target, PieceCode lo, PieceCode hi)
	{
		return (lo <= target) && (target <= hi);
	}

	// --- basic ---
	inline constexpr bool isEmpty(PieceCode pc)
	{
		return pc == PieceCode::Empty;
	}

	inline constexpr bool isSentePiece(PieceCode pc)
	{
		return InPieceCodeRange(pc, PieceCode::SenteFu, PieceCode::SenteRyu);
	}

	inline constexpr bool isGotePiece(PieceCode pc)
	{
		return InPieceCodeRange(pc, PieceCode::GoteFu, PieceCode::GoteRyu);
	}

	inline constexpr PlayerSide ownerOf(PieceCode pc)
	{
		// 前提: Empty ではない
		assert(pc != PieceCode::Empty && "ownerOf(pc): pc must not be Empty");
		return isSentePiece(pc) ? PlayerSide::Sente : PlayerSide::Gote;
	}

	inline constexpr PieceCode flipOwner(PieceCode pc)
	{
		if (isSentePiece(pc))
		{
			return static_cast<PieceCode>(static_cast<int>(pc) + FlipOffset);

		}
		else
		{
			return static_cast<PieceCode>(static_cast<int>(pc) - FlipOffset);
		}
	}

	// --- promotion ---
	inline constexpr bool isPromotedPiece(PieceCode pc)
	{
		return (InPieceCodeRange(pc, PieceCode::SenteTokin, PieceCode::SenteRyu))||
			(InPieceCodeRange(pc, PieceCode::GoteTokin, PieceCode::GoteRyu));
	}

	inline constexpr PieceCode demote(PieceCode pc)
	{
		if (isEmpty(pc) || !isPromotedPiece(pc))
			return pc;

		int iPc = static_cast<int>(pc);
		iPc -= PromoteOffset;
		return static_cast<PieceCode>(iPc);
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

		int iPc = static_cast<int>(pc);
		iPc += PromoteOffset;
		return static_cast<PieceCode>(iPc);
	}

	// --- side relation ---
	inline constexpr bool isAlly(PieceCode a, PieceCode b)
	{
		if (isEmpty(a) || isEmpty(b))
			return false;

		return (isSentePiece(a) == isSentePiece(b));
	}

	inline constexpr bool isEnemy(PieceCode a, PieceCode b)
	{
		if (isEmpty(a) || isEmpty(b))
			return false;

		return (isSentePiece(a) != isSentePiece(b));
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
}