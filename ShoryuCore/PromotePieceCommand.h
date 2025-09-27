#pragma once
#include "ShoryuCoreExport.h"
#include "IShoryuCommand.h"
#include "ShoryuParams.h"
#include "Piece.h"
#include <optional>

namespace shoryu
{
    class Board;

    class SHORYU_API PromotePieceCommand :
        public IShoryuCommand
    {
    public:
        PromotePieceCommand(Board& board, Position pos);
        ~PromotePieceCommand() = default;
        void execute(); // override
        void undo();    // override
    private:
        Board& board_;
        Position pos_;
        std::optional<Piece> normal_piece_;
        std::optional<Piece> promoted_piece_;
    };
}
