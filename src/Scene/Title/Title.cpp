#include"DxLib.h"
#include"../Title/Title.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../FrameRate/FrameRate.h"

SCENE_ID g_CurrentSceneID;	//シーン変数

//初期化
void Title::Init()
{
	//画像読み込み
	for (int i = 0; i < TITLE_IMAGE_MAX_NUM; i++)
	{
		imageHandle[i] = LoadGraph(TITLE_IMAGE_PATH[i]);
	}

	//座標の設定
	seaY = 200;
	jettyY = 200;

	titleY =  - 100;

	for (int i = 0; i < 4; i++)
	{
		cloudX[i][0] = 0;
		cloudX[i][1] = SCREEN_SIZE_X;
	}
	cloudY = -20;

	//透明度設定
	fade[0] = 0;
	fade[1] = 0;
	lighting = true;

	//進行度
	progress = 0;

	//bgm
	Sound::Bgm::Play(BGM_TITLE);

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//通常処理
void Title::Step()
{
	switch (progress)
	{
	case 0:	//画面作り

		//海
		if (seaY <= 0)
		{
			seaY = 0;
		}
		else
		{
			seaY -= 1.4f;
		}

		//桟橋
		if (jettyY <= 0)
		{
			jettyY = 0;
		}
		else
		{
			jettyY -= 1.2f;
		}

		//タイトル透明度
		if (fade[0] >= 255)
		{
			fade[0] = 255;
		}
		else
		{
			fade[0] += 1;
		}

		//タイトル
		if (titleY >= 0)
		{
			titleY = 0;
		}
		else
		{
			titleY += 0.5f;
		}

		//以上が完成していると進行
		if (seaY == 0 && jettyY == 0 && titleY == 0 && fade[0])
		{
			progress++;
		}

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

		//左クリックで以下
		if (Input::Mouse::Push(MOUSE_INPUT_LEFT))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);

			//終了処理へ
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;
		}

		break;


	default:
		break;
	}

	//画面未完成時に左クリックで完成
	if (progress != 1 && Input::Mouse::Push(MOUSE_INPUT_LEFT))
	{
		//座標の設定
		seaY = 0;
		jettyY = 0;
		fade[0] = 255;
		titleY = 0;

		//入力待ちへ
		progress = 1;
	}

	//雲の流れ
	for (int i = 0; i < 2; i++)
	{
		cloudX[0][i] -= 0.3;
		cloudX[1][i] -= 0.5;
		cloudX[2][i] -= 0.4;
		cloudX[3][i] -= 0.1;
	}
	
	//画面外に行くと元の位置に戻す
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; i < 2; i++)
		{
			if (cloudX[i][n] <= -SCREEN_SIZE_X)
			{
				cloudX[i][n] = SCREEN_SIZE_X;
			}
		}
	}
	
}

//描画
void Title::Draw()
{
	DrawGraphF(0, 0, imageHandle[TITLE_SKY], true);	//空
	DrawGraphF(0, seaY, imageHandle[TITLE_SEA], true);	//海
	DrawGraphF(0, jettyY, imageHandle[TITLE_JETTY], true);	//桟橋

	//雲
	for (int i = 0; i < 4; i++)
	{
		DrawGraphF(cloudX[i][0], cloudY, imageHandle[TITLE_CLOUD1 + i], true);
		DrawGraphF(cloudX[i][1], cloudY, imageHandle[TITLE_CLOUD1 + i], true);
	}

	//fadeで透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
	DrawGraphF(0, titleY, imageHandle[TITLE_TITLE], true);	//タイトル
	//表示を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//fadeで透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
	DrawGraphF(0, 0, imageHandle[TITLE_START], true);	//入力待ち
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