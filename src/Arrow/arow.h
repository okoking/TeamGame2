#pragma once
#include "../Player/Player.h"

#define ARROW_MAX_NUM	(6)						//��̍ő吔�i�n���h���̐��j

// ��̑��x
const float ARROW_SPEED = 4.0f;
const int ARROW_MAX_INTERVAL = 120; // ���̖�o�Ă���܂ł̊Ԋu
const int INVERSION_FRAME = 50; // ���˂���Ă��甽�]����܂ł̃t���[��

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
const char REDARROW_PATH[] = { "data/play/kari_arrow2.png" };
const char YELLOWARROW_PATH[] = { "data/play/kari_arrow1.png" };

// �摜�T�C�Y
const float ARROW_SIZE_X = 48;
const float ARROW_SIZE_Y = 32;

// �����ɔ��˂���Ȃ��P�\
const int RECOVERY_MAX_FRAME = 20;

struct ArrowInfo
{
	int handle[ARROW_TYPE_NUM];		//�摜�n���h��
	ARROW_ANGLE angle;			// ��̌����ۑ��p
	ARROW_TYPE arrowtype;	// ��̎�ޕۑ��p

	float x, y;		//���W
	float xspeed, yspeed;	// �ړ����x
	int ShotInterval;	// ���ˊԊu
	bool isUse;		//�g�p���t���O
	bool isInversion; // ��]���t���O
	bool isInversioned; // ��]�I���m�F�t���O
	int InversionCnt; // ���]�p�x�J�E���g�p
	int ShotTimeCnt; // ���˂���Ă���̃t���[���J�E���g�p
	float InversionAngle; // ���]����]���Ă��邵�Ă���p�x
};

class Arrow
{
private:
	ArrowInfo arrowInfo[ARROW_MAX_NUM] = { 0 };
	int Recoverycnt;	// �����ɔ��˂���Ȃ��悤�ɂ���

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

	// ��̎�ގ擾�p
	ARROW_TYPE GetArrowType(int _index) { return arrowInfo[_index].arrowtype; }

	// ��]���t���O�擾�p
	bool GetisInversion(int _index){return arrowInfo[_index].isInversion;}
};