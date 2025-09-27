using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shoryu
{
    internal struct Piece
    {
        public Piece() 
        {
            Type = PieceType.None;
            Owner = PlayerSide.None;
        }

        public Piece(PieceType type, PlayerSide side) 
        {
            if ((type != PieceType.None) && (side != PlayerSide.None))
            {
                Type = type;
                Owner = side;
            }
            else
            {
                Type = PieceType.None;
                Owner = PlayerSide.None;
            }
        }

        public PieceType Type { get; }    // getterのみ公開
        public PlayerSide Owner { get; }  // getterのみ公開
    }
}
