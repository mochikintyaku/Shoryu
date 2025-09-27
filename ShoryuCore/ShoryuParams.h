#pragma once
#include <unordered_map>
#include "ShoryuCoreExport.h"

namespace shoryu
{
    class Piece;

    constexpr static int BoardSize = 9;

    enum class Suji
    {
        Suji1 = 8,  // �z��v�f�̃C���f�b�N�X�ɍ��킹�Ă���
        Suji2 = 7,
        Suji3 = 6,
        Suji4 = 5,
        Suji5 = 4,
        Suji6 = 3,
        Suji7 = 2,
        Suji8 = 1,
        Suji9 = 0,
        Invalid = 9
    };

    enum class Dan
    {
        Dan1 = 0,
        Dan2,
        Dan3,
        Dan4,
        Dan5,
        Dan6,
        Dan7,
        Dan8,
        Dan9,
        Invalid
    };

    struct SHORYU_API Position
    {
        Suji suji_;
        Dan dan_;

        Position()
            : suji_(Suji::Suji1), dan_(Dan::Dan1)
        {
        }

        Position(Suji suji, Dan dan)
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

    inline const std::unordered_map<PieceType, PieceType> PromoteMap =
    {
        {PieceType::Fu, PieceType::Tokin},
        {PieceType::Kyo, PieceType::NariKyo},
        {PieceType::Kei, PieceType::NariKei},
        {PieceType::Gin, PieceType::NariGin},
        {PieceType::Kaku, PieceType::Uma},
        {PieceType::Hisha, PieceType::Ryu}
    };

    inline const std::unordered_map<PieceType, PieceType> DemoteMap =
    {
        {PieceType::Tokin, PieceType::Fu},
        {PieceType::NariKyo, PieceType::Kyo},
        {PieceType::NariKei, PieceType::Kei},
        {PieceType::NariGin, PieceType::Gin},
        {PieceType::Uma, PieceType::Kaku},
        {PieceType::Ryu, PieceType::Hisha}
    };

    enum class MoveDirection
    {
        None = 0,
        Forward = 1 << 0,
        Backward = 1 << 1,
        Left = 1 << 2,
        Right = 1 << 3,
        ForwardLeft = 1 << 4,
        ForwardRight = 1 << 5,
        BackwardLeft = 1 << 6,
        BackwardRight = 1 << 7,
        KeimaLeft = 1 << 8,
        KeimaRight = 1 << 9,
        UForward = 1 << 10,
        UBackward = 1 << 11,
        ULeft = 1 << 12,
        URight = 1 << 13,
        UForwardLeft = 1 << 14,
        UForwardRight = 1 << 15,
        UBackwardLegt = 1 << 16,
        UBackwardRight = 1 << 17
        // U = Unlimited�@��������肻�̕����ɓ�����
    };

    enum class PlayerSide
    {
        Sente = 0,
        Gote
    };


    // Utilities
    bool isNormalPiece(PieceType p);
    bool isPromotedPiece(PieceType p);
    bool canPromote(const Piece& piece);
}