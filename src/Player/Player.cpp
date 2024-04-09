#include "Player.h"

//プレイヤーの初期化
void Player::Init()
{
	//プレイヤーの状態初期化
	plStatus = Normal;

	//プレイヤーの座標の初期化
	posX = 0;		//X座標
	posY = 0;		//Y座標

	//プレイヤーの画像ハンドルの初期化
	ImageHundle = -1;
}

//プレイヤーの読み込み処理
void Player::Load()
{
	ImageHundle = LoadGraph(PLAYER_PATH);
}

//プレイヤーの初期値設定
void Player::SetDefaultValue()
{
	//プレイヤーの状態
	plStatus = Normal;

	//プレイヤーの座標の初期化
	posX = PLAYER_POS_X;		//X座標
	posY = PLAYER_POS_Y;		//Y座標
}

//プレイヤーの通常処理
void Player::Step()
{

}

//プレイヤーの描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraph((int)posX, (int)posY, 1.0f, 0.0f, ImageHundle, true, false);
}

//プレイヤーの終了処理
void Player::Fin()
{
	// プレイヤー画像削除
	DeleteGraph(ImageHundle);
}

//プレイヤーの操作処理
void Player::Operation()
{

}
