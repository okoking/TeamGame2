#include"DxLib.h"
#include"../Title/Title.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../FrameRate/FrameRate.h"

SCENE_ID g_CurrentSceneID;	//�V�[���ϐ�

//�Q�[�����[�h
GAME_MODE g_GameModeID;

//������
void Title::Init()
{
	//�摜�ǂݍ���
	for (int i = 0; i < TITLE_IMAGE_MAX_NUM; i++)
	{
		imageHandle[i] = LoadGraph(TITLE_IMAGE_PATH[i]);
	}

	////���W�̐ݒ�
	//seaY = 200;
	//jettyY = 200;

	//titleY =  - 100;

	//for (int i = 0; i < 4; i++)
	//{
	//	cloudX[i][0] = 0;
	//	cloudX[i][1] = SCREEN_SIZE_X;
	//}
	//cloudY = -20;

	//�����x�ݒ�
	//fade[0] = 0;

	//�i�s
	progress = 1;

	//bgm
	Sound::Bgm::Play(BGM_TITLE);

	//���ԉ�]
	gearAngle = 0.0f;

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;

	//�Q�[�����[�h��������
	g_GameModeID = GAME_MODE_EASY;
}

//�ʏ폈��
void Title::Step()
{
	switch (progress)
	{
	case 0:	//��ʍ��


		break;

	case 1:	//���͑҂�

		//UI�̓_��
		//�����
		if (lighting)
		{
			fade[1] += 5;

			if (fade[1] >= 255)
			{
				lighting = false;
			}
		}
		//������
		else
		{
			fade[1] -= 5;

			if (fade[1] <= 0)
			{
				lighting = true;
			}
		}

		gearAngle+=0.1f;
		

		//�X�y�[�X�L�[�ŉ�ʕω�
		if (Input::Key::Push(KEY_INPUT_SPACE))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);

			//�I��������
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;
		}

		//���L�[�ŏ�ԕω�
		if (g_GameModeID != GAME_MODE_EASY) {
			if (Input::Key::Push(KEY_INPUT_LEFT))
			{
				if(g_GameModeID== GAME_MODE_HARD)
					g_GameModeID= GAME_MODE_NORMAL;
				else
					g_GameModeID = GAME_MODE_EASY;
			}
		}
		if (g_GameModeID != GAME_MODE_HARD) {
			if (Input::Key::Push(KEY_INPUT_RIGHT))
			{
				if (g_GameModeID == GAME_MODE_EASY)
					g_GameModeID = GAME_MODE_NORMAL;
				else
					g_GameModeID = GAME_MODE_HARD;
			}
		}
		break;


	default:
		break;
	}

	
}


void Title::Draw()//800 600
{	
	//�^�C�g�����n
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	

	//����
	DrawRotaGraph(15, 30,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);

	//����
	DrawRotaGraph(0, 450,0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);	
	DrawRotaGraph(34, 552, 0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(92, 479, 0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);

	//�E��
	DrawRotaGraph(760, 460,1.0f, (int)gearAngle*-1, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(663, 576,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	

	DrawRotaGraph(400, 440, 1.0f, 0.0f, imageHandle[TITLE_EASY+g_GameModeID], true);

	//�^�C�g�����̐� ���W�A������W�A�`�悷��T�C�Y�A�n���h���A�������A�摜���]�L��  421 43
	DrawGraph(210, 310, imageHandle[TITLE_LINE], true);
	//DrawRotaGraph(400, 380, 1.0f,0.0f,imageHandle[TITLE_GEARHARF], true);


	//fade�œ����x�ύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
	DrawGraphF(300, 370, imageHandle[TITLE_START], true);	//���͑҂�
	//�\�������ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

//�I������
void Title::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_TITLE);
	
	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}