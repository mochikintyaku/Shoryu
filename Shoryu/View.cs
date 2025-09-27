using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shoryu
{
    internal class View
    {
        public static void DrowBoard(PaintEventArgs e, Rectangle boardBounds)
        {
            Graphics g = e.Graphics;
            uint width = (uint)boardBounds.Width / 9;
            uint height = (uint)boardBounds.Height / 9;

            g.FillRectangle(new SolidBrush(Color.Peru), boardBounds);
            g.DrawRectangle(new Pen(Color.Black), boardBounds);
            for (int i = 0; i < 9; i++)
            {
                g.DrawLine(new Pen(Color.Black), boardBounds.Left + width * i, boardBounds.Top, boardBounds.Left + width * i, boardBounds.Bottom);
                g.DrawLine(new Pen(Color.Black), boardBounds.Left, boardBounds.Top + height * i, boardBounds.Right, boardBounds.Top + height * i);
            }
        }
    }
}
