#include "Player.h"
#include "../Input/Input.h"

//プレイヤーの初期化
void Player::Init()
{
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
	if (Input::Key::Push(KEY_INPUT_LEFT)) {

	}
	if (Input::Key::Push(KEY_INPUT_RIGHT)) {

	}
	if (Input::Key::Push(KEY_INPUT_UP)) {

	}
	if (Input::Key::Push(KEY_INPUT_DOWN)) {

	}


}
