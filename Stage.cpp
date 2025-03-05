#include "Stage.h"
#include "./globals.h"
#include <vector>

namespace {
    // �O�ǂ���1�}�X�J���ċϓ��Ƀu���b�N��z�u����֐�
    void GenerateStageWithBlocks(int w, int h, std::vector<std::vector<STAGE_OBJ>>& _stage) {
        // ���ׂẴZ����ǂŏ�����
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                // �O�ǂ�ݒ�
                if (i == 0 || j == 0 || i == w - 1 || j == h - 1) {
                    _stage[j][i] = STAGE_OBJ::WALL;
                } else {
                    _stage[j][i] = STAGE_OBJ::EMPTY;  // �����͋�
                }
            }
        }

        // �O�ǂ���1�}�X�J���āA�����ɋϓ��Ƀu���b�N��z�u
        for (int j = 2; j < h - 2; j += 2) {  // �O�ǂ���1�}�X�J����2�}�X���ƂɃu���b�N��z�u
            for (int i = 2; i < w - 2; i += 2) {
                _stage[j][i] = STAGE_OBJ::WALL;  // �ϓ��Ƀu���b�N��ݒu
            }
        }
    }

    void MakeStageWithBlocks(int w, int h, std::vector<std::vector<STAGE_OBJ>>& _stage) {
        GenerateStageWithBlocks(w, h, _stage);  // �O�ǂ���1�}�X�J���ċϓ��Ƀu���b�N��z�u
    }
}

Stage::Stage() {
    stageData = std::vector<std::vector<STAGE_OBJ>>(STAGE_HEIGHT, std::vector<STAGE_OBJ>(STAGE_WIDTH, STAGE_OBJ::EMPTY));

    MakeStageWithBlocks(STAGE_WIDTH, STAGE_HEIGHT, stageData);  // �u���b�N��z�u�����X�e�[�W�𐶐�
    setStageRects();
}

Stage::~Stage() {}

void Stage::Update() {
    // �Q�[���̐i�s�ɔ����X�e�[�W�̍X�V�����i�����ł͎������Ȃ��Ă��ǂ��j
}

void Stage::Draw() {
    for (int y = 0; y < STAGE_HEIGHT; y++) {
        for (int x = 0; x < STAGE_WIDTH; x++) {
            switch (stageData[y][x]) {
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

void Stage::setStageRects() {
    // �ǂ̈ʒu���擾���A��`��ݒ�
    for (int y = 0; y < STAGE_HEIGHT; y++) {
        for (int x = 0; x < STAGE_WIDTH; x++) {
            if (stageData[y][x] == STAGE_OBJ::WALL) {
                stageRects.push_back(Rect(x * CHA_WIDTH, y * CHA_HEIGHT, CHA_WIDTH, CHA_HEIGHT));
            }
        }
    }
}
