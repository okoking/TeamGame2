#include"DxLib.h"
#include"../Result/Result.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../Play/Play.h"

//初期化
void Rasult::Init()
{
	for (int i = 0; i < RESULT_IMAGE_MAX_NUM; i++)
	{
		//画像読み込み
		imageHandle[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}
	progress = 1;

	//bgm
	Sound::Bgm::Play(BGM_RESULT);

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//通常処理
void Rasult::Step()
{
	//左クリックで以下
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		//se
		Sound::Se::Play(SE_SYSTEM);

		//終了処理へ
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}
	
}

//描画
void Rasult::Draw()
{
	//背景描画
	DrawGraph(0, 0, imageHandle[RESULT_BACK_GROUND], true);

	//文字の大きさを変更
	SetFontSize(60);
	DrawFormatString(500, 300, GetColor(255, 255, 255), "%d", Score);
	
	//文字の大きさを変更
	//SetFontSize(80);
	
}

//終了処理
void Rasult::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_RESULT);

	//プレイ画面へ移行
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}