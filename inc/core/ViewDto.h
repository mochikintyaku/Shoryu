#pragma once

#include "Types.h"
#include "ShoryuCoreExport.h"
#include <array>

namespace shoryu::core
{

    struct SHORYU_API ViewSquare
    {
        bool hasPiece = false;
        PlayerSide owner = PlayerSide::Sente;   // hasPiece == false ‚Ì‚Æ‚«‚Í–³‹‚³‚ê‚é‘z’è
        PieceType pieceType = PieceType::Fu;    // “¯ã
    };

    using ViewBoardLayout = std::array<std::array<ViewSquare, BoardSize>, BoardSize>;

    struct SHORYU_API ViewHand
    {
		std::array<int, NumHandPieceType> hands{ 0 }; // array‚Ìindex‚ÍPieceType‚Ì’è‹`‡‚É‘Î‰
    };

} // namespace shoryu::core