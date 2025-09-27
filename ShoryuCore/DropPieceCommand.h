#pragma once
#include "ShoryuCoreExport.h"
#include "IShoryuCommand.h"
#include "ShoryuParams.h"
#include "Piece.h"
#include <optional>

namespace shoryu
{
    class Board;

    class SHORYU_API DropPieceCommand :
        public IShoryuCommand
    {
    public:
        DropPieceCommand(Board& board, Position pos, std::optional<Piece> post_);
        ~DropPieceCommand() = default;
        void execute();  // override
        void undo();     // override
        std::optional<Piece> PrePiece() const;
    private:
        Board& board_;
        Position pos_;
        std::optional<Piece> pre_piece_;
        std::optional<Piece> post_piece_;
        bool executed_;
    };
}
