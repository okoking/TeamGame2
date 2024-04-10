#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

const char PLAYER_PATH[] = {"data/play/player.png"};		//�v���C���[�̉摜�p�X

const int PLAYER_SIZE = 32;									//�v���C���[�摜�̃T�C�Y

// �v���C���[�̏����ʒu
const float PLAYER_POS_X = 400.0f;
const float PLAYER_POS_Y = 300.0f;

class Player
{
private:
	float posX, posY;		//�v���C���[�̍��W
	int ImageHundle;		//�v���C���[�摜�n���h��
	
public:
	//�v���C���[�̏�����
	void Init();

	//�v���C���[�̓ǂݍ��ݏ���
	void Load();

	//�v���C���[�̒ʏ폈��
	void Step();

	//�v���C���[�֘A�̕`�揈��
	void Draw();

	//�v���C���[�̏I������
	void Fin();

	//�v���C���[���쏈��
	void Operation();
};
