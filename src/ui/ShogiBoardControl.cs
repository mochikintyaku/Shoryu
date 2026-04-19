using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ui
{
    internal sealed class ShogiBoardControl : UserControl
    {
        private static readonly Color BoardColor = Color.FromArgb(232, 200, 140);
        private static readonly Color BorderColor = Color.FromArgb(70, 50, 25);

        public ShogiBoardControl()
        {
            DoubleBuffered = true;
            ResizeRedraw = true;

            MinimumSize = new Size(200, 200);
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);

            Invalidate();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var g = e.Graphics;

            Rectangle boardRect = GetCenteredSquare(ClientRectangle);

            using var boardBrash = new SolidBrush(BoardColor);
            using var borderPen = new Pen(BorderColor, 2);

            g.FillRectangle(boardBrash, boardRect);
            g.DrawRectangle(borderPen, boardRect);
        }

        private static Rectangle GetCenteredSquare(Rectangle bounds)
        { 
            int side = Math.Min(bounds.Width, bounds.Height);
            int x = bounds.X + (bounds.Width - side) / 2;
            int y = bounds.Y + (bounds.Height - side) / 2;
            return new Rectangle(x, y, side, side);
        }


    }
}
