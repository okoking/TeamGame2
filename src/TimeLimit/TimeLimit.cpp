#include"DxLib.h"
#include"TimeLimit.h"
#include"../FrameRate/FrameRate.h"
#include"../Scene/Scene.h"

//初期化
void TimeLimit::Init()
{
	//画像読み込み
	LoadDivGraph(TIME_IMAGE_PATH,10,5,2,44,64,imageHandle);

	//制限時間設定
	currentTime = TIME_LIMIT;
	timeCount = 0.0;
}

//通常処理
void TimeLimit::Step()
{
	//時間をカウント
	timeCount += 1.0f / FRAME_RATE;

	//カウントが１秒になったら
	if (timeCount >= 1)
	{
		//現在の時間を減少
		currentTime--;
		//カウントを戻す
		timeCount = 0.0f;

		if (currentTime <= 10)
		{
			Sound::Se::Play(SE_TIME_LIMIT);
		}
	}

	//制限時間が0になったら
	if (currentTime <= 0)
	{
		Sound::Se::Play(SE_FINISH);
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
}

//描画
void TimeLimit::Draw()
{
	//十の位
	int imageNum = currentTime / 10;	//画像用数字
	DrawGraph(30, SCREEN_SIZE_Y - 80, imageHandle[imageNum], true);
	
	//一の位
	imageNum = currentTime % 10;	//画像用数字
	DrawGraph(30+45, SCREEN_SIZE_Y - 80, imageHandle[imageNum], true);
}

//終了処理
void TimeLimit::Fin()
{

}