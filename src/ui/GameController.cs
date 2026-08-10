using System;
using System.Collections.Generic;
using System.Text;
using shoryu.interop;

namespace UI
{
    enum GameState
    {
        Idle,                 // 駒未選択
        WaitingForMove        // 駒選択済み、駒の移動先または打ち先の選択待ち
    }

    public class GameController
    {
        public ManagedGame Game { get; }
        private GameState _state;


        public GameController(ManagedGame game)
        {
            Game = game;
            _state = GameState.Idle;
        }

        public void MakeMove(ManagedPosition pos)
        {
            ManagedPieceCode code = Game.GetPieceCodeAt(pos);
            if (code == ManagedPieceCode.Empty)
            {
                // TODO: Implement drop move logic here. For now, we will just drop a SenteFu piece for demonstration.
                Game.ExecuteDropMove(pos, ManagedPieceCode.SenteFu);
            }
            else
            {
                ManagedPosition[] legalMoves = Game.GetLegalMoves(pos);
                if (legalMoves.Length > 0)
                {
                    // TODO: Implement move selection logic here. For now, we will just move the piece to the first legal position for demonstration.
                    Game.ExecuteNormalMove(pos, legalMoves[0]);
                }
            }
        }


    }
}
