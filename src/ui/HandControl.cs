using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UI
{
    public partial class HandControl : UserControl
    {
        private static readonly Color HandControlColor = Color.LightGray;

        public HandControl()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            var g = e.Graphics;

            g.FillRectangle(new SolidBrush(HandControlColor), ClientRectangle);
        }
    }
}
