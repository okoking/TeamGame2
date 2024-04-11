#pragma once

#define ARROW_MAX_NUM	(3)						//矢の最大数（ハンドルの数）

// 矢の速度
const float ARROW_SPEED = 2.0f;

// 矢の種類
enum ARROW_TYPE {
	ARROW_TYPE_NORMAL = 0,
	ARROW_TYPE_RED,
	ARROW_TYPE_YELLOW,

	ARROW_TYPE_NUM,
};

// 矢の動く向き
enum ARROW_ANGLE {
	ARROW_ANGLE_RIGHT = 0,
	ARROW_ANGLE_DOWN,
	ARROW_ANGLE_LEFT,
	ARROW_ANGLE_UP,
};

struct ArrowInfo
{
	int handle[ARROW_TYPE_NUM];		//画像ハンドル
	ARROW_ANGLE angle;			// 矢の向き保存用
	ARROW_TYPE arrowtype;	// 矢の種類保存用

	float x, y;		//座標
	bool isUse;		//使用中フラグ
};

class Arrow
{
private:
	ArrowInfo arrowInfo[ARROW_MAX_NUM] = { 0 };

public:
	Arrow();
	~Arrow();

	// 矢初期化
	void Init();

	// データロード
	void Load();

	// 矢発射処理
	void IsShot();

	// 矢の移動処理
	void Move();

	// 矢の通常処理
	void Step();

	// 矢の描画
	void Draw();

	// 矢終了処理
	void Fin();

	// 指定された矢情報構造体の使用中フラグを取得
	bool IsUse(int _index) { return arrowInfo[_index].isUse; }

	// 指定された矢情報構造体の使用中フラグを設定
	void SetUse(int _index, bool _isUse) { arrowInfo[_index].isUse = _isUse; }

	// 指定された矢情報構造体のX座標を取得
	float GetPosX(int _index) { return arrowInfo[_index].x; }

	// 指定された矢情報構造体のY座標を取得
	float GetPosY(int _index) { return arrowInfo[_index].y; }
};