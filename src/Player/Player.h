#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

const char PLAYER_PATH[] = {"data/play/player.png"};		//プレイヤーの画像パス

const int PLAYER_SIZE = 32;									//プレイヤー画像のサイズ

// プレイヤーの初期位置
const float PLAYER_POS_X = 400.0f;
const float PLAYER_POS_Y = 300.0f;

class Player
{
private:
	float posX, posY;		//プレイヤーの座標
	int ImageHundle;		//プレイヤー画像ハンドル
	
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

	//プレイヤー操作処理
	void Operation();
};
