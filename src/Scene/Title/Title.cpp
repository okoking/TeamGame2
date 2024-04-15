#include"DxLib.h"
#include"../Title/Title.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../FrameRate/FrameRate.h"

SCENE_ID g_CurrentSceneID;	//�V�[���ϐ�

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

	////�����x�ݒ�
	//fade[0] = 0;
	//fade[1] = 0;
	//lighting = true;

	//�i�s�x
	progress = 1;

	////bgm
	//Sound::Bgm::Play(BGM_TITLE);

	//���ԉ�]
	gearAngle = 0.0f;

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//�ʏ폈��
void Title::Step()
{
	switch (progress)
	{
	case 0:	//��ʍ��

		

		//�^�C�g��
		/*if (titleY >= 0)
		{
			titleY = 0;
		}
		else
		{
			titleY += 0.5f;
		}*/

		////�ȏオ�������Ă���Ɛi�s
		//if (seaY == 0 && jettyY == 0 && titleY == 0 && fade[0])
		//{
		//progress++;
		//}

		break;

	case 1:	//���͑҂�

		////UI�̓_��
		////�����
		//if (lighting)
		//{
		//	fade[1] += 5;

		//	if (fade[1] >= 255)
		//	{
		//		lighting = false;
		//	}
		//}
		////������
		//else
		//{
		//	fade[1] -= 5;

		//	if (fade[1] <= 0)
		//	{
		//		lighting = true;
		//	}
		//}

		gearAngle+=0.1;
		lineX += 0.1;
		lineY += 0.1;
		lineW += 0.1;
		lineH += 0.1;

		//�X�y�[�X�L�[�ŉ�ʕω�
		if (Input::Key::Push(KEY_INPUT_SPACE))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);

			//�I��������
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;
		}

		break;


	default:
		break;
	}

	////��ʖ��������ɍ��N���b�N�Ŋ���
	//if (progress != 1 && Input::Mouse::Push(MOUSE_INPUT_LEFT))
	//{
	//	//���W�̐ݒ�
	//	seaY = 0;
	//	jettyY = 0;
	//	fade[0] = 255;
	//	titleY = 0;

	//	//���͑҂���
	//	progress = 1;
	//}

	////�_�̗���
	//for (int i = 0; i < 2; i++)
	//{
	//	cloudX[0][i] -= 0.3;
	//	cloudX[1][i] -= 0.5;
	//	cloudX[2][i] -= 0.4;
	//	cloudX[3][i] -= 0.1;
	//}
	
	////��ʊO�ɍs���ƌ��̈ʒu�ɖ߂�
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int n = 0; i < 2; i++)
	//	{
	//		if (cloudX[i][n] <= -SCREEN_SIZE_X)
	//		{
	//			cloudX[i][n] = SCREEN_SIZE_X;
	//		}
	//	}
	//}
	
}

//�`��
<<<<<<< HEAD
void Title::Draw()
{
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	//�^�C�g�����n
	DrawRotaGraph(-122, -106,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);
	DrawRotaGraph(-42, 410,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(578, 673, 1.0f, (int)gearAngle, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(-42, 410,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);
	DrawRotaGraph(34, 512,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);
	DrawRotaGraph(92, 429,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);
=======
void Title::Draw()//800 600
{	
	//�^�C�g�����n
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	

	//����
	DrawRotaGraph(15, 0,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);

	//����
	DrawRotaGraph(-42, 410,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR2], true);	
	DrawRotaGraph(34, 512,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(92, 429,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	
>>>>>>> 32f5009e637dd2695ea81e6d16b05cfab33da0fd

	//�E��
	DrawRotaGraph(760, 460,1.0f, (int)gearAngle*-1, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(663, 576,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	

	//�^�C�g�����̐� ���W�A������W�A�`�悷��T�C�Y�A�n���h���A�������A�摜���]�L��  421 43
	//DrawRectGraph(210, 344, lineX, lineY, lineW,lineH,imageHandle[TITLE_LINE], false,false);
	DrawRectGraph(210, 344, 421, 43, 421,43,imageHandle[TITLE_LINE], true,false);

//	//fade�œ����x�ύX
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
//	DrawGraphF(0, titleY, imageHandle[TITLE_TITLE], true);	//�^�C�g��
//	//�\�������ɖ߂�
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//
//	//fade�œ����x�ύX
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
//	DrawGraphF(0, 0, imageHandle[TITLE_START], true);	//���͑҂�
//	//�\�������ɖ߂�
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�I������
void Title::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_TITLE);
	
	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}