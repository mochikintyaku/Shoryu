#pragma once
#include "ShoryuCoreExport.h"
#include "IShoryuCommand.h"
#include "DropPieceCommand.h"
#include "ShoryuParams.h"
#include "Piece.h"
#include <optional>

namespace shoryu::core
{
    class Board;

    class SHORYU_API RemovePieceCommand :
        public IShoryuCommand
    {
    public:
        RemovePieceCommand(Board& board, Position pos);
        ~RemovePieceCommand() = default;
        void execute(); // override;
        void undo();    // override;
        std::optional<Piece> removedPiece() const;

    private:
        DropPieceCommand dropCommand;
        bool executed_;
    };
}