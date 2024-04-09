#include"DxLib.h"
#include"FrameRate.h"
#include"../Scene/Scene.h"

//フレームレート情報
struct FrameRateInfo
{
	int currentTime;		//現在の時間
	int lastFrameTime;		//前回のフレーム実行時の時間
	int count;				//フレームカウント用
	int calcFpsTime;		//FPSを計算した時間
	float fps;				//計測したFPS（表示用）
};

//フレームレート情報変数
FrameRateInfo frameRateInfo;

//超絶強引FPS関数
bool FPS()
{
	Sleep(1);	//システムに処理を返す

	//現在の時間を取得
	frameRateInfo.currentTime = GetNowCount();

	//最初のループなら
	//現在の時間を、FPSの計算した時間に設定
	if (frameRateInfo.calcFpsTime == 0.0f)
	{
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
		frameRateInfo.fps = (float)FRAME_RATE;
	}

	//現在の時間が、前回のフレーム時より
	//1000/60ミリ秒（1/60秒）以上経過していたら処理を実行する
	if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME)
	{
		//フレーム実行時の時間を更新
		frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

		//フレーム数をカウント
		frameRateInfo.count++;

		return true;
	}
	return false;
}

//FPS計算
void CalcFPS()
{
	//前回のFPSを計算した時間から経過時間を求める
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//前回のFPSを計算した時間から
	//1秒以上経過していたらFPSを計算する
	if (difTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		//FPSを求める
		//理想の数値は 60000 / 1000 で 60 となる
		frameRateInfo.fps = frameCount / difTime;

		//フレームレートカウントをクリア
		frameRateInfo.count = 0;

		//FPSを計算した時間を更新
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

//FPS表示（デバック用）
void DrawFPS()
{
	SetFontSize(20);
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(SCREEN_SIZE_X -120, SCREEN_SIZE_Y -20, color, "FPS[%.2f]", frameRateInfo.fps);
}