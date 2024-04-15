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

	////座標の設定
	//seaY = 200;
	//jettyY = 200;

	//titleY =  - 100;

	//for (int i = 0; i < 4; i++)
	//{
	//	cloudX[i][0] = 0;
	//	cloudX[i][1] = SCREEN_SIZE_X;
	//}
	//cloudY = -20;

	//透明度設定
	//fade[0] = 0;

	//進行
	progress = 1;

	//bgm
	Sound::Bgm::Play(BGM_TITLE);

	//歯車回転
	gearAngle = 0.0f;

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;

	//ゲームモードを初期化
	g_GameModeID = GAME_MODE_EASY;
}

//通常処理
void Title::Step()
{
	switch (progress)
	{
	case 0:	//画面作り


		break;

	case 1:	//入力待ち

		//UIの点滅
		//現れる
		if (lighting)
		{
			fade[1] += 5;

			if (fade[1] >= 255)
			{
				lighting = false;
			}
		}
		//消える
		else
		{
			fade[1] -= 5;

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
	//タイトル下地
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	

	//左上
	DrawRotaGraph(15, 30,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);

	//左下
	DrawRotaGraph(0, 450,0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);	
	DrawRotaGraph(34, 552, 0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(92, 479, 0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);

	//右下
	DrawRotaGraph(760, 460,1.0f, (int)gearAngle*-1, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(663, 576,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	

	DrawRotaGraph(400, 440, 1.0f, 0.0f, imageHandle[TITLE_EASY+g_GameModeID], true);

	//タイトル下の線 座標、左上座標、描画するサイズ、ハンドル、透明化、画像反転有無  421 43
	DrawGraph(210, 310, imageHandle[TITLE_LINE], true);
	//DrawRotaGraph(400, 380, 1.0f,0.0f,imageHandle[TITLE_GEARHARF], true);


	//fadeで透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
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