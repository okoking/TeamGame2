#pragma once

class Mouse
{
private:
	int x, y;		//座標
	int handle;		//ハンドル
	bool isUse;		//使用フラグ
	float angle;	//角度
	float size;		//拡大率

public:
	//初期化
	void Init(int pathNum=0);
	//画像読み込み
	void Load(int pathNum);
	//通常処理
	void Step();
	//マウスの移動処理
	void Move();
	//描画
	void Draw(int type=0);
	//終了処理
	void FIn();

	//座標を取得
	int GetX() { return x; }
	int GetY() { return y; }

	//使っているかの確認
	bool CheckUse() { return isUse; }

	//角度をセット
	void SetAngle(float set) { angle = set; }
	//拡大率をセット
	void SetSize(float set) { size = set; }
	
	//当たり判定
	bool MouseColli(int Ra, int Rx, int Ry);
	bool MouseColli(int Ax, int Ay, int Aw, int Ah);

	void SetUse(char set = '0');	//使用中セット：！でfalse
};
