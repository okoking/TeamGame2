#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

const char HEART_PATH[] = {"data/play/kari_heart2.png"};		//ハートの画像パス
const char SHIELD_PATH[] = { "data/play/shield.png" };		//シールドの画像パス
const char HP_PATH[] = { "data/play/HP.png" };		//HPの画像パス

// プレイヤーの画像サイズ
const int HEART_SIZE = 32; // ハート

const int SHIELD_WIDTH = 32;  // シールド
const int SHIELD_HEIGHT = 16;

// プレイヤーの初期体力
const int PLAYER_HP = 5;

// プレイヤーの無敵時間
const int PLAYER_INVINCIBLE_TIME = 90;

// プレイヤーの初期位置
const float HEART_INIT_POS_X = 400.0f;
const float HEART_INIT_POS_Y = 300.0f;

// 盾の向いている方向
enum SHIELD_ANGLE {
	SHIELD_ANGLE_RIGHT = 0,
	SHIELD_ANGLE_DOWN,
	SHIELD_ANGLE_LEFT,
	SHIELD_ANGLE_UP,
};

class Player
{
private:
	float HeartposX, HeartposY;		// ハートの座標
	int HeartImageHundle;		// ハート画像ハンドル
	
	float ShieldposX, ShieldposY;	// シールドの画像サイズ
	int ShieldImageHundle;		// シールドの画像ハンドル
	float Shieldangle;			// シールドの角度
	SHIELD_ANGLE CurrentShieldangle; // 現在の盾の向き

	int Hp;	// プレイヤーのHP
	int invincibletimeCnt; // プレイヤーの無敵時間カウント用
	bool isActive; // プレイヤーが生きているか
	bool isDraw; // 描画されるか 

	int HpHundle;	// HPの装飾ハンドル

	// HPバーの色保存用
	unsigned int Cr;

	// ガード成功数
	int GuardCnt;

	//プレイヤー操作処理
	void Operation();

	// 無敵時間処理
	void Invincible();

public:
	//プレイヤーの初期化
	void Init();

	//プレイヤーの読み込み処理
	void Load();

	//プレイヤーの通常処理
	void Step();

	//プレイヤー関連の描画処理
	void Draw();

	//プレイヤーの終了処理
	void Fin();

	// プレイヤーダメージ処理
	void Damaged();

	// 盾の向き取得用
	SHIELD_ANGLE GetShieldAngle() { return CurrentShieldangle; }

	// ガード数加算
	void AddGuardCnt() { GuardCnt++; };

	// ガード数取得用
	int GetGuradCnt() { return GuardCnt; }
};
