#include "Player.h"
#include "../Input/Input.h"

//�v���C���[�̏�����
void Player::Init()
{
	//�v���C���[�̍��W�̏�����
	posX = 0;		//X���W
	posY = 0;		//Y���W

	//�v���C���[�̉摜�n���h���̏�����
	ImageHundle = -1;
}

//�v���C���[�̓ǂݍ��ݏ���
void Player::Load()
{
	ImageHundle = LoadGraph(PLAYER_PATH);
}

//�v���C���[�̒ʏ폈��
void Player::Step()
{
}

//�v���C���[�̕`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��
	DrawRotaGraph((int)posX, (int)posY, 1.0f, 0.0f, ImageHundle, true, false);
}

//�v���C���[�̏I������
void Player::Fin()
{
	// �v���C���[�摜�폜
	DeleteGraph(ImageHundle);
}

//�v���C���[�̑��쏈��
void Player::Operation()
{
	if (Input::Key::Push(KEY_INPUT_LEFT)) {

	}
	if (Input::Key::Push(KEY_INPUT_RIGHT)) {

	}
	if (Input::Key::Push(KEY_INPUT_UP)) {

	}
	if (Input::Key::Push(KEY_INPUT_DOWN)) {

	}


}
