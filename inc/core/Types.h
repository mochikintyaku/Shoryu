#pragma once
#include <map>
#include <vector>
#include <array>

namespace shoryu::core
{
    struct Position
    {
        int suji_;  // x座標
        int dan_;   // y座標

        Position(int suji, int dan);

        // 比較演算子を追加
        bool operator==(const Position& other) const;
        bool operator !=(const Position& other) const;
    };

    enum class PieceCode : int
    {
        Empty = 0, //空マスを表すコード

        SenteFu = 1,
        SenteKyo = 2,
        SenteKei = 3,
        SenteGin = 4,
        SenteKin = 5,
        SenteKaku = 6,
        SenteHisya = 7,
        Ou = 8,     //先手が王
        SenteTokin = 11,  //成りごまは駒コードに10を足す事で表す
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


	inline constexpr int BoardSize = 9;        // 盤面の一辺のサイズ（9x9）
	inline constexpr int NumHandPieceType = 7; // Hand用（駒台に登場する）駒の種類数

    typedef std::array<std::array<PieceCode, BoardSize>, BoardSize> PieceLayout;
}