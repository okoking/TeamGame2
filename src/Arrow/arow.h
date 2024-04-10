#pragma once

#define BULLET_MAX_NUM	(3)						//�e�̍ő吔�i�n���h���̐��j
struct ArrowInfo
{
	int handle;		//�摜�n���h��
	int x, y;		//���W
	bool isUse;		//�g�p���t���O
};

class Arrow
{
public:
	ArrowInfo arrowInfo[BULLET_MAX_NUM] = { 0 };
	Arrow();
	~Arrow();

	// �e������
	void Init();

	// �e���ˏ���
	bool IsShot(int shotPosX, int shotPosY);

	// �e�̈ړ�����
	void Move();

	// �e�̕`��
	void Draw();

	// �w�肳�ꂽ�e���\���̂̎g�p���t���O���擾
	bool IsUse(int _index) { return arrowInfo[_index].isUse; }

	// �w�肳�ꂽ�e���\���̂̎g�p���t���O��ݒ�
	void SetUse(int _index, bool _isUse) { arrowInfo[_index].isUse = _isUse; }

	// �w�肳�ꂽ�e���\���̂�X���W���擾
	int GetPosX(int _index) { return arrowInfo[_index].x; }

	// �w�肳�ꂽ�e���\���̂�Y���W���擾
	int GetPosY(int _index) { return arrowInfo[_index].y; }
};