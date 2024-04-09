#include "Lure.h"
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Scene/Scene.h"
#include "../../MathPlus/MathPlus.h"
#include "../../Effect/Effect.h"
#include "../../FrameRate/FrameRate.h"

// �R���X�g���N�^
Lure::Lure()
{
	// ���A�[�摜�n���h��
	for (int i = 0; i < LURE_IMAGE_TYPE_NUM; i++) {
		handle[i] = -1;
	}

	// ���݂̍��W
	_X = 0.0f;
	_Y = 0.0f;
	// �ړ���̍��W
	_SaveX = 0.0f;
	_SaveY = 0.0f;

	// �g�p�����ǂ���
	isActive = true;

	//���A�[�𓊂�����
	isUse = false;
	// ���A�[�𓊂��Ă��邩
	isThrow = false;
	// ���A�[����ʂ̍������ɂ��邩
	isLureLeft = false;
	// �������Ă��邩�ǂ���
	isCaught = false;

	fade = -1; //�����x
	fishingpower = 0; // �Ƃ�������

	// ���A�[�̃}�E�X
	LureMouse = {};
}

// ���W�X�V�p
void Lure::UpdatePos()
{
	_X = _SaveX;
	_Y = _SaveY;
}

// ������
void Lure::Init()
{ 
	// �g�p�����ǂ���
	isActive = false;
	//���A�[�𓊂�����
	isUse = false;
	// ���A�[�𓊂��Ă��邩
	isThrow = false;
	// �������Ă��邩�ǂ���
	isCaught = false;

	// ���݂̍��W
	_X = LURE_POS_X;
	_Y = LURE_POS_Y;

	// ���O�̍��W
	_SaveX = _X;
	_SaveY = _Y;

	// ���A�[�̃}�E�X����������
	LureMouse.Init();

	//�����x
	fade = 255;

	// �Ƃ�������
	fishingpower = 0;

	//�G�t�F�N�g�̏�����
	Effect::Init();
	//�G�t�F�N�g���w��̐��ǂݍ���
	Effect::Load(EFFECT_TYPE_RIPPLE,20);
	//�Ԋu�����Z�b�g
	effectInterval = 0;
	seFrg = false;
}

// �摜���[�h
void Lure::Load()
{
	// ���A�[�̉摜���[�h
	handle[LURE_IMAGE_TYPE_LURE] = LoadGraph(LURE_PATH);
	handle[LURE_IMAGE_TYPE_GAUGE] = LoadGraph(GAUGE_PATH);
	handle[LURE_IMAGE_TYPE_BAR] = LoadGraph(BAR_PATH);

}

// �}�E�X����
void Lure::Mouse()
{
	//���A�[���������Ă��Ȃ�������
	if (!isUse)
	{
		int zX = 0, zY = 0;	//�ꎞ�ۑ��p�̍��W

		// �}�E�X�̈ʒu���擾
		GetMousePoint(&zX, &zY);

		//���N���b�N�������ꂽ ���� �����Ă���r������Ȃ�
		if (Input::Mouse::Push(MOUSE_INPUT_LEFT) && !isThrow)
		{
			//���A�[�ݒu�͈͓��Ȃ�ȉ����s
			if (zX >= 30 && zX <= SCREEN_SIZE_X - 30 &&
				zY >= 30 && zY <= SCREEN_SIZE_Y - 145)
			{
				//�N���b�N�����ʒu�Ƀ��A�[��\��
				_SaveX = (float)zX;
				_SaveY = (float)zY;

				// �����Ă��锻��ɂ���
				isThrow = true;

				// ������ꂽ�ʒu����ʂ̍��������ǂ���
				if (_SaveX < LURE_POS_X) {
					isLureLeft = true;
				}
				else {
					isLureLeft = false;
				}

				//se
				Sound::Se::Play(SE_FISHING_ROD);

				//isActive = true;
			}
		}
	}
}

// �ړ�����
void Lure::Move()
{
	if (!isCaught) {
		// ���A�[�𓊂����Ȃ�
		if (isThrow) {
			// ���A�[���N���b�N�����Ƃ���܂ł������ړ�������
			_X += GetDirection(_SaveX, _SaveY, _X, _Y, 'x', 10);
			_Y += GetDirection(_SaveX, _SaveY, _X, _Y, 'y', 10);

			// �N���b�N�����Ƃ���܂œ�������~�܂�
			if ((isLureLeft && _X <= _SaveX) ||
				(!isLureLeft && _X >= _SaveX)) {
				_X = _SaveX; // �N���b�N�����Ƃ���܂œ�������~�܂�
			}

			if (_Y < _SaveY) {
				_Y = _SaveY; // �N���b�N�����Ƃ���܂œ�������~�܂�
			}

			// �N���b�N�����Ƃ���܂ňړ�������
			if (_X == _SaveX && _Y == _SaveY) {
				// �����Ă��Ȃ�
				isThrow = false;

				// �g�p���ɂ���
				isUse = true;

				//�g����o��
				effectInterval = 0.5f;

				//se
				Sound::Se::Play(SE_LURE);
			}
		}

		//���A�[�𓊂��ꂽ��
		if (isUse)
		{
			//���N���b�N�������������Ă�����
			if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
			{
				//�����l�Ɍ������Đi�s
				_X += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'x', 3);
				_Y += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'y', 3);

				//�g��̊Ԋu������
				effectInterval += 3.0f / FRAME_RATE;

				//�����l�͈̔́A20�ȓ��ɓ�������
				if (GetDistance(LURE_POS_X, LURE_POS_Y, _X, _Y) <= 20)
				{
					//�����l����
					_X = LURE_POS_X;
					_Y = LURE_POS_Y;

					//�g�p�t���O��܂�
					isUse = false;


					//isActive = false;
				}
			}

			//se�p����
			//���N���b�N�������ꂽ��
			if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
			{
				Sound::Bgm::Play(BGM_RECOVERY);
			}

			if(Input::Mouse::Release(MOUSE_INPUT_LEFT))
			{
				Sound::Bgm::StopSound(BGM_RECOVERY);
			}
		}
		else
		{
			//se
			Sound::Bgm::StopSound(BGM_RECOVERY);
		}
	}
}

// �ʏ폈��
void Lure::Step()
{
	//���A�[�����鏈��
	Mouse();
	//�������
	Move();
	// �ނ菈��
	Fishing();

	//�ȉ����o
	//���A�[���������Ă�����ȉ�
	if (isUse)
	{
		//�g��̊Ԋu�����Z
		effectInterval += 1.0f / FRAME_RATE;
		//�w��̎��ԂɂȂ�����
		if (effectInterval >= 0.7f)
		{
			//�G�t�F�N�g���o��
			Effect::Play(EFFECT_TYPE_RIPPLE, _X, _Y);
			//���Ԃ�������
			effectInterval = 0.0f;
		}
	}

	//�G�t�F�N�g�̒ʏ폈��
	Effect::Step();
}

// �摜�`��
void Lure::Draw()
{

	//�f�o�b�N�p�@���A�[�͈̔�
	DrawBox(30, 30, SCREEN_SIZE_X - 30, SCREEN_SIZE_Y - 145, GetColor(0, 0, 255), false);

	/*if (isActive) {*/

	//�G�t�F�N�g�`��
	Effect::Draw();

	//�����x�ύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawRotaGraph((int)_X, (int)_Y, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_LURE], true, false);
	//�\�������ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//DrawRotaGraph(500, 500, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_LURE], true, false);
	//}
	
	//�ނ莅
	DrawLine((int)_X, (int)_Y, (int)(LURE_POS_X - 2), (int)(LURE_POS_Y - 5), GetColor(255, 255, 255));

	if (isCaught) {
		DrawRotaGraph(GAUGE_POS_X, GAUGE_POS_Y, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_GAUGE], true, false);
		DrawRotaGraph(GAUGE_POS_X - GAUGE_SIZE_X / 2 + fishingpower, GAUGE_POS_Y, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_BAR], true, false);
	}
}

// �I������
void Lure::Fin()
{
	// ���A�[�̉摜�폜
	for (int i = 0; i < LURE_IMAGE_TYPE_NUM; i++) {
		DeleteGraph(handle[i]);
	}
}

// �ނ菈��
void Lure::Fishing()
{
	if (isCaught) {
		if (!seFrg)
		{
			seFrg = true;
			Sound::Bgm::Play(BGM_FISHING);
			Sound::Bgm::Play(BGM_FISH);
		}

		if (Input::Mouse::Keep(MOUSE_INPUT_LEFT)) {
			fishingpower += 3; // ���N���b�N��������Ă����power�������Ȃ�
		}
		else {
			fishingpower -= 3; // ������Ă��Ȃ��ƌ����Ă���
		}

		if (fishingpower > MAX_FISHING_POWER) {
			fishingpower = MAX_FISHING_POWER;
		}
		else if (fishingpower < 0) {
			fishingpower = 0;
		}

		// fishingpower�������͈̔͂Ȃ�
		// ����Փx�v����
		if (fishingpower >= 75 && fishingpower <= MAX_FISHING_POWER - 75) {
			//�����l�Ɍ������Đi�s
			_X += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'x', 1);
			_Y += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'y', 1);

			//�g��Ԋu������
			effectInterval += 3.0f / FRAME_RATE;
		}

		//�����l�͈̔́A10�ȓ��ɓ�������
		if (GetDistance(LURE_POS_X, LURE_POS_Y, _X, _Y) <= 10)
		{
			//�����l����
			_X = LURE_POS_X;
			_Y = LURE_POS_Y;

			//�g�p�t���O��܂�
			isUse = false;

			// fishingpower��������
			fishingpower = 0;

			//�������Ă��Ȃ��ɂ���
			isCaught = false;

			//se
			Sound::Se::Play(SE_FISH_GET);
		}

		////se�p����
		//	//���N���b�N�������ꂽ��
		//if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
		//{
		//	Sound::Bgm::Play(BGM_FISHING);
		//	Sound::Bgm::Play(BGM_FISH);
		//}

		//if (Input::Mouse::Release(MOUSE_INPUT_LEFT))
		//{
		//	Sound::Bgm::StopSound(BGM_FISHING);
		//	Sound::Bgm::StopSound(BGM_FISH);
		//}
	}
	else
	{
		seFrg = false;
		Sound::Bgm::StopSound(BGM_FISHING);
		Sound::Bgm::StopSound(BGM_FISH);
	}
}
