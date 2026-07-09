using shoryu.interop;


namespace UI
{
    public partial class MainForm : Form
    {
        private ManagedGame game;
        public MainForm()
        {
            InitializeComponent();
            game = new ManagedGame();
        }

        private void boardControl_MouseClick(object sender, MouseEventArgs e)
        {
            ManagedPosition position = new ManagedPosition(boardControl.ToSuji(e.X), boardControl.ToDan(e.Y));
            ManagedPieceCode code = game.GetPieceCodeAt(position);
            if (code == ManagedPieceCode.Empty)
            {
                game.ExecuteDropMove(position, ManagedPieceCode.SenteFu);
            }
            boardControl.Invalidate();
        }

        private void boardControl_Paint(object sender, PaintEventArgs e)
        {
            boardControl.OnPaint(e, game);
        }
    }
}
