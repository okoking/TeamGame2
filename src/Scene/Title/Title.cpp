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

	////透明度設定
	//fade[0] = 0;
	//fade[1] = 0;
	//lighting = true;

	//進行度
	progress = 1;

	////bgm
	//Sound::Bgm::Play(BGM_TITLE);

	//歯車回転
	gearAngle = 0.0f;

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//通常処理
void Title::Step()
{
	switch (progress)
	{
	case 0:	//画面作り

		

		//タイトル
		/*if (titleY >= 0)
		{
			titleY = 0;
		}
		else
		{
			titleY += 0.5f;
		}*/

		////以上が完成していると進行
		//if (seaY == 0 && jettyY == 0 && titleY == 0 && fade[0])
		//{
		//progress++;
		//}

		break;

	case 1:	//入力待ち

		////UIの点滅
		////現れる
		//if (lighting)
		//{
		//	fade[1] += 5;

		//	if (fade[1] >= 255)
		//	{
		//		lighting = false;
		//	}
		//}
		////消える
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

		//スペースキーで画面変化
		if (Input::Key::Push(KEY_INPUT_SPACE))
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

	////画面未完成時に左クリックで完成
	//if (progress != 1 && Input::Mouse::Push(MOUSE_INPUT_LEFT))
	//{
	//	//座標の設定
	//	seaY = 0;
	//	jettyY = 0;
	//	fade[0] = 255;
	//	titleY = 0;

	//	//入力待ちへ
	//	progress = 1;
	//}

	////雲の流れ
	//for (int i = 0; i < 2; i++)
	//{
	//	cloudX[0][i] -= 0.3;
	//	cloudX[1][i] -= 0.5;
	//	cloudX[2][i] -= 0.4;
	//	cloudX[3][i] -= 0.1;
	//}
	
	////画面外に行くと元の位置に戻す
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

//描画
<<<<<<< HEAD
void Title::Draw()
{
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	//タイトル下地
	DrawRotaGraph(-122, -106,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);
	DrawRotaGraph(-42, 410,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(578, 673, 1.0f, (int)gearAngle, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(-42, 410,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);
	DrawRotaGraph(34, 512,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);
	DrawRotaGraph(92, 429,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);
=======
void Title::Draw()//800 600
{	
	//タイトル下地
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	

	//左上
	DrawRotaGraph(15, 0,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);

	//左下
	DrawRotaGraph(-42, 410,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR2], true);	
	DrawRotaGraph(34, 512,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(92, 429,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	
>>>>>>> 32f5009e637dd2695ea81e6d16b05cfab33da0fd

	//右下
	DrawRotaGraph(760, 460,1.0f, (int)gearAngle*-1, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(663, 576,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	

	//タイトル下の線 座標、左上座標、描画するサイズ、ハンドル、透明化、画像反転有無  421 43
	//DrawRectGraph(210, 344, lineX, lineY, lineW,lineH,imageHandle[TITLE_LINE], false,false);
	DrawRectGraph(210, 344, 421, 43, 421,43,imageHandle[TITLE_LINE], true,false);

//	//fadeで透明度変更
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
//	DrawGraphF(0, titleY, imageHandle[TITLE_TITLE], true);	//タイトル
//	//表示を元に戻す
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//
//	//fadeで透明度変更
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
//	DrawGraphF(0, 0, imageHandle[TITLE_START], true);	//入力待ち
//	//表示を元に戻す
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//終了処理
void Title::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_TITLE);
	
	//プレイ画面へ移行
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}