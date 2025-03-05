#include "Stage.h"
#include "./globals.h"
#include <vector>

namespace {
    // 外壁から1マス開けて均等にブロックを配置する関数
    void GenerateStageWithBlocks(int w, int h, std::vector<std::vector<STAGE_OBJ>>& _stage) {
        // すべてのセルを壁で初期化
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                // 外壁を設定
                if (i == 0 || j == 0 || i == w - 1 || j == h - 1) {
                    _stage[j][i] = STAGE_OBJ::WALL;
                } else {
                    _stage[j][i] = STAGE_OBJ::EMPTY;  // 内部は空白
                }
            }
        }

        // 外壁から1マス開けて、内側に均等にブロックを配置
        for (int j = 2; j < h - 2; j += 2) {  // 外壁から1マス開けて2マスごとにブロックを配置
            for (int i = 2; i < w - 2; i += 2) {
                _stage[j][i] = STAGE_OBJ::WALL;  // 均等にブロックを設置
            }
        }
    }

    void MakeStageWithBlocks(int w, int h, std::vector<std::vector<STAGE_OBJ>>& _stage) {
        GenerateStageWithBlocks(w, h, _stage);  // 外壁から1マス開けて均等にブロックを配置
    }
}

Stage::Stage() {
    stageData = std::vector<std::vector<STAGE_OBJ>>(STAGE_HEIGHT, std::vector<STAGE_OBJ>(STAGE_WIDTH, STAGE_OBJ::EMPTY));

    MakeStageWithBlocks(STAGE_WIDTH, STAGE_HEIGHT, stageData);  // ブロックを配置したステージを生成
    setStageRects();
}

Stage::~Stage() {}

void Stage::Update() {
    // ゲームの進行に伴うステージの更新処理（ここでは実装しなくても良い）
}

void Stage::Draw() {
    for (int y = 0; y < STAGE_HEIGHT; y++) {
        for (int x = 0; x < STAGE_WIDTH; x++) {
            switch (stageData[y][x]) {
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

void Stage::setStageRects() {
    // 壁の位置を取得し、矩形を設定
    for (int y = 0; y < STAGE_HEIGHT; y++) {
        for (int x = 0; x < STAGE_WIDTH; x++) {
            if (stageData[y][x] == STAGE_OBJ::WALL) {
                stageRects.push_back(Rect(x * CHA_WIDTH, y * CHA_HEIGHT, CHA_WIDTH, CHA_HEIGHT));
            }
        }
    }
}
