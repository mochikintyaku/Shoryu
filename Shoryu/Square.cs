using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shoryu
{
    internal struct Square
    {
        public Piece? Piece { get; }

        public Square()
        {
            Piece = null;
        }

        public Square(Piece? piece)
        {
            Piece = piece;
        }

        public bool IsEmpty => Piece == null;
    }
}
