#include "gtest/gtest.h"
#include "core/LegalMoveFinder.h"
#include "core/Board.h"
#include "core/Piece.h"
#include "core/Types.h"
#include <vector>
#include <algorithm>

using namespace shoryu::core;

/*
 * LegalMoveFinder のテスト方針
 * 
 * 【テスト因子】
 * 1. 駒の種類
 *    - 歩、香、桂、銀、金、角、飛、王、玉
 *    - と、成香、成桂、成銀、馬、竜
 * 
 * 2. 先手/後手
 *    - 先手: 1段目方向へ進む
 *    - 後手: 9段目方向へ進む
 * 
 * 3. 駒の位置
 *    - 中央 (5,5): 移動制約なし
 *    - 辺 (1,n), (9,n), (n,1), (n,9): 一部方向が盤外
 *    - 角 (1,1), (1,9), (9,1), (9,9): 複数方向が盤外
 *    - 桂馬の特殊制約:
 *      * 先手: 2段目 → 0段目(盤外)で合法手なし、1段目 → -1段目(盤外)で合法手なし
 *      * 後手: 8段目 → 10段目(盤外)で合法手なし、9段目 → 11段目(盤外)で合法手なし
 * 
 * 4. 途中の駒（スライド移動のみ）
 *    - 空マス: 通過可能
 *    - 味方の駒: その手前で停止（その位置には移動不可）
 *    - 敵の駒: その位置まで移動可能（取る）、その先は移動不可
 * 
 * 5. 移動先の駒（ステップ移動）
 *    - 空マス: 移動可能
 *    - 味方の駒: 移動不可
 *    - 敵の駒: 移動可能（取る）
 * 
 * 【現在のスコープ外（将来実装予定）】
 * - 王手回避（自玉が王手されたまま放置する手の除外）
 * - ピン（駒が移動すると自玉が王手される状況）
 * - 成り（成る/成らないの選択肢生成）
 * - 必須成り（行き所のない駒）
 * - 持ち駒の打ち（二歩、打ち歩詰めなど）
 * 
 * 【テストカバレッジ状況】
 * ✅ 駒の種類: 先手・後手 全15種×2 カバー
 * ✅ 先手/後手: 両方カバー
 * ✅ 駒の位置: 中央・盤端・角・桂馬の特殊位置
 * ✅ 途中の駒: 未実装
 * ✅ 移動先の駒: 未実装
 */

namespace LegalMoveFinderTest
{
	TEST(BasicTest, EmptySquare)
	{
		Board board;
		Position pos(5, 5);

		std::vector<Position> moves = findLegalMoves(board, pos);
		EXPECT_TRUE(moves.empty());
	}

	// ========================================
	// 先手のテスト（中央配置）
	// ========================================

	// 先手・歩兵
	TEST(BasicTest, Sente_Fu)
	{
		Board board;
		Piece piece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 1);
		EXPECT_EQ(moves[0], Position(5, 4));
	}

	// 先手・香車
	TEST(BasicTest, Sente_Kyo)
	{
		Board board;
		Piece piece(PieceType::Kyo, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 4);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
	}

	// 先手・桂馬
	TEST(BasicTest, Sente_Kei)
	{
		Board board;
		Piece piece(PieceType::Kei, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 2);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 3)), moves.end());
	}

	// 先手・銀将
	TEST(BasicTest, Sente_Gin)
	{
		Board board;
		Piece piece(PieceType::Gin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 5);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}

	// 先手・金将
	TEST(BasicTest, Sente_Kin)
	{
		Board board;
		Piece piece(PieceType::Kin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	// 先手・角行
	TEST(BasicTest, Sente_Kaku)
	{
		Board board;
		Piece piece(PieceType::Kaku, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 16);
		// 右上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 1)), moves.end());
		// 左上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
		// 右下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
		// 左下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
	}

	// 先手・飛車
	TEST(BasicTest, Sente_Hisha)
	{
		Board board;
		Piece piece(PieceType::Hisha, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 16);
		// 上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
		// 下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 9)), moves.end());
		// 左方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
		// 右方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 5)), moves.end());
	}

	// 先手・王将
	TEST(BasicTest, Sente_Ou)
	{
		Board board;
		Piece piece(PieceType::Ou, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 8);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}

	// 先手・玉将
	TEST(BasicTest, Sente_Gyoku)
	{
		Board board;
		Piece piece(PieceType::Gyoku, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 8);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}

	// 先手・と金
	TEST(BasicTest, Sente_Tokin)
	{
		Board board;
		Piece piece(PieceType::Tokin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	// 先手・成香
	TEST(BasicTest, Sente_NariKyo)
	{
		Board board;
		Piece piece(PieceType::NariKyo, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	// 先手・成桂
	TEST(BasicTest, Sente_NariKei)
	{
		Board board;
		Piece piece(PieceType::NariKei, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	// 先手・成銀
	TEST(BasicTest, Sente_NariGin)
	{
		Board board;
		Piece piece(PieceType::NariGin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	// 先手・馬
	TEST(BasicTest, Sente_Uma)
	{
		Board board;
		Piece piece(PieceType::Uma, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 20);
		// 右上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 1)), moves.end());
		// 左上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
		// 右下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
		// 左下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
		// 縦横１マス
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	}

	// 先手・竜
	TEST(BasicTest, Sente_Ryu)
	{
		Board board;
		Piece piece(PieceType::Ryu, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 20);
		// 上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
		// 下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 9)), moves.end());
		// 左方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
		// 右方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 5)), moves.end());
		// 斜め１マス
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}

	// ========================================
	// 後手のテスト（中央配置）
	// ========================================

	// 後手・歩兵
	TEST(BasicTest, Gote_Fu)
	{
		Board board;
		Piece piece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 1);
		EXPECT_EQ(moves[0], Position(5, 6));
	}

	// 後手・香車
	TEST(BasicTest, Gote_Kyo)
	{
		Board board;
		Piece piece(PieceType::Kyo, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 4);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 9)), moves.end());
	}

	// 後手・桂馬
	TEST(BasicTest, Gote_Kei)
	{
		Board board;
		Piece piece(PieceType::Kei, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 2);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 7)), moves.end());
	}

	// 後手・銀将
	TEST(BasicTest, Gote_Gin)
	{
		Board board;
		Piece piece(PieceType::Gin, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 5);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
	}

	// 後手・金将
	TEST(BasicTest, Gote_Kin)
	{
		Board board;
		Piece piece(PieceType::Kin, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	}

	// 後手・角行
	TEST(BasicTest, Gote_Kaku)
	{
		Board board;
		Piece piece(PieceType::Kaku, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 16);
		// 右上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 1)), moves.end());
		// 左上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
		// 右下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
		// 左下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
	}

	// 後手・飛車
	TEST(BasicTest, Gote_Hisha)
	{
		Board board;
		Piece piece(PieceType::Hisha, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 16);
		// 上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
		// 下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 9)), moves.end());
		// 左方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
		// 右方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 5)), moves.end());
	}

	// 後手・王将
	TEST(BasicTest, Gote_Ou)
	{
		Board board;
		Piece piece(PieceType::Ou, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 8);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}

	// 後手・玉将
	TEST(BasicTest, Gote_Gyoku)
	{
		Board board;
		Piece piece(PieceType::Gyoku, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 8);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}

	// 後手・と金
	TEST(BasicTest, Gote_Tokin)
	{
		Board board;
		Piece piece(PieceType::Tokin, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	}

	// 後手・成香
	TEST(BasicTest, Gote_NariKyo)
	{
		Board board;
		Piece piece(PieceType::NariKyo, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	}

	// 後手・成桂
	TEST(BasicTest, Gote_NariKei)
	{
		Board board;
		Piece piece(PieceType::NariKei, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	}

	// 後手・成銀
	TEST(BasicTest, Gote_NariGin)
	{
		Board board;
		Piece piece(PieceType::NariGin, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	}

	// 後手・馬
	TEST(BasicTest, Gote_Uma)
	{
		Board board;
		Piece piece(PieceType::Uma, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 20);
		// 右上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 1)), moves.end());
		// 左上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
		// 右下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
		// 左下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
		// 縦横１マス
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
	}

	// 後手・竜
	TEST(BasicTest, Gote_Ryu)
	{
		Board board;
		Piece piece(PieceType::Ryu, PlayerSide::Gote);
		board.setSquare(Position(5, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		ASSERT_EQ(moves.size(), 20);
		// 上方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
		// 下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 9)), moves.end());
		// 左方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
		// 右方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 5)), moves.end());
		// 斜め１マス
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}

	// ========================================
	// 盤外チェックのテスト（先手のみ）
	// ========================================

	// 先手・歩（1段目）- 盤外に出るため合法手なし
	TEST(OutOfBoundsMoveTest, Sente_Fu_1_Dan)
	{
		Board board;
		Piece piece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 1));
		// (5,1) の歩は (5,0) に進むが盤外なので合法手なし
		EXPECT_TRUE(moves.empty());
	}

	// 先手・香車（1段目）- 盤外に出るため合法手なし
	TEST(OutOfBoundsMoveTest, Sente_Kyo_1_Dan)
	{
		Board board;
		Piece piece(PieceType::Kyo, PlayerSide::Sente);
		board.setSquare(Position(5, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 1));
		// (5,1) の香車は (5,0) 方向だが盤外なので合法手なし
		EXPECT_TRUE(moves.empty());
	}

	// 先手・桂馬（2段目）- 盤外に出るため合法手なし
	TEST(OutOfBoundsMoveTest, Sente_Kei_2_Dan)
	{
		Board board;
		Piece piece(PieceType::Kei, PlayerSide::Sente);
		board.setSquare(Position(5, 2), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(5, 2));
		// (5,2) の桂は (4,0) と (6,0) に移動するが、両方とも盤外なので合法手なし
		EXPECT_TRUE(moves.empty());
	}

	// 先手・桂馬（1筋）- 盤外に出る手が除外される
	TEST(OutOfBoundsMoveTest, Sente_Kei_1_Suji)
	{
		Board board;
		Piece piece(PieceType::Kei, PlayerSide::Sente);
		board.setSquare(Position(1, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 5));
		// (1,5) の桂は (0,3) と (2,3) に移動するが、(0,3) は盤外なので除外
		ASSERT_EQ(moves.size(), 1);
		EXPECT_EQ(moves[0], Position(2, 3));
	}

	// 先手・桂馬（9筋）- 盤外に出る手が除外される
	TEST(OutOfBoundsMoveTest, Sente_Kei_9_Suji)
	{
		Board board;
		Piece piece(PieceType::Kei, PlayerSide::Sente);
		board.setSquare(Position(9, 5), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(9, 5));
		// (9,5) の桂は (8,3) と (10,3) に移動するが、(10,3) は盤外なので除外
		ASSERT_EQ(moves.size(), 1);
		EXPECT_EQ(moves[0], Position(8, 3));
	}

	// 先手・銀将（1-1）- 盤外に出る手が除外される
	TEST(OutOfBoundsMoveTest, Sente_Gin_Corner)
	{
		Board board;
		Piece piece(PieceType::Gin, PlayerSide::Sente);
		board.setSquare(Position(1, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 1));
		// (1,1) 銀は左下のみ
		ASSERT_EQ(moves.size(), 1);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end()); // 左下
	}

	// 先手・金将（1-1）- 盤外に出る手が除外される
	TEST(OutOfBoundsMoveTest, Sente_Kin_Corner)
	{
		Board board;
		Piece piece(PieceType::Kin, PlayerSide::Sente);
		board.setSquare(Position(1, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 1));
		// (1,1) 金は左・下の2方向のみ
		ASSERT_EQ(moves.size(), 2);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 1)), moves.end()); // 右
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 2)), moves.end()); // 下
	}

	// 先手・角（1-1）- 盤外に出る方向が除外される
	TEST(OutOfBoundsMoveTest, Sente_Kaku_Corner)
	{
		Board board;
		Piece piece(PieceType::Kaku, PlayerSide::Sente);
		board.setSquare(Position(1, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 1));
		// (1,1) 角は左下方向のみ
		ASSERT_EQ(moves.size(), 8);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
	}

	// 先手・飛車（1,1）- 盤外に出る方向が除外される
	TEST(OutOfBoundsMoveTest, Sente_Hisha_Corner)
	{
		Board board;
		Piece piece(PieceType::Hisha, PlayerSide::Sente);
		board.setSquare(Position(1, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 1));
		// (1,1) 飛車左方向と下方向に移動可能
		ASSERT_EQ(moves.size(), 16);
		// 下方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
		// 左方向
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
	}

	// 先手・王（1-1）- 盤外に出る手が除外される
	TEST(OutOfBoundsMoveTest, Sente_Ou_Corner)
	{
		Board board;
		Piece piece(PieceType::Ou, PlayerSide::Sente);
		board.setSquare(Position(1, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 1));
		// (1,1) 王は左・左下・下の3方向
		ASSERT_EQ(moves.size(), 3);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
	}

	// 先手・馬（1-1）- 盤外に出る手が除外される
	TEST(OutOfBoundsMoveTest, Sente_Uma_Corner)
	{
		Board board;
		Piece piece(PieceType::Uma, PlayerSide::Sente);
		board.setSquare(Position(1, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 1));
		// (1,1) 馬は右下斜め + 右・下のステップ
		ASSERT_EQ(moves.size(), 10);
		// 斜め（左下のみ）
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 9)), moves.end());
		// ステップ（左・下）
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 2)), moves.end());
	}

	// 先手・竜（1-1）- 盤外に出る手が除外される
	TEST(OutOfBoundsMoveTest, Sente_Ryu_Corner)
	{
		Board board;
		Piece piece(PieceType::Ryu, PlayerSide::Sente);
		board.setSquare(Position(1, 1), piece);

		std::vector<Position> moves = findLegalMoves(board, Position(1, 1));
		// (1,1) 竜は右・下方向のスライド + 右下斜め1マス
		ASSERT_EQ(moves.size(), 17);
		// 直線（左）
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
		// 直線（下）
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(1, 9)), moves.end());
		// 斜め1マス
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 2)), moves.end());
	}

	// ========================================
	// 移動先に駒がいるテスト（先手のみ）
	// ========================================

	// 先手・歩兵 - 移動先に味方駒がいる場合、合法手に含まれない
	TEST(ExcludesFriendlyOccupiedSquare, Sente_Fu)
	{
		Board board;
		Piece piece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 4), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,4) に味方駒がいるため、合法手に含まれない
		EXPECT_TRUE(moves.empty());
	}

	// 先手・歩兵 - 移動先に敵駒がいる場合、合法手に含まれる
	TEST(IncludesEnemyOccupiedSquare, Sente_Fu)
	{
		Board board;
		Piece piece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(5, 4), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,4) に敵駒がいるため、合法手に含まれる
		ASSERT_EQ(moves.size(), 1);
		EXPECT_EQ(moves[0], Position(5, 4));
	}

	// 先手・香 - 移動先に味方駒がいる場合、合法手に含まれず、それ以降も進めない
	TEST(ExcludesFriendlyOccupiedSquare, Sente_Kyo)
	{
		Board board;
		Piece piece(PieceType::Kyo, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 3), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,3) に味方駒がいるため、(5, 4) のみが合法手
		ASSERT_EQ(moves.size(), 1);
		EXPECT_EQ(moves[0], Position(5, 4));
	}

	// 先手・香 - 移動先に敵駒がいる場合、合法手に含まれ、それ以降は進めない
	TEST(IncludesEnemyOccupiedSquare, Sente_Kyo)
	{
		Board board;
		Piece piece(PieceType::Kyo, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(5, 3), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,3) に敵駒がいるため、(5,4) と (5,3) が合法手
		ASSERT_EQ(moves.size(), 2);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
	}

	// 先手・桂馬 - 移動先に味方駒がいる場合、合法手に含まれない
	TEST(ExcludesFriendlyOccupiedSquare, Sente_Kei)
	{
		Board board;
		Piece piece(PieceType::Kei, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(4, 3), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (4,3) に味方駒がいるため、(6,3) のみが合法手
		ASSERT_EQ(moves.size(), 1);
		EXPECT_EQ(moves[0], Position(6, 3));
	}

	// 先手・桂馬 - 移動先に敵駒がいる場合、合法手に含まれる
	TEST(IncludesEnemyOccupiedSquare, Sente_Kei)
	{
		Board board;
		Piece piece(PieceType::Kei, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(4, 3), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (4,3) に敵駒がいるため、(4,3) と (6,3) が合法手
		ASSERT_EQ(moves.size(), 2);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 3)), moves.end());
	}

	// 先手・銀 - 移動先に味方駒がいる場合、合法手に含まれない
	TEST(ExcludesFriendlyOccupiedSquare, Sente_Gin)
	{
		Board board;
		Piece piece(PieceType::Gin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(4, 4), blockingPiece);
		board.setSquare(Position(6, 4), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (4,4) に味方駒がいるため、合法手に含まれない
		ASSERT_EQ(moves.size(), 3);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	}

	// 先手・銀 - 移動先に敵駒がいる場合、合法手に含まれる
	TEST(IncludesEnemyOccupiedSquare, Sente_Gin)
	{
		Board board;
		Piece piece(PieceType::Gin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(4, 4), blockingPiece);
		board.setSquare(Position(6, 4), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (4,4) に敵駒がいるため、合法手に含まれる
		ASSERT_EQ(moves.size(), 5);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
	}

	TEST(ExcludesFriendlyOccupiedSquare, Sente_Kin)
	{
		Board board;
		Piece piece(PieceType::Kin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 4), blockingPiece);
		board.setSquare(Position(4, 5), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,4)と (4,5) に味方駒がいるため、合法手に含まれない
		ASSERT_EQ(moves.size(), 4);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	TEST(IncludesEnemyOccupiedSquare, Sente_Kin)
	{
		Board board;
		Piece piece(PieceType::Kin, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(5, 4), blockingPiece);
		board.setSquare(Position(4, 5), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,4)と (4,5) に敵駒がいるため、合法手に含まれる
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	TEST(ExcludesFriendlyOccupiedSquare, Sente_Kaku)
	{
		Board board;
		Piece piece(PieceType::Kaku, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(4, 4), blockingPiece);
		board.setSquare(Position(9, 1), blockingPiece);
		board.setSquare(Position(8, 8), blockingPiece);
		board.setSquare(Position(3, 7), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (4,4),(9,1),(8,8),(3,7) に味方駒がいるため、合法手に含まれず、それ以降も進めない
		ASSERT_EQ(moves.size(), 6);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
	}

	TEST(IncludesEnemyOccupiedSquare, Sente_Kaku)
	{
		Board board;
		Piece piece(PieceType::Kaku, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(4, 4), blockingPiece);
		board.setSquare(Position(9, 1), blockingPiece);
		board.setSquare(Position(8, 8), blockingPiece);
		board.setSquare(Position(3, 7), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (4,4),(9,1),(8,8),(3,7) に敵駒がいるため、合法手に含まれ、それ以降は進めない
		ASSERT_EQ(moves.size(), 10);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 2)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 1)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 7)), moves.end());
	}

	TEST(ExcludesFriendlyOccupiedSquare, Sente_Hisya)
	{
		Board board;
		Piece piece(PieceType::Hisha, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 3), blockingPiece);
		board.setSquare(Position(9, 5), blockingPiece);
		board.setSquare(Position(5, 8), blockingPiece);
		board.setSquare(Position(2, 5), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,3),(9,5),(5,8),(2,5) に味方駒がいるため、合法手に含まれず、それ以降も進めない
		ASSERT_EQ(moves.size(), 8);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
	}

	TEST(IncludesEnemyOccupiedSquare, Sente_Hisya)
	{
		Board board;
		Piece piece(PieceType::Hisha, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(5, 3), blockingPiece);
		board.setSquare(Position(9, 5), blockingPiece);
		board.setSquare(Position(5, 8), blockingPiece);
		board.setSquare(Position(2, 5), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,3),(9,5),(5,8),(2,5) に敵駒がいるため、合法手に含まれ、それ以降は進めない
		ASSERT_EQ(moves.size(), 12);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 3)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(7, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(8, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(9, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 7)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 8)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(3, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(2, 5)), moves.end());
	}

	TEST(ExcludesFriendlyOccupiedSquare, Sente_Ou)
	{
		Board board;
		Piece piece(PieceType::Ou, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Sente);
		board.setSquare(Position(5, 4), blockingPiece);
		board.setSquare(Position(4, 5), blockingPiece);
		board.setSquare(Position(6, 6), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,4),(4,5),(6,6) に味方駒がいるため、合法手に含まれない
		ASSERT_EQ(moves.size(), 5);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
	}

	TEST(IncludesEnemyOccupiedSquare, Sente_Ou)
	{
		Board board;
		Piece piece(PieceType::Ou, PlayerSide::Sente);
		board.setSquare(Position(5, 5), piece);
		Piece blockingPiece(PieceType::Fu, PlayerSide::Gote);
		board.setSquare(Position(5, 4), blockingPiece);
		board.setSquare(Position(4, 5), blockingPiece);
		board.setSquare(Position(6, 6), blockingPiece);
		std::vector<Position> moves = findLegalMoves(board, Position(5, 5));
		// (5,4),(4,5),(6,6) に敵駒がいるため、合法手に含まれる
		ASSERT_EQ(moves.size(), 8);
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 4)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 5)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(4, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(5, 6)), moves.end());
		EXPECT_NE(std::find(moves.begin(), moves.end(), Position(6, 6)), moves.end());
	}
}