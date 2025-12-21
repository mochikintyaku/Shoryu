#pragma once
#include <map>
#include <vector>
#include "ShoryuCoreExport.h"

namespace shoryu::core
{
    struct SHORYU_API Position
    {
        int suji_;  // x•ûŒü
        int dan_;   // y•ûŒü

        Position(int suji, int dan);

        // ”äŠr‰‰Zq‚ğ’Ç‰Á
        bool operator==(const Position& other) const;
        bool operator !=(const Position& other) const;
    };

    enum class PieceType
    {
        Fu = 0,  // •à•º  =0
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