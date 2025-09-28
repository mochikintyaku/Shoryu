#pragma once
#include <unordered_map>
#include "ShoryuCoreExport.h"

namespace shoryu::core
{
    class Piece;

    constexpr static int BoardSize = 9;

    enum class Suji
    {
        _1 = 8,  // �z��v�f�̃C���f�b�N�X�ɍ��킹�Ă���
        _2 = 7,
        _3 = 6,
        _4 = 5,
        _5 = 4,
        _6 = 3,
        _7 = 2,
        _8 = 1,
        _9 = 0,
        Invalid = 9
    };

    enum class Dan
    {
        _1 = 0,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        Invalid
    };

    struct SHORYU_API Position
    {
        Suji suji_;
        Dan dan_;

        Position()
            : suji_(Suji::_1), dan_(Dan::_1)
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