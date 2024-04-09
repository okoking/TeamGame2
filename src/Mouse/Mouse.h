#pragma once

class Mouse
{
private:
	int x, y;		//���W
	int handle;		//�n���h��
	bool isUse;		//�g�p�t���O
	float angle;	//�p�x
	float size;		//�g�嗦

public:
	//������
	void Init(int pathNum=0);
	//�摜�ǂݍ���
	void Load(int pathNum);
	//�ʏ폈��
	void Step();
	//�}�E�X�̈ړ�����
	void Move();
	//�`��
	void Draw(int type=0);
	//�I������
	void FIn();

	//���W���擾
	int GetX() { return x; }
	int GetY() { return y; }

	//�g���Ă��邩�̊m�F
	bool CheckUse() { return isUse; }

	//�p�x���Z�b�g
	void SetAngle(float set) { angle = set; }
	//�g�嗦���Z�b�g
	void SetSize(float set) { size = set; }
	
	//�����蔻��
	bool MouseColli(int Ra, int Rx, int Ry);
	bool MouseColli(int Ax, int Ay, int Aw, int Ah);

	void SetUse(char set = '0');	//�g�p���Z�b�g�F�I��false
};
