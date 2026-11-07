using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using shoryu.interop;

namespace UI
{
    public partial class BoardControl : UserControl
    {
        private int cellWidth;
        private int cellHeight;

        public BoardControl()
        {
            InitializeComponent();
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            cellWidth = Width / 9;
            cellHeight = Height / 9;
        }

        public void OnPaint(PaintEventArgs e, ManagedGame game)
        {
            var g = e.Graphics;

            DrawBoardFrame(e);
            DrawLayout(e, game);
        }

        private void DrawBoardFrame(PaintEventArgs e)
        {
            var g = e.Graphics;
            for (int i = 0; i <= 9; i++)
            {
                g.DrawLine(Pens.Black, new Point(cellWidth*i, 0), new Point(cellWidth*i, Height));
                g.DrawLine(Pens.Black, new Point(0, cellHeight*i), new Point(Width, cellHeight*i));
            }
        }

        private void DrawLayout(PaintEventArgs e, ManagedGame game)
        {
            for(int suji = 1; suji<=9; suji++)
            {
                for(int dan=1; dan<=9; dan++)
                {
                    ManagedPieceCode code = game.GetPieceCodeAt(new ManagedPosition(suji, dan));
                    if (code != ManagedPieceCode.Empty)
                    {
                        DrawPiece(e, code, suji, dan);
                    }
                }
            }
        }
        public void DrawPiece(PaintEventArgs e, ManagedPieceCode code, int suji, int dan)
        {
            var g = e.Graphics;
            Rectangle rect = new Rectangle((9 - suji) * cellWidth, (dan - 1) * cellHeight, cellWidth, cellHeight);
            Image? img = PieceImageProvider.GetPieceImage(code);
            if (img != null)
            {
                g.DrawImage(img, rect);
            }
        }

        public int ToSuji(int x)
        {
            return 9 - (x / cellWidth);
        }
        public int ToDan(int y)
        {
            return (y / cellHeight) + 1;
        }
    }
}
