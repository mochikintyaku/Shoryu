using System;
using System.Collections.Generic;
using System.Text;
using shoryu.interop;

namespace UI
{
    public enum GameState
    {
        Idle,                 // 駒未選択
        PieceSelected,        // 盤上の駒を選択済み
        HandSelected,         // 持ち駒を選択済み
        PromotionPending,       // 成りの選択待ち
    }

    public class GameController
    {
        public ManagedGame Game { get; }
        public GameState State { get; private set; }
        private ManagedPosition? _selectedFrom; //選択中の駒の位置
        private ManagedPosition[] _availablePos; //移動可能なマス
 
        public GameController(ManagedGame game)
        {
            Game = game;
            State = GameState.Idle;
            _selectedFrom = null;
            _availablePos = [];
        }

        private void HandleClickWhenIdle(ManagedPosition pos)
        {
            ManagedPieceCode code = Game.GetPieceCodeAt(pos);
            if (code == ManagedPieceCode.Empty)
            {
                return;
            }

            ManagedPosition[] tmpLegalMoves = Game.GetLegalMoves(pos);
            if(tmpLegalMoves.Length == 0)
            {
                return;
            }

            _availablePos = tmpLegalMoves.ToArray();
            _selectedFrom = pos;
            State = GameState.PieceSelected;
        }


        private void HandleClickWhenPieceSelected(ManagedPosition pos)
        {
            if(!_availablePos.Contains(pos))
            {
                return;
            }
            
            if(_selectedFrom == null)
            {
                State = GameState.Idle;
            }
            else 
            {
                ManagedPosition from = _selectedFrom.Value;
                Game.ExecuteNormalMove(from, pos);
                _selectedFrom = null;
                State = GameState.Idle;
            }
        }

        public void OnMouseClick(ManagedPosition pos)
        {
            switch (State)
            {
                case GameState.Idle:
                    HandleClickWhenIdle(pos);
                    break;
                case GameState.PieceSelected:
                    HandleClickWhenPieceSelected(pos);
                    break;
                case GameState.PromotionPending:
                    break;
            }
        }


    }
}
