#pragma once
#include "../../Scene/Scene.h"
#include "DxLib.h"
#include "../../Player/Player.h"
#include "../../Fish/Fish.h"
#include "../../Mouse/Mouse.h"
#include "../../TimeLimit/TimeLimit.h"
#include "../../Collision/Collision.h"
#include "../../Player/Lure/Lure.h"
#include "../../MathPlus/MathPlus.h"




class Play
{
private:
	//�N���X�̕ϐ��錾
	Player player;			//�v���C���[�N���X
	
	Collision collision;	//�����蔻��
	Lure lure;				//���A�[

	int backgroundHandle;	//�w�i�摜�n���h��
	int jettyHandle;		//�V���摜�n���h��
	int scoreImageHandle;	//�X�R�A�{�[�h�摜�n���h��

	//���ƃ��A�[�������������ǂ����̊m�F�t���O
	bool IsFishToLureHit;

	float caughtCountTime;
	int fishingChanceNum;
	

	//�m�F�p�ϐ�
	float num = 0;
	char moji[256] = "x";

public:
	//�v���C�V�[���̏�����
	void Init();

	//�v���C�V�[���̏����l�ݒ�
	void SetDefaultValue();

	//�v���C�V�[���̓ǂݍ���
	void Load();

	//�v���C�V�[���̒ʏ폈��
	void Step();

	//�v���C�V�[���̕`�揈��
	void Draw();

	//�v���C�V�[���̏I������
	void Fin();

	//���ƃ��A�[�̓����蔻��
	bool FishToLureCollision();

	//���ƃ��A�[������������
	void FishToLureHit();

};
