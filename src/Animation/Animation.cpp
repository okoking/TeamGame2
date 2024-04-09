#include<DxLib.h>
#include"Animation.h"

//アニメ情報
AnimeClass animeInfo[ANIME_TYPE_NUM];

//==============================================================================================

//ファイルパス
const char animeFilePath[ANIME_TYPE_NUM][256] =
{
	"",	//
};

//アニメ数
const int animeImgNum[ANIME_TYPE_NUM] =
{
	0,	//
};

//画像分割数 [0] = x, [1] = y
const int animeImageSplitNum[ANIME_TYPE_NUM][2] =
{
	{0,0},	//
};

//画像サイズ [0] = x, [1] = y
const int animeImageSize[ANIME_TYPE_NUM][2] =
{
	{0,0},	//
};

//アニメ画像切り替え時間
const float animwChageTime[ANIME_TYPE_NUM] =
{
	0.1f,	//
};

//再生タイプ　ループするか
const bool animeLoop[ANIME_TYPE_NUM] =
{
	true,	//
};

//==============================================================================================

//アニメの読み込み
void AnimeClass::Load()
{
	for (int animeIndex = 0; animeIndex < ANIME_TYPE_NUM; animeIndex++)
	{
	
		//★画像を分割読み込み
			LoadDivGraph(animeFilePath[animeIndex],				//パス
						animeImgNum[animeIndex],				//画像総数
						animeImageSplitNum[animeIndex][0],		//横の数
						animeImageSplitNum[animeIndex][1],		//縦の数
						animeImageSize[animeIndex][0],			//分割サイズ　横
						animeImageSize[animeIndex][1],			//分割サイズ　縦
						animeInfo[animeIndex].ImgHundle);		//ハンドル変数

		//アニメ数を格納
		animeInfo[animeIndex].animeUsedNum = animeImgNum[animeIndex];

		//１枚当たりの表示時間を設定
		animeInfo[animeIndex].changeTime = animwChageTime[animeIndex];

		//ループアニメーションか設定
		if (animeLoop[animeIndex])
		{
			animeInfo[animeIndex].loop = true;
		}
		else
		{
			animeInfo[animeIndex].loop = false;
		}
		
	}
}

//==============================================================================================

//アニメの初期化
void AnimeClass::Init()
{
	//すべてのエフェクト情報の変数をクリアする（ゼロにする）
	for (int i = 0; i < ANIME_TYPE_NUM; i++)
	{
		animeInfo[i].x = 0;
		animeInfo[i].y = 0;
		animeInfo[i].animeUsedNum = 0;
		animeInfo[i].currentAnimeIndex = 0;

		animeInfo[i].changeTime = 0.0f;
		animeInfo[i].currentAnimeTime = 0.0f;

		animeInfo[i].isUse = false;

		animeInfo[i].type = ANIME_FIRST;
		animeInfo[i].loop = false;

		for (int n = 0; n < ANIME_MAX_NUM; n++)
		{
			animeInfo[i].ImgHundle[n] = 0;
		}
	}

	//画像のロード
	Load();
}

//==============================================================================================

//アニメ通常処理
void AnimeClass::Step()
{
	for (int animeIndex = 0; animeIndex < ANIME_TYPE_NUM; animeIndex++)
	{
		//使用中ならアニメ時間を経過させて、アニメ番号を更新する
		if (animeInfo[animeIndex].isUse)
		{
			//時間更新
			animeInfo[animeIndex].currentAnimeTime += 1.0f / 60;	//60はFPS

			//画像切り替わるに必要な時間経過したら
			if (animeInfo[animeIndex].currentAnimeTime >= animeInfo[animeIndex].changeTime)
			{	
				//次の画像へ
				animeInfo[animeIndex].currentAnimeIndex++;

				//計測時間リセット
				animeInfo[animeIndex].currentAnimeTime = 0.0f;

				//次の画像がもし無いなら
				if (animeInfo[animeIndex].currentAnimeIndex >= animeInfo[animeIndex].animeUsedNum)
				{
					if (animeInfo[animeIndex].loop)
					{
						//初めに戻る
						animeInfo[animeIndex].currentAnimeIndex = 0;
					}
					else
					{
						//最後の画像に固定
						animeInfo[animeIndex].currentAnimeIndex = animeInfo[animeIndex].animeUsedNum-1;
					}
				}
			}
		}
	}
}

//==============================================================================================

//アニメ描画処理（通常の描画関数として使う）
//引数：座標X,Y　アニメタイプを格納している変数
void AnimeClass::Draw(float x, float y, int type, float size,float angle)
{
	//使用中なら現在のアニメ番号で描画する
	if (animeInfo[type].isUse)
	{
		//変数をまとめる
		int handleIndex = animeInfo[type].currentAnimeIndex;
		int imageHundle = animeInfo[type].ImgHundle[handleIndex];

		DrawRotaGraphF(x, y, size, angle, imageHundle, true);
	}
}

//==============================================================================================

//アニメの後処理
void AnimeClass::Fin()
{
	for (int animeIndex = 0; animeIndex < ANIME_TYPE_NUM; animeIndex++)
	{
		//すべてのエフェクトを削除する
		for (int imageindex = 0; imageindex < animeInfo[animeIndex].animeUsedNum; imageindex++)
		{
			//ゼロ以外なら削除する
			if (animeInfo[animeIndex].ImgHundle[imageindex] != 0)
			{
				//画像削除引数を設定する
				DeleteGraph(animeInfo[animeIndex].ImgHundle[imageindex]);

				//削除したらゼロを入れておく
				animeInfo[animeIndex].ImgHundle[imageindex] = 0;
			}
		}
	}
}

//==============================================================================================

//アニメのセット
//引数：アニメの種類, ＆アニメタイプを格納する変数
void AnimeClass::SetType(ANIME_TYPE type, int* animaHundle)
{
	//変えるアニメが未使用なら以下実行
	if (!CheckType(type))
	{
		//現在使用中のアニメのフラグを折る
		animeInfo[*animaHundle].isUse = false;

		//アニメを変更し格納する
		*animaHundle = type;

		//使用中なら以下行わない
		if (!animeInfo[type].isUse)
		{
			//計測用の変数をクリア
			animeInfo[type].currentAnimeIndex = 0;		//現在のアニメ番号
			animeInfo[type].currentAnimeTime = 0.0f;	//現在のアニメ時間
			//使用中にする
			animeInfo[type].isUse = true;
		}
	}
}

//アニメの再生
//引数：アニメの種類
bool AnimeClass::CheckType(ANIME_TYPE type)
{
	//使用しているか確認
	if (animeInfo[type].isUse)
	{
		return true;
	}
	else
	{
		return false;
	}
}
