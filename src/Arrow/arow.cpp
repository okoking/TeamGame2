#include "DxLib.h"
#include "arow.h"
#include "../Collision/Collision.h"
Arrow::Arrow() {}
Arrow::~Arrow() {}


// �e������
void Arrow::Init()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		arrowInfo[i].handle = LoadGraph("data/play/kari_arrow.png");
		arrowInfo[i].x = 0;
		arrowInfo[i].y = 0;
		arrowInfo[i].isUse = false;
	}
}

// �e���ˏ���
bool Arrow::IsShot(int shotPosX, int shotPosY)
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		if (!arrowInfo[i].isUse) {
			// ���E�㉺����o��
			// �e���W�̏����ʒu�ɐݒ�
			arrowInfo[i].x = shotPosX;
			arrowInfo[i].y = shotPosY;
			arrowInfo[i].isUse = true;

			// ���ː���
			return true;
		}
	}

	// ���ˎ��s
	return false;
}

// �e�̈ړ�����
void Arrow::Move()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			// �e���g�p���Ȃ�ړ�������
			arrowInfo[i].x += 3;

			// �n�[�g�ɓ��������疢�g�p�ɖ߂�IsHitRect�g��
			if (Collision::Rect(326,225,148,149, arrowInfo[i].x, arrowInfo[i].y,108,56)) {
				arrowInfo[i].isUse = false;
			}
		}
	}
}

// �e�̕`��
void Arrow::Draw()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			DrawGraph(arrowInfo[i].x+(i*2), arrowInfo[i].y, arrowInfo[i].handle, true);
		}
	}
}