#include"DxLib.h"
#include"../Title/Title.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../FrameRate/FrameRate.h"

SCENE_ID g_CurrentSceneID;	//シーン変数

//ゲームモード
GAME_MODE g_GameModeID;

//初期化
void Title::Init()
{
	//画像読み込み
	for (int i = 0; i < TITLE_IMAGE_MAX_NUM; i++)
	{
		imageHandle[i] = LoadGraph(TITLE_IMAGE_PATH[i]);
	}

	//bgm
	Sound::Bgm::Play(BGM_TITLE);
	Sound::Bgm::SetVolume(BGM_TITLE,50);
	//歯車回転
	gearAngle = 0.0f;

	//透過点滅
	fade[0] = 0;
	fade[1] = 0;

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;

	//ゲームモードを初期化
	g_GameModeID = GAME_MODE_EASY;
}

//通常処理
void Title::Step()
{
	//現れる
	if (lighting)
	{
		fade[0] += 4;
		fade[1] += 7;

		if (fade[0] >= 255)
		{
			lighting = false;
		}
		if (fade[1] >= 255)
		{
			lighting = false;
		}
	}
	//消える
	else
	{
		fade[0] -= 4;
		fade[1] -= 7;

		if (fade[0] <= 0)
		{
			lighting = true;
		}
		if (fade[1] <= 0)
		{
			lighting = true;
		}
	}

	gearAngle+=0.1f;
		

	//スペースキーで画面変化
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		//se
		Sound::Se::Play(SE_SYSTEM);

		//終了処理へ
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}

	//矢印キーで状態変化
	if (g_GameModeID != GAME_MODE_EASY) {
		if (Input::Key::Push(KEY_INPUT_LEFT))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);
			if(g_GameModeID== GAME_MODE_HARD)
				g_GameModeID= GAME_MODE_NORMAL;
			else
				g_GameModeID = GAME_MODE_EASY;
		}
	}
	if (g_GameModeID != GAME_MODE_HARD) {
		if (Input::Key::Push(KEY_INPUT_RIGHT))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);
			if (g_GameModeID == GAME_MODE_EASY)
				g_GameModeID = GAME_MODE_NORMAL;
			else
				g_GameModeID = GAME_MODE_HARD;
		}
	}
	
}


void Title::Draw()//800 600
{	
	//タイトル下地
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	

	//左上
	DrawRotaGraph(15, 30,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);

	//左下
	DrawRotaGraph(0, 450,0.5, (int)gearAngle*-1+0.4, imageHandle[TITLE_GEAR2], true);	
	DrawRotaGraph(34, 552, 0.5, (int)gearAngle*-1+0.1, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(92, 479, 0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);

	//右下
	DrawRotaGraph(760, 460,1.0f, (int)gearAngle*-1+0.5, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(663, 576,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	

	DrawRotaGraph(400, 440, 1.0f, 0.0f, imageHandle[TITLE_EASY+g_GameModeID], true);

	//タイトル下の線 座標、左上座標、描画するサイズ、ハンドル、透明化、画像反転有無  421 43
	DrawGraph(210, 310, imageHandle[TITLE_LINE], true);
	//DrawRotaGraph(400, 380, 1.0f,0.0f,imageHandle[TITLE_GEARHARF], true);

	//矢印
	if (g_GameModeID != GAME_MODE_NORMAL) {
		//fadeで透明度変更
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
		DrawRotaGraph(250, 440, 0.5, 0, imageHandle[TITLE_ARROW2], true);
		DrawRotaGraph(540, 440, 0.5, 0.0f, imageHandle[TITLE_ARROW], true);
		//表示を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	else {
		//fadeで透明度変更
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
		DrawRotaGraph(200, 440, 0.5, 0, imageHandle[TITLE_ARROW2], true);
		DrawRotaGraph(590, 440, 0.5, 0.0f, imageHandle[TITLE_ARROW], true);
		//表示を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

	//fadeで透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
	DrawGraphF(300, 370, imageHandle[TITLE_START], true);	//入力待ち
	//表示を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

//終了処理
void Title::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_TITLE);
	
	//プレイ画面へ移行
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}