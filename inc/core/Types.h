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
        SenteTokin = 9,  //成りごまは駒コードに10を足す事で表す
        SenteNariKyo = 10,
        SenteNariKei = 11,
        SenteNariGin = 12,
        SenteUma = 13,
        SenteRyu = 14,

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
        Gote = 1
    };


	inline constexpr int BoardSize = 9;        // 盤面の一辺のサイズ（9x9）
	inline constexpr int NumPieceType = 29;    // 駒の種類数
	inline constexpr int PromoteOffset = 8;     // 成り駒のコードは、通常駒のコードにこの値を足すことで表す
	inline constexpr int FlipOffset = 14;       // 後手駒のコードは、先手駒のコードにこの値を足すことで表す

    typedef std::array<std::array<PieceCode, BoardSize>, BoardSize> PieceLayout;
}