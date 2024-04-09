#pragma once
#include "../../Mouse/Mouse.h"

// 浮きの画像パス
const char LURE_PATH[] = { "data/play/lure.png" };
// ゲージの画像パス
const char GAUGE_PATH[] = { "data/play/fishingpowergauge.png" };
// バーの画像パス
const char BAR_PATH[] = { "data/play/fishingpowerbar.png" };

// ルアー画像のサイズ
const int LURE_SIZE = 10;

//ルアー画像の縦、横サイズ
const float LURE_HIGHT = 17.0f;
const float LURE_WIDTH = 17.0f;

//ルアーの初期位置
const float LURE_POS_X = 400.0f;
const float LURE_POS_Y = 460.0f;

// ゲージの描画位置
const int GAUGE_POS_X = 400;
const int GAUGE_POS_Y = 30;

// ゲージの画像サイズ
const int GAUGE_SIZE_X = 300;

// 釣る力の最大値
const int MAX_FISHING_POWER = 300;

enum LURE_IMAGE_TYPE {
	LURE_IMAGE_TYPE_LURE=0,
	LURE_IMAGE_TYPE_GAUGE,
	LURE_IMAGE_TYPE_BAR,

	LURE_IMAGE_TYPE_NUM,
};
class Lure {
private:
	Mouse LureMouse;

	enum LureDirection {
		LURE_LEFT = 0,
		LURE_RIGHT,
	};

	int handle[LURE_IMAGE_TYPE_NUM]; // ルアー画像ハンドル
	float _X, _Y; // 現在の座標
	float _SaveX, _SaveY; // 移動後の座標

	bool isActive; // 使用中かどうか
	bool isLureLeft; // ルアーが画面の左半分にあるか

	bool isUse;	//ルアーを投げたら
	bool isThrow; // ルアーを投げているか
	bool isCaught; // かかっているかどうか

	int fade; //透明度
	int fishingpower; // 竿を引く力

	//波紋============================
	float effectInterval;

	//SE用============================
	bool seFrg;	//音を鳴らしたか

public:

	Lure(); // コンストラクタ

	// 座標変更用(引数:X座標,Y座標,配列番号)
	void Setpos(float X, float Y)
	{
		_SaveX = X;
		_SaveY = Y;
	}

	// X座標取得用
	float GetXPos() { return _X; }
	// Y座標取得用
	float GetYPos() { return _Y; }

	// 移動後のX座標取得用(引数:移動後の座標)
	void GetSaveXPos(float X) { _SaveX = X; }
	// 移動後のY座標取得用(引数:移動後の座標)
	void GetSaveYPos(float Y) { _SaveY = Y; }

	// 座標更新用
	void UpdatePos();

	// 初期化
	void Init();

	// 画像ロード
	void Load();

	// マウス処理
	void Mouse();

	// 移動処理
	void Move();

	// 通常処理
	void Step();

	// 画像描画
	void Draw();

	// 終了処理
	void Fin();
	
	// 釣り処理
	void Fishing();

	// isCaught変更用
	void SetisCaught(bool _isCaught) { isCaught = _isCaught; }

	// isCaught取得用
	bool GetisCaught() { return isCaught; }

	bool GetisUse() { return isUse; }

	void SetFade(int set) { fade = set; }
};