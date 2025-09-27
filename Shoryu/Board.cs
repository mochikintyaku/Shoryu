using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shoryu
{
    internal class Board
    {
        Board() 
        {
            _pieceLayout = new Square[9, 9];
        }

        private Square[,] _pieceLayout;
        public Square[,] PieceLayout 
        { 
            get => PieceLayout;
            set
            {
                ArgumentNullException.ThrowIfNull(value);
                if ((value.GetLength(0) != 9) || (value.GetLength(1) != 9))
                {
                    throw new ArgumentException("Invalid Board Size", nameof(value));
                }
                _pieceLayout = value;
            }
        }

        public void SetSquare(Suji suji, Dan dan, Piece? piece)
        {
            _pieceLayout[(int)dan, (int)suji] = new Square(piece);
        }

        public Square GetSquare(Suji suji, Dan dan)
        {
            return _pieceLayout[(int)dan, (int)suji];
        }
    }
}
