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

        public HandControl(ManagedPlayerSide managedPlayerSide=ManagedPlayerSide.Sente)
        {
            _playerSide = managedPlayerSide;
            InitializeComponent();
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
             |        |        |
             |        |        |
             +--------+--------+
             |        |        |
             |        |        |
             +--------+--------+
            */


            int pieceStandHeight = Height;
            int horizontalGuideLineWidth = pieceStandHeight / 3;
            int pieceStandWidth = Width;
            int verticalGuideLineWidth = pieceStandWidth / 3;
            int verticalGuideLineWidth2 = pieceStandWidth / 2;

            Pen threeSplitPen = new Pen(Color.Black, 1);
            threeSplitPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            g.DrawLine(threeSplitPen, new Point(0, horizontalGuideLineWidth), new Point(pieceStandWidth, horizontalGuideLineWidth));
            g.DrawLine(threeSplitPen, new Point(0, horizontalGuideLineWidth * 2), new Point(pieceStandWidth, horizontalGuideLineWidth * 2));
            g.DrawLine(threeSplitPen, new Point(verticalGuideLineWidth, 0), new Point(verticalGuideLineWidth, horizontalGuideLineWidth));
            g.DrawLine(threeSplitPen, new Point(verticalGuideLineWidth * 2, 0), new Point(verticalGuideLineWidth * 2, horizontalGuideLineWidth));
            g.DrawLine(threeSplitPen, new Point(verticalGuideLineWidth2, horizontalGuideLineWidth), new Point(verticalGuideLineWidth2, pieceStandHeight));
        }

        public void DrowHandPiece(Graphics g, ManagedGame game)
        {
            if (this._playerSide == ManagedPlayerSide.Sente)
            {
                int[] pieceCounts = game.GetHandPieceCounts();
            }
        }
    }
}
