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

        private void boardControl_MouseClick(object sender, MouseEventArgs e)
        {
            ManagedPosition position = new ManagedPosition(boardControl.ToSuji(e.X), boardControl.ToDan(e.Y));
            _gameController.MakeMove(position);
            boardControl.Invalidate();
        }

        private void boardControl_Paint(object sender, PaintEventArgs e)
        {
            boardControl.OnPaint(e, _gameController.Game);
        }
    }
}
