#include "Player.h"

//�v���C���[�̏�����
void Player::Init()
{
	//�v���C���[�̏�ԏ�����
	plStatus = Normal;

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

//�v���C���[�̏����l�ݒ�
void Player::SetDefaultValue()
{
	//�v���C���[�̏��
	plStatus = Normal;

	//�v���C���[�̍��W�̏�����
	posX = PLAYER_POS_X;		//X���W
	posY = PLAYER_POS_Y;		//Y���W
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

}
