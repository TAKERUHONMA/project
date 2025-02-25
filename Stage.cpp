#include "Stage.h"
#include "./globals.h"
#include <stack>
#include <vector>
#include <cstdlib>

namespace {
    const int DIRS[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };  // 右、下、左、上

    // ランダムに壁を削除して通路を作成する深さ優先探索
    void GenerateMaze(int w, int h, vector<vector<STAGE_OBJ>>& _stage) {
        // すべてのセルを壁で初期化
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                _stage[j][i] = STAGE_OBJ::WALL;
            }
        }

        // ランダムな開始点 (奇数のセルにすることで壁と通路の間隔を調整)
        int startX = (rand() % (w / 2)) * 2 + 1;
        int startY = (rand() % (h / 2)) * 2 + 1;

        _stage[startY][startX] = STAGE_OBJ::EMPTY;

        // スタックに現在位置を保持
        std::stack<Point> stack;
        stack.push({ startX, startY });

        while (!stack.empty()) {
            Point current = stack.top();
            stack.pop();

            std::vector<Point> neighbors;

            // 隣接する未訪問のセルを見つける
            for (auto& dir : DIRS) {
                int nx = current.x + dir[0] * 2;
                int ny = current.y + dir[1] * 2;

                if (nx > 0 && ny > 0 && nx < w - 1 && ny < h - 1 && _stage[ny][nx] == STAGE_OBJ::WALL) {
                    neighbors.push_back({ nx, ny });
                }
            }

            if (!neighbors.empty()) {
                // ランダムな隣接セルを選ぶ
                Point next = neighbors[rand() % neighbors.size()];

                // 隣接セルの壁を削除して通路を作成
                int wallX = (current.x + next.x) / 2;
                int wallY = (current.y + next.y) / 2;
                _stage[wallY][wallX] = STAGE_OBJ::EMPTY;

                // 次に進む
                _stage[next.y][next.x] = STAGE_OBJ::EMPTY;
                stack.push(current);  // 現在位置を戻すためにスタックに追加
                stack.push(next);     // 次に進む
            }
        }
    }

    void MakeMazeDigDug(int w, int h, vector<vector<STAGE_OBJ>>& _stage)
    {
        GenerateMaze(w, h, _stage);  // 深さ優先探索で迷路を生成
    }
}

Stage::Stage()
{
    stageData = vector(STAGE_HEIGHT, vector<STAGE_OBJ>(STAGE_WIDTH, STAGE_OBJ::EMPTY));

    MakeMazeDigDug(STAGE_WIDTH, STAGE_HEIGHT, stageData);  // 迷路の生成
    setStageRects();
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
    for (int y = 0; y < STAGE_HEIGHT; y++)
    {
        for (int x = 0; x < STAGE_WIDTH; x++)
        {
            switch (stageData[y][x])
            {
            case STAGE_OBJ::EMPTY:
                DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(102, 205, 170), TRUE);  // 空白
                break;
            case STAGE_OBJ::WALL:
                DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(119, 136, 153), TRUE);  // 壁
                break;
            case STAGE_OBJ::GOAL:
                // 目標地点などがあれば描画
                break;
            default:
                break;
            }
        }
    }
}

void Stage::setStageRects()
{
    // 壁の位置を取得し、矩形を設定
    for (int y = 0; y < STAGE_HEIGHT; y++)
    {
        for (int x = 0; x < STAGE_WIDTH; x++)
        {
            if (stageData[y][x] == STAGE_OBJ::WALL)
            {
                stageRects.push_back(Rect(x * CHA_WIDTH, y * CHA_HEIGHT, CHA_WIDTH, CHA_HEIGHT));
            }
        }
    }
}
