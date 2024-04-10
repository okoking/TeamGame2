#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

const char HEART_PATH[] = {"data/play/lure.png"};		//ハートの画像パス
const char SHIELD_PATH[] = { "data/play/fishingpowerbar.png" };		//シールドの画像パス

// プレイヤーの画像サイズ
const int HEART_SIZE = 32; // ハート

const int SHIELD_WIDTH = 32;  // シールド
const int SHIELD_HEIGHT = 16;

// プレイヤーの初期体力
const int PLAYER_HP = 5;

// プレイヤーの無敵時間
const int PLAYER_INVINCIBLE_TIME = 120;

// プレイヤーの初期位置
const float HEART_INIT_POS_X = 400.0f;
const float HEART_INIT_POS_Y = 300.0f;

class Player
{
private:
	float HeartposX, HeartposY;		// ハートの座標
	int HeartImageHundle;		// ハート画像ハンドル
	
	float ShieldposX, ShieldposY;	// シールドの画像サイズ
	int ShieldImageHundle;		// シールドの画像ハンドル
	float Shieldangle;			// シールドの角度

	int Hp;	// プレイヤーのHP
	int invincibletimeCnt; // プレイヤーの無敵時間カウント用
	bool isActive; // プレイヤーが生きているか
	bool isDraw; // 描画されるか 

	// HPバーの色保存用
	unsigned int Cr;

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
};
