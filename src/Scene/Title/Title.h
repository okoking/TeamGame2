#pragma once

//画像の種類
enum TITLE_IMAGE_NUM
{
	TITLE_SKY,	//空
	TITLE_SEA,	//海
	TITLE_JETTY,	//桟橋
	TITLE_CLOUD1,	//雲1
	TITLE_CLOUD2,	//雲2
	TITLE_CLOUD3,	//雲3
	TITLE_CLOUD4,	//雲4
	TITLE_TITLE,	//タイトル
	TITLE_START,	//入力待ち

	TITLE_IMAGE_MAX_NUM,	//画像数
};

//画像パス
const char TITLE_IMAGE_PATH[TITLE_IMAGE_MAX_NUM][255] =
{
	"data/title/sky.png",	//空
	"data/title/sea.png",	//海
	"data/title/jetty.png",	//桟橋
	"data/title/cloud1.png",	//雲1
	"data/title/cloud2.png",	//雲2
	"data/title/cloud3.png",	//雲3
	"data/title/cloud4.png",	//雲4
	"data/title/title.png",	//タイトル
	"data/title/start.png",	//入力待ち
};

class Title
{
private:
	int imageHandle[TITLE_IMAGE_MAX_NUM];	//画像ハンドル

	float seaY;	//海Ｙ
	float jettyY;	//桟橋Ｙ
	float cloudX[4][2];	//雲Ｘ
	float cloudY;	//雲Ｘ
	float titleY;	//タイトルＹ

	int fade[2];	//透明度：タイトル 入力待ち

	bool lighting;	//入力待ちの点滅

	int progress;	//進行度

public:

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//終了処理
	void Fin();

};