using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shoryu
{
    public enum PieceType
    {
        None = 0,  // 駒の種類が存在しない = 駒がないマス
        Fu,      // 歩兵
        Kyo,     // 香車
        Kei,     // 桂馬
        Gin,     // 銀将
        Kin,     // 金将
        Kaku,    // 角行
        Hisha,   // 飛車
        Ou,      // 王将
        Gyoku,   // 玉将
        Tokin,   // と金
        NariKyo, // 成香
        NariKei, // 成桂
        NariGin, // 成銀
        Uma,     // 馬
        Ryu      // 竜
    }

    public enum NormalPieceType
    {
        Fu = 1,
        Kyo,
        Kei,
        Gin,
        Kin,
        Kaku,
        Hisha,
        Ou,
        Gyoku
    }

    public enum PromotedPieceType
    {
        Tokin = 10,
        NariKyo,
        NariKei,
        NariGin,
        Uma,
        Ryu
    }

    public enum PlayerSide
    {
        None = 0,  // マスがプレイヤーに属さない = 駒がないマス
        Sente,
        Gote
    }

    public enum Suji
    {
        Suji1 = 8,  // 配列要素のインデックスに合わせている
        Suji2 = 7,
        Suji3 = 6,
        Suji4 = 5,
        Suji5 = 4,
        Suji6 = 3,
        Suji7 = 2,
        Suji8 = 1,
        Suji9 = 0,
        Invalid = 9
    }

    public enum Dan
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
    }

    public enum MoveDirection
    {
        None           = 0,
        Forward        = 1 << 0,
        Backward       = 1 << 1,
        Left           = 1 << 2,
        Right          = 1 << 3,
        ForwardLeft    = 1 << 4,
        ForwardRight   = 1 << 5,
        BackwardLeft   = 1 << 6,
        BackwardRight  = 1 << 7,
        KeimaLeft      = 1 << 8,
        KeimaRight     = 1 << 9,
        UForward       = 1 << 10,
        UBackward      = 1 << 11,
        ULeft          = 1 << 12,
        URight         = 1 << 13,
        UForwardLeft   = 1 << 14,
        UForwardRight  = 1 << 15,
        UBackwardLegt  = 1 << 16,
        UBackwardRight = 1 << 17
        // U = Unlimited　駒が無い限りその方向に動ける
    }
}
