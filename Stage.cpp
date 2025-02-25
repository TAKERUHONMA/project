#include "Stage.h"
#include "./globals.h"
#include <stack>
#include <vector>
#include <cstdlib>

namespace {
    const int DIRS[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };  // �E�A���A���A��

    // �����_���ɕǂ��폜���ĒʘH���쐬����[���D��T��
    void GenerateMaze(int w, int h, vector<vector<STAGE_OBJ>>& _stage) {
        // ���ׂẴZ����ǂŏ�����
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                _stage[j][i] = STAGE_OBJ::WALL;
            }
        }

        // �����_���ȊJ�n�_ (��̃Z���ɂ��邱�ƂŕǂƒʘH�̊Ԋu�𒲐�)
        int startX = (rand() % (w / 2)) * 2 + 1;
        int startY = (rand() % (h / 2)) * 2 + 1;

        _stage[startY][startX] = STAGE_OBJ::EMPTY;

        // �X�^�b�N�Ɍ��݈ʒu��ێ�
        std::stack<Point> stack;
        stack.push({ startX, startY });

        while (!stack.empty()) {
            Point current = stack.top();
            stack.pop();

            std::vector<Point> neighbors;

            // �אڂ��関�K��̃Z����������
            for (auto& dir : DIRS) {
                int nx = current.x + dir[0] * 2;
                int ny = current.y + dir[1] * 2;

                if (nx > 0 && ny > 0 && nx < w - 1 && ny < h - 1 && _stage[ny][nx] == STAGE_OBJ::WALL) {
                    neighbors.push_back({ nx, ny });
                }
            }

            if (!neighbors.empty()) {
                // �����_���ȗאڃZ����I��
                Point next = neighbors[rand() % neighbors.size()];

                // �אڃZ���̕ǂ��폜���ĒʘH���쐬
                int wallX = (current.x + next.x) / 2;
                int wallY = (current.y + next.y) / 2;
                _stage[wallY][wallX] = STAGE_OBJ::EMPTY;

                // ���ɐi��
                _stage[next.y][next.x] = STAGE_OBJ::EMPTY;
                stack.push(current);  // ���݈ʒu��߂����߂ɃX�^�b�N�ɒǉ�
                stack.push(next);     // ���ɐi��
            }
        }
    }

    void MakeMazeDigDug(int w, int h, vector<vector<STAGE_OBJ>>& _stage)
    {
        GenerateMaze(w, h, _stage);  // �[���D��T���Ŗ��H�𐶐�
    }
}

Stage::Stage()
{
    stageData = vector(STAGE_HEIGHT, vector<STAGE_OBJ>(STAGE_WIDTH, STAGE_OBJ::EMPTY));

    MakeMazeDigDug(STAGE_WIDTH, STAGE_HEIGHT, stageData);  // ���H�̐���
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
                DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(102, 205, 170), TRUE);  // ��
                break;
            case STAGE_OBJ::WALL:
                DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(119, 136, 153), TRUE);  // ��
                break;
            case STAGE_OBJ::GOAL:
                // �ڕW�n�_�Ȃǂ�����Ε`��
                break;
            default:
                break;
            }
        }
    }
}

void Stage::setStageRects()
{
    // �ǂ̈ʒu���擾���A��`��ݒ�
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
