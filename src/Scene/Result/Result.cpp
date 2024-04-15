#include"DxLib.h"
#include"../Result/Result.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../Play/Play.h"

//������
void Rasult::Init()
{
	for (int i = 0; i < RESULT_IMAGE_MAX_NUM; i++)
	{
		//�摜�ǂݍ���
		imageHandle[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}

	/*y = 0;
	fade[0] = 0;
	fade[1] = 0;
	lighting = false;*/
	progress = 1;

	//bgm
	Sound::Bgm::Play(BGM_RESULT);

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�ʏ폈��
void Rasult::Step()
{
	switch (progress)
	{
	case 0:	//�X�R�A�\��


		break;

	case 1:	//���͑҂�


		//���N���b�N�ňȉ�
		if (Input::Key::Push(KEY_INPUT_SPACE))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);

			//�I��������
			g_CurrentSceneID = SCENE_ID_FIN_RESULT;
		}

		break;

		
	default:
		break;
	}
	
}

//�`��
void Rasult::Draw()
{
	//�w�i�`��
	DrawGraph(0, 0, imageHandle[RESULT_BACK_GROUND], true);

	//�����̑傫����ύX
	SetFontSize(60);
	DrawFormatString(500, 300, GetColor(255, 255, 255), "%d", Score);
	////�����̑傫����ύX
	//SetFontSize(80);

	
}

//�I������
void Rasult::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_RESULT);

	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}