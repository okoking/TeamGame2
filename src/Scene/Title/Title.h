#pragma once

//�摜�̎��
enum TITLE_IMAGE_NUM
{
	//TITLE_SKY,	//��
	//TITLE_SEA,	//�C
	//TITLE_JETTY,	//�V��
	//TITLE_CLOUD1,	//�_1
	//TITLE_CLOUD2,	//�_2
	//TITLE_CLOUD3,	//�_3
	//TITLE_CLOUD4,	//�_4
	TITLE_TITLE,	//�^�C�g��
	//TITLE_START,	//���͑҂�
	TITLE_GEAR1,	//����
	TITLE_GEAR2,
	TITLE_GEAR3,

	TITLE_IMAGE_MAX_NUM,	//�摜��
};

//�摜�p�X
const char TITLE_IMAGE_PATH[TITLE_IMAGE_MAX_NUM][255] =
{
	"data/title/back.png",	//�^�C�g��
	"data/title/gear1.png",	//����1
	"data/title/gear2.png",	//����2
	"data/title/gear3.png",	//����3
	
	//"data/title/start.png",	//���͑҂�
};

class Title
{
private:
	int imageHandle[TITLE_IMAGE_MAX_NUM];	//�摜�n���h��

	//float seaY;	//�C�x
	//float jettyY;	//�V���x
	//float cloudX[4][2];	//�_�w
	//float cloudY;	//�_�w
	//float titleY;	//�^�C�g���x

	//int fade[2];	//�����x�F�^�C�g�� ���͑҂�

	//bool lighting;	//���͑҂��̓_��

	int progress;	//�i�s�x

	float gearAngle;	//���Ԃ̉�]

public:

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�I������
	void Fin();

};