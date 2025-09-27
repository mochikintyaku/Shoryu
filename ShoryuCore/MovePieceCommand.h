#pragma once
#include "ShoryuCoreExport.h"
#include "IShoryuCommand.h"
#include "RemovePieceCommand.h"
#include "DropPieceCommand.h"
#include "ShoryuParams.h"
#include <optional>

namespace shoryu
{
    class Board;

    class SHORYU_API MovePieceCommand :
        public IShoryuCommand
    {
    public:
        MovePieceCommand(Board& board, Position from, Position to);
        ~MovePieceCommand() = default;
        void execute(); // override
        void undo();    // override
    private:
        Board& board_;
        Position from_;
        Position to_;
        std::optional<RemovePieceCommand> removeCommand_;
        std::optional<DropPieceCommand> dropCommand_;
        bool executed_;
    };
}