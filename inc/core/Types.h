#pragma once
#include <map>
#include <vector>
#include "ShoryuCoreExport.h"

namespace shoryu::core
{
    struct SHORYU_API Position
    {
        int suji_;  // x座標
        int dan_;   // y座標

        Position(int suji, int dan);

        // 比較演算子を追加
        bool operator==(const Position& other) const;
        bool operator !=(const Position& other) const;
    };

    enum class PieceType
    {
        Fu = 0,  // 歩  =0
        Kyo,     // 香車
        Kei,     // 桂馬
        Gin,     // 銀将
        Kin,     // 金将
        Kaku,    // 角行
        Hisha,   // 飛車
        Ou,      // 王将
        Gyoku,   // 玉将
        Tokin,   // と金  =9
        NariKyo, // 成香
        NariKei, // 成桂
        NariGin, // 成銀
        Uma,     // 馬
        Ryu      // 竜
    };

    inline const std::map<PieceType, PieceType> PromoteMap =
    {
        {PieceType::Fu, PieceType::Tokin},
        {PieceType::Kyo, PieceType::NariKyo},
        {PieceType::Kei, PieceType::NariKei},
        {PieceType::Gin, PieceType::NariGin},
        {PieceType::Kaku, PieceType::Uma},
        {PieceType::Hisha, PieceType::Ryu}
    };

    inline const std::map<PieceType, PieceType> DemoteMap =
    {
        {PieceType::Tokin, PieceType::Fu},
        {PieceType::NariKyo, PieceType::Kyo},
        {PieceType::NariKei, PieceType::Kei},
        {PieceType::NariGin, PieceType::Gin},
        {PieceType::Uma, PieceType::Kaku},
        {PieceType::Ryu, PieceType::Hisha}
    };

    struct step
    {
        const int dx;
        const int dy;
    };

    struct slideDir
    {
        const int dx;
        const int dy;
    };

    struct MoveSpec
    {
        std::vector<step> stepMoves;
        std::vector<slideDir> slideMoves;
    };

    enum class PlayerSide
    {
        Sente = 0,
        Gote
    };

	//---- 以下、定数定義 ----//
	inline constexpr int BoardSize = 9;        // 盤面の一辺のサイズ（9x9）
	inline constexpr int NumHandPieceType = 7; // Hand用（駒台に登場する）駒の種類数
}