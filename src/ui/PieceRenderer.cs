using shoryu.interop;
using System;
using System.Collections.Generic;
using System.Text;

namespace UI
{
    internal class PieceRenderer
    {
        public static void DrawPiece(Graphics g, ManagedPieceCode code, int x, int y, int width, int height)
        {
            Image? pieceImage = PieceImageProvider.GetPieceImage(code);
            if (pieceImage != null)
            {
                g.DrawImage(pieceImage, x, y, width, height);
            }
        }
    }
}
