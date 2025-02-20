#pragma once

//画像の種類
enum RESULT_IMAGE
{
	RESULT_BACK_GROUND,	//背景
	RESULT_GAER1,		//歯車
	RESULT_GAER2,		//歯車

	RESULT_IMAGE_MAX_NUM,	//最大数
};

//画像のパス
const char RESULT_IMAGE_PATH[RESULT_IMAGE_MAX_NUM][255] =
{
	"data/result/result.png",	//背景
	"data/result/gear2.png",	//背景
	"data/result/gear3.png",	//背景
};

class Rasult
{
private:
	int imageHandle[RESULT_IMAGE_MAX_NUM];	//画像ハンドル
	int fade[2];	//透明度

	int y;	//スコアの座標

	bool lighting;	//入力待ちの点滅

	int progress;	//進行度
	float RgearAngle;

public:
	//初期化
	void Init();

	//通常処理
	void Step();

	//描画処理
	void Draw();

	//終了処理
	void Fin();
};