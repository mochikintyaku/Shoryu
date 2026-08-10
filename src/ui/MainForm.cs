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
                // TODO: Implement drop move logic here. For now, we will just drop a SenteFu piece for demonstration.
                game.ExecuteDropMove(position, ManagedPieceCode.SenteFu);
            }
            else
            {
                ManagedPosition[] legalMoves = game.GetLegalMoves(position);
                if (legalMoves.Length > 0)
                {
                    // TODO: Implement move selection logic here. For now, we will just move the piece to the first legal position for demonstration.
                    game.ExecuteNormalMove(position, legalMoves[0]);
                }
            }
            boardControl.Invalidate();
        }

        private void boardControl_Paint(object sender, PaintEventArgs e)
        {
            boardControl.OnPaint(e, game);
        }
    }
}
