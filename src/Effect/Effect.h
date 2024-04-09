
#ifndef __EFFECT_H__
#define __EFFECT_H__

//一度に表示できるエフェクト最大数
const int EFFECT_MAX_NUM = 200;

//エフェクトのアニメ最大数
const int EFFECT_ANIME_MAX_NUM = 10;

//==============================================================================================

//エフェクトの種類
enum EFFECT_TYPE
{
	EFFECT_TYPE_RIPPLE = 0,		//波紋

	//=============ｹﾞｰﾑ=============

	EFFECT_TYPE_SLASH,			//斬撃
	EFFECT_TYPE_GUN_HOLES,		//銃痕
	EFFECT_TYPE_LIGHTNING,		//電撃
	EFFECT_TYPE_FEATHER_BREAK,	//羽根破壊

	EFFECT_TYPE_ENEDAMAGE,		//敵のダメージ

	//=============加算=============

	EFFECT_TYPE_BLESSING,		//回復：加算

	EFFECT_TYPE_NUM,
};

//==============================================================================================

//エフェクト情報
struct EffectInfo
{
	//★エフェクトの種類
	int type;

	//★画像ハンドル
	int ImgHundle[EFFECT_ANIME_MAX_NUM];

	//★座標
	float x, y;
	//★使用フラグ
	bool isUse;

	//★アニメ数
	int animeUsedNum;
	//★現在のアニメ番号
	int currentAnimeIndex;

	//★１枚あたりの表示時間
	float changeTime;
	//★現在のアニメ時間
	float currentAnimeTime;
};

//エフェクト情報
class Effect
{
private:

	//エフェクト情報
	static EffectInfo effectInfo[EFFECT_MAX_NUM];

public:

	//エフェクトの読み込み
//引数	：エフェクトの種類、作成数
	static void Load(EFFECT_TYPE type, int create_num);

	//エフェクトの初期化
	static void Init();

	//エフェクト通常処理
	static void Step();

	//エフェクト描画処理：０システム １ゲーム
	static void Draw(int type=0);

	//エフェクトの後処理
	static void Fin();

	//エフェクトの再生
	//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
	static void Play(EFFECT_TYPE type, float x, float y);

};

#endif
