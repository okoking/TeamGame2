#include "Player.h"
#include "../Input/Input.h"
#include "../Scene/Scene.h"
int Score;

//プレイヤーの初期化
void Player::Init()
{
	//プレイヤーの座標の初期化
	HeartposX = HEART_INIT_POS_X;		//X座標
	HeartposY = HEART_INIT_POS_Y;		//Y座標

	ShieldposX = HEART_INIT_POS_X;		//X座標
	ShieldposY = HEART_INIT_POS_Y - HEART_SIZE;		//Y座標

	// シールドの角度初期化
	Shieldangle = 270.0f;
	CurrentShieldangle = SHIELD_ANGLE_UP;

	//プレイヤーの画像ハンドルの初期化
	HeartImageHundle = -1;
	ShieldImageHundle = -1;

	// HP
	Hp = PLAYER_HP;

	// ガード成功数
	GuardCnt = 0;

	isActive = true;							// プレイヤーが生きているか
	invincibletimeCnt = PLAYER_INVINCIBLE_TIME; // 無敵時間カウント用
	isDraw = true;								// 描画されているか
	Cr= GetColor(0, 255, 0);					// 緑色をセット
}

//プレイヤーの読み込み処理
void Player::Load()
{
	HeartImageHundle = LoadGraph(HEART_PATH);
	ShieldImageHundle = LoadGraph(SHIELD_PATH);
}

//プレイヤーの通常処理
void Player::Step()
{
	//プレイヤーの操作処理
	Operation();

	// 無敵時間処理
	Invincible();

	if (Input::Key::Push(KEY_INPUT_RETURN)) {
		//プレイシーンの終了処理に遷移
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
	if (Input::Key::Push(KEY_INPUT_Q)) {
		// プレイヤーダメージ処理
		Damaged();
	}

}

//プレイヤーの描画処理
void Player::Draw()
{
	if (isDraw) { // 描画されている判定なら
		DrawRotaGraph((int)HeartposX, (int)HeartposY, 1.0f, 0.0f, HeartImageHundle, true); // ハート
	}

	DrawRotaGraph((int)ShieldposX, (int)ShieldposY, 1.0f, Shieldangle / 180 * 3.14, ShieldImageHundle, true); // 盾

	DrawBox(0 , 0 , Hp * 64, 32 , Cr, TRUE);    // 四角形を描画
}

//プレイヤーの終了処理
void Player::Fin()
{
	// ハート画像削除
	DeleteGraph(HeartImageHundle);

	// シールド画像削除
	DeleteGraph(ShieldImageHundle);

	Score = GuardCnt;

}

//プレイヤーの操作処理
void Player::Operation()
{
	// 盾を入力した方向に向ける
	if (Input::Key::Push(KEY_INPUT_LEFT)) {
		ShieldposX = HeartposX - HEART_SIZE;
		ShieldposY = HeartposY;
		CurrentShieldangle = SHIELD_ANGLE_LEFT;
		Shieldangle = 180.0f;
	}
	if (Input::Key::Push(KEY_INPUT_RIGHT)) {
		ShieldposX = HeartposX + HEART_SIZE;
		ShieldposY = HeartposY;
		CurrentShieldangle = SHIELD_ANGLE_RIGHT;
		Shieldangle = 0.0f;
	}
	if (Input::Key::Push(KEY_INPUT_UP)) {
		ShieldposX = HeartposX;
		ShieldposY = HeartposY - HEART_SIZE;
		CurrentShieldangle = SHIELD_ANGLE_UP;
		Shieldangle = 270.0f;
	}
	if (Input::Key::Push(KEY_INPUT_DOWN)) {
		ShieldposX = HeartposX;
		ShieldposY = HeartposY + HEART_SIZE;
		CurrentShieldangle = SHIELD_ANGLE_DOWN;
		Shieldangle = 90.0f;
	}
}

// プレイヤーダメージ処理
void Player::Damaged()
{
	// 無敵中でないなら
	if (invincibletimeCnt == PLAYER_INVINCIBLE_TIME) {
		//se
		Sound::Se::Play(SE_DAMAGE);

		// 無敵時間をリセット
		invincibletimeCnt = 0;
		// HPを減らす
		Hp--;

		if (Hp <= 1) { // HPが1以下なら
			Cr = GetColor(255, 0, 0); // 赤色をセット
		}
		else if (Hp <= 3) { // HPが3以下なら
			Cr = GetColor(255, 255, 0); // 黄色をセット
		}

		// HPが0を下回ったなら
		if (Hp < 0) {
			Hp = 0;
		}

		// 体力が0になったとき
		if (Hp == 0) {
			// 殺して
			isActive = false;

			//プレイシーンの終了処理に遷移
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}
}

// 無敵時間処理
void Player::Invincible()
{
	isDraw = false; // 一度描画されない

	//無敵中ならカウントを進める
	invincibletimeCnt++;

	// 上限を超えているなら上限を代入
	if (invincibletimeCnt > PLAYER_INVINCIBLE_TIME) {
		invincibletimeCnt = PLAYER_INVINCIBLE_TIME;
	}

	if (invincibletimeCnt % 9 < 4) {
		isDraw = true; // 描画されているにする
	}
}
