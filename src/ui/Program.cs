using shoryu.interop;

namespace UI
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            ManagedGame game = new ManagedGame();
            GameController gameController = new GameController(game);
            Application.Run(new MainForm(gameController));
        }
    }
}