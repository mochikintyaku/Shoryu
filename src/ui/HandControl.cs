using shoryu.interop;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UI
{
    public partial class HandControl : UserControl
    {
        private readonly ManagedPlayerSide _playerSide;
        private int _cellWidth;
        private int _cellHeight;
        private static int _handPieceCountsLength = 7;  // 持ち駒として扱う駒の種類は7種類しかないので、配列の長さは7に固定する
        private static int _flipOffset = 14;
        public HandControl()
            : this(ManagedPlayerSide.Sente)
        {
        }

        public HandControl(ManagedPlayerSide managedPlayerSide)
        {
            _playerSide = managedPlayerSide;
            InitializeComponent();
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            this._cellWidth = Width / 3;
            this._cellHeight = Height / 3;

        }
        public void OnPaint(PaintEventArgs e, ManagedGame game)
        {
            var g = e.Graphics;
            DrowPieceStandFrame(g, game);
            DrowHandPiece(g, game);
        }

        public void DrowPieceStandFrame(Graphics g, ManagedGame game)
        {
            /*
             +-----+-----+-----+
             |     |     |     |
             |     |     |     |
             +-----+-----+-----+
             |     |     |     |
             |     |     |     |
             +-----+-----+-----+
             |     |     |     |
             |     |     |     |
             +-----+-----+-----+
            */

            Pen threeSplitPen = new Pen(Color.Black, 1);
            threeSplitPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            for (int i = 1; i <= 2; ++i)
            {
                g.DrawLine(threeSplitPen, new Point(_cellWidth*i, 0), new Point(_cellWidth*i, Height));
                g.DrawLine(threeSplitPen, new Point(0, _cellHeight*i), new Point(Width, _cellHeight*i));
            }
        }

        public void DrowHandPiece(Graphics g, ManagedGame game)
        {
            int[] pieceAllCounts = game.GetHandPieceCounts();
            int beginIdx = (this._playerSide == ManagedPlayerSide.Sente) ? (int)ManagedPieceCode.SenteFu : (int)ManagedPieceCode.GoteFu;
            int endIdx = beginIdx + _handPieceCountsLength;
            for (; beginIdx < endIdx;++beginIdx)
            {
                if (pieceAllCounts[beginIdx] > 0)
                {
                    int x = 0;
                    int y = 0;
                    if (this._playerSide == ManagedPlayerSide.Sente)
                    {
                        x = (beginIdx - 1) % 3;
                        y = (beginIdx - 1) / 3;
                    }
                    else
                    {
                        int tmpIdx = beginIdx - _flipOffset;
                        x = 2 - (tmpIdx - 1) % 3;
                        y = 2 - (tmpIdx - 1) / 3;
                    }

                    DrawPiece(g, (ManagedPieceCode)beginIdx, x, y);
                }
            }
        }

        public void DrawPiece(Graphics g, ManagedPieceCode code, int x, int y)
        {
            var pieceImage = PieceImageProvider.GetPieceImage(code);
            if (pieceImage != null)
            {
                g.DrawImage(pieceImage, new Rectangle(_cellWidth * x, _cellHeight * y, _cellWidth, _cellHeight));
            }
        }
    }
}
