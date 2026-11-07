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
            if (this._playerSide == ManagedPlayerSide.Sente)
            {
                int[] pieceCounts = game.GetHandPieceCounts();
            }
        }
    }
}
