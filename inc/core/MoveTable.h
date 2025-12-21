#pragma once
#include <map>
#include "Types.h"

namespace shoryu::core
{
    inline static const std::map<PieceType, MoveSpec> moveTable =
    {
        {
            PieceType::Fu, {
            .stepMoves = { {0, -1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::Kyo, {
            .stepMoves = {},
            .slideMoves = { {0, -1} }
            }
        },
        {
            PieceType::Kei, {
            .stepMoves = { {-1, -2}, {1, -2} },
            .slideMoves = {}
            }
        },
        {
            PieceType::Gin, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::Kin, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::Kaku, {
            .stepMoves = {},
            .slideMoves = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} }
            }
        },
        {
            PieceType::Hisha, {
            .stepMoves = {},
            .slideMoves = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }
            }
        },
        {
            PieceType::Ou, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1}, {-1, 1}, {1, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::Gyoku, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1}, {-1, 1}, {1, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::Tokin, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::NariKyo, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::NariKei, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::NariGin, {
            .stepMoves = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1} },
            .slideMoves = {}
            }
        },
        {
            PieceType::Uma, {
            .stepMoves = { {0, -1}, {-1, 0}, {1, 0}, {0, 1} },
            .slideMoves = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} }
            }
        },
        {
            PieceType::Ryu, {
            .stepMoves = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} },
            .slideMoves = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }
            }
        }
    };
}