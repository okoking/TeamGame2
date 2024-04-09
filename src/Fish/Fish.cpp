#include "Fish.h"
#include "../Scene/Scene.h"
#include "../FrameRate/FrameRate.h"
#include "../Player/Lure/Lure.h"
#include "../MathPlus/MathPlus.h"

#include "DxLib.h"

Fish::Fish()
{
	//���̍ő吔�܂�for������
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// �n���h��
		handle[IMAGE_TYPE_NORMAL][FishIndex] = -1;
		handle[IMAGE_TYPE_CAUGHT][FishIndex] = -1;

		// ���݂̍��W
		_X[FishIndex] = 0.0f;
		_Y[FishIndex] = 0.0f;
		// ���O�̍��W
		_SaveX[FishIndex] = 0.0f;
		_SaveY[FishIndex] = 0.0f;
		
		// ���̈ړ����x
		fishSpeed[FishIndex] = 0;

		isLeft[FishIndex] = true; // ���������Ă��邩�ǂ���
		isActive[FishIndex] = false; // �����Ă��邩�ǂ���
		isCaught[FishIndex] = false; // �������Ă��邩�ǂ���
	}

	//�����o�Ă���܂ł̎���
	Poptime = 0;
	countTime = 0;

	CaughtNum = 0; // ���C�ނ�Ă��邩
}

// ���W�X�V�p
void Fish::UpdatePos()
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) 
	{
		_X[FishIndex] = _SaveX[FishIndex];
		_Y[FishIndex] = _SaveY[FishIndex];
	}
}

// isCaught�ύX�p(����:�z��ԍ�,�ύX��)
void Fish::SetisCaught(int FishIndex, bool _isCaught)
{
	isCaught[FishIndex] = _isCaught; // �������Ă��邩�ǂ���
}

// ������
void Fish::Init()
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// ���݂̍��W
		_X[FishIndex] = 0.0f;
		_Y[FishIndex] = 0.0f;

		// ���O�̍��W
		_SaveX[FishIndex] = _X[FishIndex];
		_SaveY[FishIndex] = _Y[FishIndex];

		isLeft[FishIndex] = true; // ���������Ă��邩�ǂ���
		isActive[FishIndex] = false; // �����Ă��邩�ǂ���
		isCaught[FishIndex] = false; // �������Ă��邩�ǂ���

		//���������Ă��邩�ǂ���
		if (GetRand(1) == 0)
		{
			isLeft[FishIndex] = true;
		}
		else
		{
			isLeft[FishIndex] = false;
		}
		
	}

	//�����o�Ă���܂ł̎���
	Poptime = 0;
	countTime = 0;

	CaughtNum = 0; // ���C�ނ�Ă��邩

	fishingChance = false;

	//���_���Z�̉摜�ǂݍ���
	scoreImageHandle = LoadGraph(SCORE_IMAGE_PATH);
	//���_���Z�̍��W�ǉ����ݒ�
	scoreAddY = 0;
	//���_���Z�̓����x�ݒ�
	scoreFade = 0;
	//���_���Z���o���s�t���O
	addScore = false;
}

// �摜���[�h
void Fish::Load()
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// ���̉摜���[�h
		handle[IMAGE_TYPE_NORMAL][FishIndex] = LoadGraph(FISH_PATH);
		handle[IMAGE_TYPE_CAUGHT][FishIndex] = LoadGraph(CAUGHT_FISH_PATH);
	}
}

// �ʏ폈��(����:���A�[�̍��W)
void Fish::Step(float lureX,float lureY, bool lureIsUse, bool lureIsCaught)
{
	//�ړ�����
	Move(lureX, lureY, lureIsUse, lureIsCaught);

	//�o������
	Pop();

	//�����������Ƃ�
	Caught(lureX, lureY);

	//���W�X�V����
	//UpdatePos();

	//���_���Z���o
	ScoreAddMove();
}

// �摜�`��
void Fish::Draw()
{
	//60%�ŕ`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * 0.6));

	//���̍ő吔�܂�for������
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) 
	{
		//�����g�p���Ȃ�`��
		if (isActive[FishIndex])
		{
			if (!isCaught[FishIndex]) {
				// �������Ă��Ȃ��Ƃ��͋��̂�����
				DrawRotaGraph((int)_X[FishIndex], (int)_Y[FishIndex],
					1.0f, angle[FishIndex], handle[IMAGE_TYPE_NORMAL][FishIndex], true, isLeft[FishIndex]);
			}
			else {
				// ���������Ƃ��͉e
				DrawRotaGraph((int)_X[FishIndex], (int)_Y[FishIndex],
					1.0f, 0.0f, handle[IMAGE_TYPE_CAUGHT][FishIndex], true, isLeft[FishIndex]);
			}
		}

		//DrawFormatString(30, 30, GetColor(255, 0, 0), "%d", Poptime);
	}

	//�\�������ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�����̑傫����ύX
	SetFontSize(40);
	// �ނꂽ���̕\��
	DrawFormatString(657, 600 - 80, GetColor(59, 45, 45), "%d", CaughtNum);
	//�����̑傫�������ɖ߂�
	SetFontSize(20);

	//�����x�ύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, scoreFade);
	DrawRotaGraph(700, 500+ scoreAddY, 1.0f, 0.0f, scoreImageHandle, true);
	//�\�������ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// �I������
void Fish::Fin()
{
	//���̍ő吔�܂�for������
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// ���̉摜�폜
		DeleteGraph(handle[IMAGE_TYPE_NORMAL][FishIndex]);
	}
}

//�ړ�����
void Fish::Move(float lureX,float lureY,bool lureIsUse,bool lureIsCaught)
{	
	fishingChance = false;
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) 
	{
		//�����ňȉ�
		if (isActive[FishIndex])
		{
			//���A�[�̈�苗���ɓ������烋�A�[��ǐ�==================================
			if (GetDistance(_X[FishIndex], _Y[FishIndex], lureX, lureY) <= 100&&
				lureIsUse&&	//���A�[�𓊂��Ă���
				!lureIsCaught&&	//hit���Ă��Ȃ�
				!fishingChance)	//�܂���C���������ĂȂ�
			{
				_X[FishIndex] += GetDirection(lureX, lureY, _X[FishIndex], _Y[FishIndex], 'x', 0.5f);
				_Y[FishIndex] += GetDirection(lureX, lureY, _X[FishIndex], _Y[FishIndex], 'y', 0.5f);

				//������ς���
				if (isLeft[FishIndex])
				{
					
					angle[FishIndex] = GetAngle(_X[FishIndex], _Y[FishIndex], lureX, lureY);
				}
				else
				{
					angle[FishIndex] = GetAngle(lureX, lureY, _X[FishIndex], _Y[FishIndex]);
				}

				//��C�������A�[�ɔ�������悤�ɂ���
				fishingChance = true;
			}

			//�ʏ�ړ�===============================================================
			else
			{
				// ���̈ړ�����
				if (isLeft[FishIndex]) {
					_X[FishIndex] -= fishSpeed[FishIndex]; // ���������Ă���Ƃ����ɓ���
					angle[FishIndex] = 0;
				}
				else {
					_X[FishIndex] += fishSpeed[FishIndex]; // �E�������Ă���Ƃ��ɉE�ɓ���
					angle[FishIndex] = 0;
				}

				// ������ʊO�ɍs�����Ƃ�
				//��
				if (isLeft[FishIndex])
				{
					if (_X[FishIndex] < -(FISH_X_SIZE / 2))
					{
						isActive[FishIndex] = false; // �����E��
					}
				}
				//��
				else
				{
					if (_X[FishIndex] > SCREEN_SIZE_X + FISH_X_SIZE / 2)
					{
						isActive[FishIndex] = false; // �����E��
					}
				}
			}
		}
	}

}

//�o�����ԊǗ�����
void Fish::SetPopTime()
{
	countTime += 1.0f / FRAME_RATE;	//���Ԃ��J�E���g
}

//���o��
void Fish::Pop()
{
	//�o�����ԊǗ�����
	SetPopTime();

	//�J�E���g���o�����Ԃ��z������
	if (countTime > Poptime)
	{
		for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++)
		{
			//�g�p����ĂȂ�������ȉ����s
			if (!isActive[FishIndex])
			{
				//���������Ă��邩�ǂ����@�����_���Ō���
				//��
				if (GetRand(1) == 0)
				{
					isLeft[FishIndex] = true;
				}
				//��
				else
				{
					isLeft[FishIndex] = false;
				}

				//���E����ʒu��ݒ�
				if (isLeft[FishIndex])
				{
					//�E�[�ɐݒ�
					_X[FishIndex] = (float)(SCREEN_SIZE_X + FISH_X_SIZE / 2);
					_Y[FishIndex] = (float)(GetRand(SCREEN_SIZE_Y - 145 - 30) + 30);
				}
				else
				{
					//���[�ɐݒ�
					_X[FishIndex] = 0 - FISH_X_SIZE / 2;
					_Y[FishIndex] = (float)(GetRand(SCREEN_SIZE_Y - 145 - 30) + 30);
				}

				//�����g�p���ɂ���
				isActive[FishIndex] = true;

				// �������Ă��Ȃ��ɂ���
				isCaught[FishIndex] = false;

				//���̃X�s�[�h��ݒ�
				fishSpeed[FishIndex] = GetRand((int)FISH_SPEED - 1) + 1;

				//���̏o�����Ԃ�ݒ�
				Poptime = GetRand(FISH_POP_TIME) + 1;
				//�J�E���g�����Z�b�g
				countTime = 0;

				break;
			}
		}
	}
}

//�����������Ƃ�(����:���A�[�̍��W)
void Fish::Caught(float lureX, float lureY)
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		if (isCaught[FishIndex]) {
			// �������A�[�̈ʒu�܂ňړ�
			_X[FishIndex] = lureX;
			_Y[FishIndex] = lureY;

			//�ނꂽ
			if (_X[FishIndex] == LURE_POS_X && _Y[FishIndex] == LURE_POS_Y) {
				// �t���O��������
				isCaught[FishIndex] = false;
				isActive[FishIndex] = false;

				CaughtNum++; // �ނ�Ă��鐔�����Z

				fishChance = false;

				//���_���Z���o==========================
		
				//���_���Z�̍��W�ǉ����ݒ�
				scoreAddY = 0;
				//���_���Z�̓����x�ݒ�
				scoreFade = 255;
				//���_���Z���o��
				addScore = true;
			}
		}
	}
}

//���_���Z�̓���
void Fish::ScoreAddMove()
{
	if (addScore)
	{
		if (scoreAddY < 50)
		{
			scoreAddY += 2;
		}
		else
		{
			scoreAddY = 50;
		}

		if (scoreFade > 0)
		{
			scoreFade -= 20;
		}
		else
		{
			scoreFade = 0;
		}

		if (scoreAddY == 50 && scoreFade == 0)
		{
			addScore = false;
		}
	}
	
}