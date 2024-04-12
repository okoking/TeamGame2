#pragma once

#include "../../Scene/Scene.h"
#include "DxLib.h"
#include "../../Player/Player.h"
#include "../../Collision/Collision.h"
#include "../../MathPlus/MathPlus.h"
#include "../../Arrow/arow.h"

class Play
{
private:
	//クラスの変数宣言
	Player player;

	Arrow arrow;	// 矢

	int backgroundHandle;	//背景画像ハンドル

public:
	//プレイシーンの初期化
	void Init();

	//プレイシーンの読み込み
	void Load();

	//プレイシーンの通常処理
	void Step();

	//プレイシーンの描画処理
	void Draw();

	//プレイシーンの終了処理
	void Fin();

	// 矢の当たり判定
	void ArrowCollision(SHIELD_ANGLE ShieldAngle);
};
