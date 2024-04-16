#pragma once
#include "../Player/Player.h"

#define ARROW_MAX_NUM	(6)						//矢の最大数（ハンドルの数）

// 矢の速度
const float ARROW_SPEED = 4.0f;
const int ARROW_MAX_INTERVAL = 120; // 次の矢が出てくるまでの間隔
const int INVERSION_FRAME = 50; // 発射されてから反転するまでのフレーム

// 矢の種類
enum ARROW_TYPE {
	ARROW_TYPE_NORMAL = 0,
	ARROW_TYPE_RED,
	ARROW_TYPE_YELLOW,

	ARROW_TYPE_NUM,
};

// 矢の来る方向
enum ARROW_ANGLE {
	ARROW_ANGLE_RIGHT = 0,
	ARROW_ANGLE_DOWN,
	ARROW_ANGLE_LEFT,
	ARROW_ANGLE_UP,
};

// 矢の画像ファイルパス
const char NORMALARROW_PATH[] = { "data/play/kari_arrow.png" };
const char REDARROW_PATH[] = { "data/play/kari_arrow2.png" };
const char YELLOWARROW_PATH[] = { "data/play/kari_arrow1.png" };

// 画像サイズ
const float ARROW_SIZE_X = 48;
const float ARROW_SIZE_Y = 32;

// 同時に発射されない猶予
const int RECOVERY_MAX_FRAME = 20;

struct ArrowInfo
{
	int handle[ARROW_TYPE_NUM];		//画像ハンドル
	ARROW_ANGLE angle;			// 矢の向き保存用
	ARROW_TYPE arrowtype;	// 矢の種類保存用

	float x, y;		//座標
	float xspeed, yspeed;	// 移動速度
	int ShotInterval;	// 発射間隔
	bool isUse;		//使用中フラグ
	bool isInversion; // 矢反転中フラグ
	bool isInversioned; // 回転終了確認フラグ
	int InversionCnt; // 反転角度カウント用
	int ShotTimeCnt; // 発射されてからのフレームカウント用
	float InversionAngle; // 反転中回転しているしている角度
};

class Arrow
{
private:
	ArrowInfo arrowInfo[ARROW_MAX_NUM] = { 0 };
	int Recoverycnt;	// 同時に発射されないようにする

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

	// 指定された矢の向きを取得
	ARROW_ANGLE GetArrowAngle(int _index) { return arrowInfo[_index].angle; }

	// 矢のランダム要素をリセット
	void ResetArrow(int _index);

	// 矢の種類取得用
	ARROW_TYPE GetArrowType(int _index) { return arrowInfo[_index].arrowtype; }

	// 回転中フラグ取得用
	bool GetisInversion(int _index){return arrowInfo[_index].isInversion;}
};