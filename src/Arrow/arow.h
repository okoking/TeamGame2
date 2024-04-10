#pragma once

#define BULLET_MAX_NUM	(3)						//弾の最大数（ハンドルの数）
struct ArrowInfo
{
	int handle;		//画像ハンドル
	int x, y;		//座標
	bool isUse;		//使用中フラグ
};

class Arrow
{
public:
	ArrowInfo arrowInfo[BULLET_MAX_NUM] = { 0 };
	Arrow();
	~Arrow();

	// 弾初期化
	void Init();

	// 弾発射処理
	bool IsShot(int shotPosX, int shotPosY);

	// 弾の移動処理
	void Move();

	// 弾の描画
	void Draw();

	// 指定された弾情報構造体の使用中フラグを取得
	bool IsUse(int _index) { return arrowInfo[_index].isUse; }

	// 指定された弾情報構造体の使用中フラグを設定
	void SetUse(int _index, bool _isUse) { arrowInfo[_index].isUse = _isUse; }

	// 指定された弾情報構造体のX座標を取得
	int GetPosX(int _index) { return arrowInfo[_index].x; }

	// 指定された弾情報構造体のY座標を取得
	int GetPosY(int _index) { return arrowInfo[_index].y; }
};