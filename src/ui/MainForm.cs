using shoryu.interop;


namespace UI
{
    public partial class MainForm : Form
    {
        private GameController _gameController;

        public MainForm(GameController gameController)
        {
            _gameController = gameController;
            InitializeComponent();
        }

        private void BoardControl_MouseClick(object sender, MouseEventArgs e)
        {
            ManagedPosition position = new ManagedPosition(boardControl.ToSuji(e.X), boardControl.ToDan(e.Y));
            _gameController.OnMouseClick(position);
            boardControl.Invalidate();
        }

        private void BoardControl_Paint(object sender, PaintEventArgs e)
        {
            boardControl.OnPaint(e, _gameController.Game);
        }

        private void HandControl_Sente_OnPaint(object sender, PaintEventArgs e)
        {
            handControl_Sente.OnPaint(e, _gameController.Game);
        }
    }
}
