#include"DxLib.h"
#include"../Result/Result.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../Fish/Fish.h"


//初期化
void Rasult::Init()
{
	for (int i = 0; i < RESULT_IMAGE_MAX_NUM; i++)
	{
		//画像読み込み
		imageHandle[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}

	y = 0;
	fade[0] = 0;
	fade[1] = 0;
	lighting = false;
	progress = 0;

	//bgm
	Sound::Bgm::Play(BGM_RESULT);

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//通常処理
void Rasult::Step()
{
	switch (progress)
	{
	case 0:	//スコア表示

		//スコアの透明度
		if (fade[0] >= 255)
		{
			fade[0] = 255;
		}
		else
		{
			fade[0] += 2;
		}

		//スコアの座標
		if (y >= 120)
		{
			y = 120;
		}
		else
		{
			y += 1;
		}

		//以上が指定通りなら進行
		if (fade[0] == 255 && y == 120)
		{
			progress++;
		}

		break;

	case 1:	//入力待ち

		//点滅
		//点く
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
			g_CurrentSceneID = SCENE_ID_FIN_RESULT;
		}

		break;

		
	default:
		break;
	}
	
}

//描画
void Rasult::Draw()
{
	//背景描画
	DrawGraph(0, 0, imageHandle[RESULT_BACK_GROUND], true);

	//fadeで透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
	//文字の大きさを変更
	SetFontSize(60);
	DrawFormatString(300, y, GetColor(255, 255, 255), "スコア");
	//文字の大きさを変更
	SetFontSize(80);
	DrawFormatString(400, y + 60, GetColor(255, 255, 255), "%d匹", fish.GetCaughtNum());
	//文字の大きさを元に戻す
	SetFontSize(20);
	//表示を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//fadeで透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
	DrawGraphF(0, 0, imageHandle[RESULT_FINISH], true);	//タイトル
	//表示を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//終了処理
void Rasult::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_RESULT);

	//プレイ画面へ移行
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}