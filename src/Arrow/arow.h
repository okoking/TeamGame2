#pragma once
#include "../Player/Player.h"

#define ARROW_MAX_NUM	(2)						//��̍ő吔�i�n���h���̐��j

// ��̑��x
const float ARROW_SPEED = 4.0f;
const int ARROW_MAX_INTERVAL = 180;

// ��̎��
enum ARROW_TYPE {
	ARROW_TYPE_NORMAL = 0,
	ARROW_TYPE_RED,
	ARROW_TYPE_YELLOW,

	ARROW_TYPE_NUM,
};

// ��̗������
enum ARROW_ANGLE {
	ARROW_ANGLE_RIGHT = 0,
	ARROW_ANGLE_DOWN,
	ARROW_ANGLE_LEFT,
	ARROW_ANGLE_UP,
};

// ��̉摜�t�@�C���p�X
const char NORMALARROW_PATH[] = { "data/play/kari_arrow.png" };

// �摜�T�C�Y
const float ARROW_SIZE_X = 64;
const float ARROW_SIZE_Y = 32;

struct ArrowInfo
{
	int handle[ARROW_TYPE_NUM];		//�摜�n���h��
	ARROW_ANGLE angle;			// ��̌����ۑ��p
	ARROW_TYPE arrowtype;	// ��̎�ޕۑ��p

	float x, y;		//���W
	float xspeed, yspeed;	// �ړ����x
	int ShotInterval;	// ���ˊԊu
	bool isUse;		//�g�p���t���O
};

class Arrow
{
private:
	ArrowInfo arrowInfo[ARROW_MAX_NUM] = { 0 };

public:
	Arrow();
	~Arrow();

	// �����
	void Init();

	// �f�[�^���[�h
	void Load();

	// ��ˏ���
	void IsShot();

	// ��̈ړ�����
	void Move();

	// ��̒ʏ폈��
	void Step();

	// ��̕`��
	void Draw();

	// ��I������
	void Fin();

	// �w�肳�ꂽ����\���̂̎g�p���t���O���擾
	bool IsUse(int _index) { return arrowInfo[_index].isUse; }

	// �w�肳�ꂽ����\���̂̎g�p���t���O��ݒ�
	void SetUse(int _index, bool _isUse) { arrowInfo[_index].isUse = _isUse; }

	// �w�肳�ꂽ����\���̂�X���W���擾
	float GetPosX(int _index) { return arrowInfo[_index].x; }

	// �w�肳�ꂽ����\���̂�Y���W���擾
	float GetPosY(int _index) { return arrowInfo[_index].y; }

	// �w�肳�ꂽ��̌������擾
	ARROW_ANGLE GetArrowAngle(int _index) { return arrowInfo[_index].angle; }

	// ��̃����_���v�f�����Z�b�g
	void ResetArrow(int _index);
};