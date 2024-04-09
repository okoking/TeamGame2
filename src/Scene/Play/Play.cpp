#include "Play.h"
#include "../../FrameRate/FrameRate.h"

//�摜�p�X
const char BACKGROUND_PATH[] = { "data/play/backGround.png" };		//�v���C�V�[���̔w�i�摜�̃p�X
const char JETTY_PATH[] = { "data/play/jetty.png" };					//�v���C�V�[���̎V���摜�̃p�X
const char SCORE_BOARD_PATH[] = { "data/play/scoreBoard.png" };					//�v���C�V�[���̎V���摜�̃p�X

TimeLimit timeLimit;	//���Ԑ���

Fish fish;				//���N���X

bool fishChance;	//hit��ԃt���O

//�v���C�V�[���̏�����
void Play::Init()
{
	
	IsFishToLureHit = false;		//���ƃ��A�[�������������ǂ����̊m�F�t���O�̏�����

	player.Init();					//�v���C���[�̏�����
	fish.Init();					//�t�B�b�V���̏�����
	lure.Init();					//���A�[�̏�����

	//�������Ԃ̏�����
	timeLimit.Init();

	caughtCountTime = 0;
	fishChance = false;
	fishingChanceNum = 0;

	//bgm
	Sound::Bgm::Play(BGM_PLAY);
	Sound::Bgm::Play(BGM_SEA);

	//�v���C�V�[���̒ʏ폈���ɑJ��
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���̏����l�ݒ�
void Play::SetDefaultValue()
{
	//�v���C���[�̏����l�ݒ�
	player.SetDefaultValue();
}

//�v���C�V�[���̓ǂݍ���
void Play::Load()
{
	//�摜�ǂݍ���
	//�w�i�֘A
	backgroundHandle = LoadGraph(BACKGROUND_PATH);	//�w�i
	jettyHandle = LoadGraph(JETTY_PATH);			//�V��
	scoreImageHandle = LoadGraph(SCORE_BOARD_PATH);			//�X�R�A�{�[�h
	
	//�v���C���[�֘A
	player.Load();									//�v���C���[�摜�̓ǂݍ���
	fish.Load();									//�t�B�b�V���̉摜�̓ǂݍ���
	lure.Load();									//���A�[�摜�̓ǂݍ���
}

//�v���C���[�V�[���̒ʏ폈��
void Play::Step()
{
	player.Step();			//�v���C���[�̒ʏ폈��
	fish.Step(lure.GetXPos(),lure.GetYPos(),lure.GetisUse(),lure.GetisCaught());			//�t�B�b�V���̒ʏ폈��
	lure.Step();			//���A�[�̒ʏ폈��

	//���ƃ��A�[�������������ǂ������m�F����t���O�ɑ��
	IsFishToLureHit = FishToLureCollision();

	//�m�F
	FishToLureHit();

	//�������Ԃ̒ʏ폈��
	timeLimit.Step();
	
}

//�v���C���[�V�[���̕`�揈��
void Play::Draw()
{
	//�w�i�`��
	DrawGraph(0, 0, backgroundHandle, true);	//�w�i
	DrawGraph(0, 0, jettyHandle, true);	//�V��
	DrawGraph(600, 500, scoreImageHandle, true);	//�X�R�A�{�[�h

	//�������Ԃ̕`��
	timeLimit.Draw();

	fish.Draw();		//�t�B�b�V���摜�̕`��
	lure.Draw();		//���A�[�摜�̕`��		
	player.Draw();		//�v���C���[�摜�̕`��

	//�����̑傫����ύX
	SetFontSize(20);
	//�������������
	DrawFormatString(20, 465, GetColor(255, 255, 255), "�N���b�N�����ʒu�Ƀ��A�[�𓊂���");
	//�����̑傫�������ɖ߂�
	SetFontSize(20);

	//�m�F
	//if (IsFishToLureHit)
		//DrawFormatString(100, 100, GetColor(255, 0, 0), "%f", num);

	//for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
	//	if (fish.GetisCaught(FishIndex))
	//		DrawFormatString(100, 100, GetColor(255, 0, 0), "%f", num);
	//}

}

//�v���C���[�V�[���̏I������
void Play::Fin()
{
	lure.Fin();			//���A�[�̏I������
	player.Fin();		//�v���C���[�̏I������
	fish.Fin();			//�t�B�b�V���̏I������

	//�������Ԃ̏I������
	timeLimit.Fin();

	//gem
	Sound::Bgm::StopSound(BGM_PLAY);
	Sound::Bgm::StopSound(BGM_SEA);

	Sound::Bgm::StopSound(BGM_FISH);
	Sound::Bgm::StopSound(BGM_FISHING);
	Sound::Bgm::StopSound(BGM_RECOVERY);

	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

//���ƃ��A�[�̓����蔻��
bool Play::FishToLureCollision()
{
	//���A�[�𓊂��Ă��邩
	if (lure.GetisUse())
	{
		//���̐���for������
		for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
			// ���������Ă���Ȃ��΂�
			if (lure.GetisCaught())
				continue;

			//���������Ă��邩�ǂ���
			if (fish.GetIsActive(FishIndex)) {

				//��苗���ɓ�������ȉ�
				if (GetDistance(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex)) < 50)
				{
					if (!fishChance)
					{
						//�R�O���̊m����hit
						if (GetRand(100) < 30)
						{
							//se
							Sound::Se::Play(SE_LURE);

							//�����e�ɂ���
							fish.SetisCaught(FishIndex, true);

							//�`�����X�Ɉڍs
							fishChance = true;
							//���A�[�̓����x��ς���
							lure.SetFade(255 * 0.5);

							//hit���������L�^
							fishingChanceNum = FishIndex;
						}
						//hit���Ȃ�����
						else
						{
							//se
							Sound::Se::Play(SE_HIT);

							//������������
							if (fish.GetIsLeft(FishIndex))
							{
								fish.AddPosX(FishIndex, -50);
							}
							else
							{
								fish.AddPosX(FishIndex, 50);
							}
						}
					}
				}
				//���ƃ��A�[�̓����蔻��
				//if (GetDistance(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex)) < 70)
				//{
				//	// �ǂ̋��������������𓯎��ɂƂ�
				//	fish.SetisCaught(FishIndex, true);
				//	lure.SetisCaught(true);

				//	return true;
				//}
			}
		}

		//hit���ނ�~�j�Q�[��������Ȃ�
		if (fishChance&&!lure.GetisCaught())
		{
			//�����e�Ȃ�
			if (fish.GetisCaught(fishingChanceNum))
			{
				//���W�����A�[�ɌŒ�
				fish.SetPosX(fishingChanceNum, lure.GetXPos());
				fish.SetPosY(fishingChanceNum, lure.GetYPos());
			}

			//hit�������Ԃ����Z
			caughtCountTime += 1.0f / FRAME_RATE;

			//�������Ԃ���b�ȉ��Ȃ�ȉ�
			if (caughtCountTime <= 1.0f)
			{
				//���N���b�N�Ń~�j�Q�[����
				if (Input::Mouse::Push(MOUSE_INPUT_LEFT))
				{
					// �ǂ̋��������������𓯎��ɂƂ�
					fish.SetisCaught(fishingChanceNum, true);
					lure.SetisCaught(true);
					caughtCountTime = 0.0f;

					return true;
				}
			}
			//hit�������Ԃ��z����
			else
			{
				//����������i�����t���O��܂�j
				fish.SetIsActive(fishingChanceNum, false);
				//hit���ĂȂ�
				fishChance = false;
				//�������Ԃ̃��Z�b�g
				caughtCountTime = 0.0f;

				//���A�[�̓����x�����ɖ߂�
				lure.SetFade(255);
			}
		}
	}

	//hit���Ă��Ȃ������烋�A�[�̓����x�͍ő�
	if (!fishChance)
	{
		lure.SetFade(255);
	}


	return false;
}

//���ƃ��A�[������������
void Play::FishToLureHit()
{
	if (IsFishToLureHit)
	{
		for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
			fish.SetHitUpdatePosX(GetDirection(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex), 'x', 1), FishIndex);
			fish.SetHitUpdatePosX(GetDirection(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex), 'x', 1), FishIndex);
		}
	}
}
