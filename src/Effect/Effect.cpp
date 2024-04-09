
#include <DxLib.h>
#include "Effect.h"

#include"../FrameRate/FrameRate.h"

//エフェクト情報
EffectInfo Effect::effectInfo[EFFECT_MAX_NUM];

//==============================================================================================

//エフェクトのファイルパス
const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	"data/effect/ripple_96×96.png",	//波紋
};

//各エフェクトのアニメ数
const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	8,	//波紋
};

//各エフェクトの画像分割数 [0] = x, [1] = y
const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
{
	{ 8, 1,},	//波紋
};

//エフェクトの画像サイズ
const int effectImageSize[EFFECT_TYPE_NUM][2] =
{
	{ 96, 96,},	//波紋
};

//各エフェクトのアニメ画像切り替え時間
const float effectChageTime[EFFECT_TYPE_NUM] =
{
	0.15f,	//波紋
};

//==============================================================================================

//エフェクトの読み込み
//引数	：エフェクトの種類、作成数
void Effect::Load(EFFECT_TYPE type, int create_num)
{
	for (int createNumIndex = 0; createNumIndex < create_num; createNumIndex++)
	{
		for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
		{
			//★読み込みしていないエフェクト情報を見つける
			//★（ひとつ目の画像ハンドルがゼロなら読み込みされてない）
			if (effectInfo[effectIndex].ImgHundle[0] == -1)
			{
				//★画像を分割読み込み
				LoadDivGraph(	effectFilePath[type],	//パス
								effectAnimeImgNum[type],							//画像総数
								effectImageSplitNum[type][0],						//横の数
								effectImageSplitNum[type][1],						//縦の数
								effectImageSize[type][0],								//分割サイズ　横
								effectImageSize[type][1],								//分割サイズ　縦
								effectInfo[effectIndex].ImgHundle);					//ハンドル変数

				//成功した
				if (effectInfo[effectIndex].ImgHundle[0] != -1)
				{
					//★アニメ数を格納
					effectInfo[effectIndex].animeUsedNum = effectAnimeImgNum[type];

					//★１枚当たりの表示時間を設定
					effectInfo[effectIndex].changeTime = effectChageTime[type];

					//★エフェクトの種類を設定
					effectInfo[effectIndex].type = type;
				}
				//★成否にかかわらず抜ける
				break;
			}
		}
	}
}

//==============================================================================================

//エフェクトの初期化
void Effect::Init()
{
	//★すべてのエフェクト情報の変数をクリアする（ゼロにする）
	for (int i = 0; i < EFFECT_MAX_NUM; i++)
	{		
		effectInfo[i].x = 0;
		effectInfo[i].y = 0;
		effectInfo[i].animeUsedNum = 0;
		effectInfo[i].currentAnimeIndex = 0;

		effectInfo[i].changeTime = 0.0f;
		effectInfo[i].currentAnimeTime = 0.0f;

		effectInfo[i].isUse = false;

		effectInfo[i].type = -1;

		for (int n=0; n < EFFECT_ANIME_MAX_NUM; n++)
		{
			effectInfo[i].ImgHundle[n] = -1;
		}
	}
}

//==============================================================================================

//エフェクト通常処理
void Effect::Step()
{
	for (int effectindex = 0; effectindex < EFFECT_MAX_NUM; effectindex++)
	{
		//★使用中ならアニメ時間を経過させて、アニメ番号を更新する
		if (effectInfo[effectindex].isUse)
		{
			//★時間更新
			effectInfo[effectindex].currentAnimeTime += 1.0f/60;	//60はFPS

			//★画像切り替わるに必要な時間経過したら
			if (effectInfo[effectindex].currentAnimeTime >= effectInfo[effectindex].changeTime)
			{
				//★次の画像へ
				effectInfo[effectindex].currentAnimeIndex++;

				//★計測時間リセット
				effectInfo[effectindex].currentAnimeTime = 0.0f;

				//★次の画像がもし無いなら
				if (effectInfo[effectindex].currentAnimeIndex >= effectInfo[effectindex].animeUsedNum)
				{
					//★使用中フラグをOFFに
					effectInfo[effectindex].isUse = false;
				}
			}
		}
	}
}

//==============================================================================================

//エフェクト描画処理：０システム １ゲーム
void Effect::Draw(int type)
{
	for(int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		switch (type)
		{
			//システム
		case 0: {

			if (effectInfo[effect_index].type != EFFECT_TYPE_RIPPLE)
			{
				continue;
			}

			//★使用中なら現在のアニメ番号で描画する
			if (effectInfo[effect_index].isUse)
			{
				float x = effectInfo[effect_index].x;
				float y = effectInfo[effect_index].y;
				int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
				int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

				DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);
			}

			break; }

			//ゲーム：通常
		case 1: {

			if (effectInfo[effect_index].type < EFFECT_TYPE_SLASH)
			{
				continue;
			}

			//通常
			if (effectInfo[effect_index].type < EFFECT_TYPE_BLESSING)
			{
				if (effectInfo[effect_index].type != EFFECT_TYPE_GUN_HOLES)
				{
					//★使用中なら現在のアニメ番号で描画する
					if (effectInfo[effect_index].isUse)
					{
						float x = effectInfo[effect_index].x;
						float y = effectInfo[effect_index].y;
						int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
						int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

						DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);
					}
				}
				else
				{
					//★使用中なら現在のアニメ番号で描画する
					if (effectInfo[effect_index].isUse)
					{
						float x = effectInfo[effect_index].x;
						float y = effectInfo[effect_index].y;
						int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
						int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

						DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);
					}
				}
			}

			//加算
			else
			{
				//★使用中なら現在のアニメ番号で描画する
				if (effectInfo[effect_index].isUse)
				{
					float x = effectInfo[effect_index].x;
					float y = effectInfo[effect_index].y;
					int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
					int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

					//モードを乗算にする
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

					DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);

					//モードを通常に戻す
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}

			break; }

		default: {
			break; }
		}
	}
}

//==============================================================================================

//エフェクトの後処理
void Effect::Fin()
{
	for (int effectindex = 0; effectindex < EFFECT_MAX_NUM; effectindex++)
	{
		//★すべてのエフェクトを削除する
		for (int imageindex = 0; imageindex < effectInfo[effectindex].animeUsedNum; imageindex++)
		{
			//★すべて削除する

				//★ゼロ以外なら削除する
			if (effectInfo[effectindex].ImgHundle[imageindex] != -1)
			{
				//★画像削除引数を設定する
				DeleteGraph(effectInfo[effectindex].ImgHundle[imageindex]);

				//★削除したらゼロを入れておく
				effectInfo[effectindex].ImgHundle[imageindex] = -1;
			}
		}
	}
}

//==============================================================================================

//エフェクトの再生
//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
void Effect::Play(EFFECT_TYPE type, float x, float y)
{
	for (int effectindex = 0; effectindex < EFFECT_MAX_NUM; effectindex++)
	{
		//★未使用エフェクトを探して再生
		if (!effectInfo[effectindex].isUse)
		{
			//★使用中なら以下行わない
			//★タイプが一致した
			if (effectInfo[effectindex].type == type)
			{
				//★座標設定
				effectInfo[effectindex].x = x;
				effectInfo[effectindex].y = y;
				//★計測用の変数をクリア
				effectInfo[effectindex].currentAnimeIndex = 0;		//現在のアニメ番号
				effectInfo[effectindex].currentAnimeTime = 0.0f;	//現在のアニメ時間
				//★使用中にする
				effectInfo[effectindex].isUse = true;

				//★抜ける
				break;
			}
		}
	}
}
