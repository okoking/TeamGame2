#include "DxLib.h"
#include "arow.h"
#include "../Collision/Collision.h"
#include "../Player/Player.h"
#include "../Scene/Scene.h"
#include "math.h"

// �R���X�g���N�^
Arrow::Arrow() 
{
	for (int ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			arrowInfo[ArrowIndex].handle[ArrowType] = -1;
		}

		arrowInfo[ArrowIndex].x = 0;
		arrowInfo[ArrowIndex].y = 0;
		arrowInfo[ArrowIndex].isUse = false;
		arrowInfo[ArrowIndex].ShotInterval = ARROW_MAX_INTERVAL;

		arrowInfo[ArrowIndex].angle = ARROW_ANGLE_UP;
		arrowInfo[ArrowIndex].arrowtype = ARROW_TYPE_NORMAL;
		arrowInfo[ArrowIndex].isInversion = false; // ��]���t���O
		arrowInfo[ArrowIndex].isInversioned = false;
	}
	// �����ɔ��˂���Ȃ��悤�ɂ���
	Recoverycnt = -1;
}
Arrow::~Arrow() {}


// �����
void Arrow::Init()
{
	for (int  ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			arrowInfo[ArrowIndex].handle[ArrowType] = 0;
		}

		arrowInfo[ArrowIndex].x = 0;
		arrowInfo[ArrowIndex].y = 0;
		arrowInfo[ArrowIndex].isUse = false;

		arrowInfo[ArrowIndex].angle = (ARROW_ANGLE)GetRand(3);

		arrowInfo[ArrowIndex].ShotInterval = GetRand(ARROW_MAX_INTERVAL);

		arrowInfo[ArrowIndex].arrowtype = (ARROW_TYPE)GetRand(2);

		arrowInfo[ArrowIndex].isInversion = false; // ��]���t���O
		arrowInfo[ArrowIndex].ShotTimeCnt = 0;
		arrowInfo[ArrowIndex].InversionAngle = 0; // ���]����]���Ă��邵�Ă���p�x
	}
	// �����ɔ��˂���Ȃ��悤�ɂ���
	Recoverycnt = RECOVERY_MAX_FRAME;
}

// �f�[�^���[�h
void Arrow::Load()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		arrowInfo[i].handle[ARROW_TYPE_NORMAL] = LoadGraph(NORMALARROW_PATH);
		arrowInfo[i].handle[ARROW_TYPE_RED] = LoadGraph(REDARROW_PATH);
		arrowInfo[i].handle[ARROW_TYPE_YELLOW] = LoadGraph(YELLOWARROW_PATH);
	}
}

// ��ˏ���
void Arrow::IsShot()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (!arrowInfo[i].isUse) {
			// ���E�㉺����o��
			// ����W�̏����ʒu�ɐݒ�
			// ��̔��˕����ɑΉ������l������
			if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
				arrowInfo[i].x = HEART_INIT_POS_X - HEART_INIT_POS_Y;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = 0;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
				arrowInfo[i].x = HEART_INIT_POS_X + HEART_INIT_POS_Y;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = HEART_INIT_POS_Y + HEART_INIT_POS_Y;
			}

			arrowInfo[i].ShotInterval++;

			Recoverycnt++;

			if (arrowInfo[i].ShotInterval > ARROW_MAX_INTERVAL) {
				if (Recoverycnt > RECOVERY_MAX_FRAME) {
					Recoverycnt = 0;

					arrowInfo[i].ShotInterval = ARROW_MAX_INTERVAL;
					arrowInfo[i].isUse = true;
				}
			}
		}
	}
}

// ��̈ړ�����
void Arrow::Move()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (arrowInfo[i].isUse && !arrowInfo[i].isInversion) {
			// ��g�p�������]������Ȃ��Ȃ�ړ�������
			// ��̔��˕����ɑΉ������l������
			if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
				arrowInfo[i].x += ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
				arrowInfo[i].y += ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
				arrowInfo[i].x -= ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
				arrowInfo[i].y -= ARROW_SPEED;
			}

			arrowInfo[i].ShotTimeCnt++;

			if (arrowInfo[i].ShotTimeCnt > INVERSION_FRAME) {
				arrowInfo[i].ShotTimeCnt = INVERSION_FRAME;
			}
		}

		// ����F�Ȃ�
		if (arrowInfo[i].arrowtype == ARROW_TYPE_YELLOW) {
			if (arrowInfo[i].ShotTimeCnt == INVERSION_FRAME) {
				// ��̔��˕����ɑΉ�����悤�ɖ���ړ�������
				if(!arrowInfo[i].isInversioned)
					arrowInfo[i].isInversion = true;
			}
		}

		// ��]�t���O��ON�Ȃ�
		if (arrowInfo[i].isInversion) {
			arrowInfo[i].InversionAngle += 9.0f;
			arrowInfo[i].x = HEART_INIT_POS_X + cosf(((arrowInfo[i].angle) * 90 + arrowInfo[i].InversionAngle) * 3.14 / 180) * 120;
			arrowInfo[i].y = HEART_INIT_POS_Y + sinf(((arrowInfo[i].angle) * 90 + arrowInfo[i].InversionAngle) * 3.14 / 180) * 120;

			if (arrowInfo[i].InversionAngle > 180.0f) {
				// ��̌�����ύX����
				if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
					arrowInfo[i].angle = ARROW_ANGLE_RIGHT;
					arrowInfo[i].y = HEART_INIT_POS_Y;
				}
				else if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
					arrowInfo[i].angle = ARROW_ANGLE_DOWN;
					arrowInfo[i].x = HEART_INIT_POS_X;
				}
				else if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
					arrowInfo[i].angle = ARROW_ANGLE_LEFT;
					arrowInfo[i].y = HEART_INIT_POS_Y;
				}
				else if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
					arrowInfo[i].angle = ARROW_ANGLE_UP;
					arrowInfo[i].x = HEART_INIT_POS_X;
				}
				arrowInfo[i].InversionAngle = 0.0f;
				arrowInfo[i].isInversioned = true;
				arrowInfo[i].isInversion = false;
			}
		}
	}
}

// ��̒ʏ폈��
void Arrow::Step()
{
	// ��ˏ���
	IsShot();

	// ��̈ړ�����
	Move();
}

// ��̕`��
void Arrow::Draw()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			DrawRotaGraph((int)arrowInfo[i].x, (int)arrowInfo[i].y, 1.0f, 
				((arrowInfo[i].angle + 2) * 90 + arrowInfo[i].InversionAngle) * 3.14 / 180, arrowInfo[i].handle[arrowInfo[i].arrowtype], true);
		}
	}
}

// ��I������
void Arrow::Fin()
{
	for (int ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			DeleteGraph(arrowInfo[ArrowIndex].handle[ArrowType]);
		}
	}
}

// ��̃����_���v�f�����Z�b�g
void Arrow::ResetArrow(int _index)
{
	arrowInfo[_index].angle = (ARROW_ANGLE)GetRand(3);
	arrowInfo[_index].arrowtype = (ARROW_TYPE)GetRand(2);

	arrowInfo[_index].ShotInterval = GetRand(ARROW_MAX_INTERVAL);
	arrowInfo[_index].ShotTimeCnt = 0;
	arrowInfo[_index].InversionAngle = 0.0f;

	arrowInfo[_index].isInversioned = false;
}
