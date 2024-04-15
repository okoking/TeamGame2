#pragma once

//画像の種類
enum TITLE_IMAGE_NUM
{
	
	TITLE_TITLE,	//タイトル
	TITLE_START,	//入力待ち
	TITLE_GEAR1,	//歯車
	TITLE_GEAR2,
	TITLE_GEAR3,
	TITLE_GEARHARF,
	TITLE_LINE,		//線
	TITLE_EASY,		//easy
	TITLE_NORMAL,	//normal
	TITLE_HARD,		//hard

	TITLE_IMAGE_MAX_NUM,	//画像数
};

//画像パス
const char TITLE_IMAGE_PATH[TITLE_IMAGE_MAX_NUM][255] =
{
	"data/title/title2.png",	//タイトル
	"data/title/push.png",	//入力待ち
	"data/title/gear1.png",	//歯車1
	"data/title/gear2.png",	//歯車2
	"data/title/gear3.png",	//歯車3
	"data/title/gear2herf .png",	//歯車3
	"data/title/sen.png",	//線
	
	"data/title/easy.png",	//easy
	"data/title/normal.png",//normal
	"data/title/hard.png",	//hard 

	//"data/title/start.png",	//入力待ち
};

class Title
{
private:
	int imageHandle[TITLE_IMAGE_MAX_NUM];	//画像ハンドル

	//float seaY;	//海Ｙ
	//float jettyY;	//桟橋Ｙ
	//float cloudX[4][2];	//雲Ｘ
	//float cloudY;	//雲Ｘ
	//float titleY;	//タイトルＹ

	int fade[2];	//透明度：タイトル 入力待ち

	bool lighting;	//入力待ちの点滅

	int progress;	//進行度

	float gearAngle;	//歯車の回転
	float lineX;		//タイトル下の線
	float lineY;		//タイトル下の線
	float lineW;		//タイトル下の線
	float lineH;		//タイトル下の線

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