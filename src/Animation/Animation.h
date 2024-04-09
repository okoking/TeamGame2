#pragma once

//アニメ最大数
#define ANIME_MAX_NUM	(10)	

//==============================================================================================

//アニメの種類
enum ANIME_TYPE
{
	ANIME_FIRST,	//

	ANIME_TYPE_NUM,				//アニメの数
};

//==============================================================================================

//アニメ情報
class AnimeClass
{
private:
	//アニメの種類
	ANIME_TYPE type;

	//画像ハンドル
	int ImgHundle[ANIME_MAX_NUM];

	//座標
	int* x;
	int* y;

	//使用フラグ
	bool isUse;

	//アニメ数
	int animeUsedNum;
	//現在のアニメ番号
	int currentAnimeIndex;

	//１枚あたりの表示時間
	float changeTime;
	//現在のアニメ時間
	float currentAnimeTime;

	//ループアニメーション
	bool loop;

public:
	//読み込み
	void Load();

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画処理
	//引数：座標、アニメタイプ
	void Draw(float x, float y, int type, float size , float angle = 0.0f);

	//後処理
	void Fin();

	//再生
	//引数：アニメの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
	void SetType(ANIME_TYPE type, int* animaHundle);

	//アニメーションが使用中か確認する
	bool CheckType(ANIME_TYPE type);
};

//アニメ情報
extern AnimeClass animeInfo[ANIME_TYPE_NUM];

/*
AnimeClass selAnime;	//光るアニメ
int selAnimeHandle;		//光るハンドル
int selX, selY;




*/