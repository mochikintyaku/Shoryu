#pragma once
#include <map>
#include <vector>
#include "ShoryuCoreExport.h"

namespace shoryu::core
{
    class Piece;

    struct SHORYU_API Position
    {
        int suji_;  // x����
        int dan_;   // y����

        Position(int suji, int dan)
            : suji_(suji), dan_(dan)
        { }
    };

    enum class PieceType
    {
        Fu = 0,  // ����  =0
        Kyo,     // ����
        Kei,     // �j�n
        Gin,     // �⏫
        Kin,     // ����
        Kaku,    // �p�s
        Hisha,   // ���
        Ou,      // ����
        Gyoku,   // �ʏ�
        Tokin,   // �Ƌ�  =9
        NariKyo, // ����
        NariKei, // ���j
        NariGin, // ����
        Uma,     // �n
        Ryu      // ��
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