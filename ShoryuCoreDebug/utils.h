#pragma once
#include "Types.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <string>

namespace shoryu::core
{
    static inline std::string toKanji(Piece piece)
    {
        std::string strPiece = (piece.owner() == PlayerSide::Sente) ? "£ " : "¤ ";

        static const char* kanji_piece[] = { "•à", "", "Œj", "‹â", "‹à", "Šp", "”ò", "‰¤", "‹Ê", "‚Æ", "ˆÇ", "Œ\", "‘S", "”n", "—³" };
        if (piece.pieceType() >= PieceType::Fu && piece.pieceType() <= PieceType::Ryu)
        {
            strPiece.append(kanji_piece[(int)piece.pieceType()]);
            return strPiece;
        }
        return "?";
    }


	static inline void printSeparatorLine() {
        std::cout << "+";
        for (int i = 0; i < BoardSize; ++i) {
            std::cout << "----+";
        }
        std::cout << "\n";
    }

    static inline void show(const Board::PieceLayout& layout){
        for (int row = 0; row < BoardSize; ++row) {
            printSeparatorLine();
            std::cout << "|";
            for (int column = 0; column < BoardSize; ++column) {
                const auto& pieceOpt = layout[row][column];
                if (pieceOpt.has_value()) {
                    std::string kanji = toKanji(pieceOpt.value());
                    std::cout << std::setw(3) << kanji << "|";
                }
                else {
                    std::cout << "    |";
                }
            }
            std::cout << "\n";
        }
        printSeparatorLine();
        std::cout << std::endl << std::endl;
    }
}
