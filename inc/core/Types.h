#pragma once
#include <map>
#include <vector>
#include "ShoryuCoreExport.h"

namespace shoryu::core
{
    struct SHORYU_API Position
    {
        int suji_;  // xç¿ïW
        int dan_;   // yç¿ïW

        Position(int suji, int dan);

        // î‰ärââéZéqÇí«â¡
        bool operator==(const Position& other) const;
        bool operator !=(const Position& other) const;
    };

    enum class PieceType
    {
        Fu = 0,  // ï‡  =0
        Kyo,     // çÅé‘
        Kei,     // åjîn
        Gin,     // ã‚è´
        Kin,     // ã‡è´
        Kaku,    // äpçs
        Hisha,   // îÚé‘
        Ou,      // â§è´
        Gyoku,   // ã è´
        Tokin,   // Ç∆ã‡  =9
        NariKyo, // ê¨çÅ
        NariKei, // ê¨åj
        NariGin, // ê¨ã‚
        Uma,     // în
        Ryu      // ó≥
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
        int dx;
        int dy;
    };

    struct slideDir
    {
        int dx;
        int dy;
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
}