#pragma once
#include "../../Scene/Scene.h"
#include "DxLib.h"
#include "../../Player/Player.h"
#include "../../Fish/Fish.h"
#include "../../Mouse/Mouse.h"
#include "../../TimeLimit/TimeLimit.h"
#include "../../Collision/Collision.h"
#include "../../Player/Lure/Lure.h"
#include "../../MathPlus/MathPlus.h"




class Play
{
private:
	//クラスの変数宣言
	Player player;			//プレイヤークラス
	
	Collision collision;	//当たり判定
	Lure lure;				//ルアー

	int backgroundHandle;	//背景画像ハンドル
	int jettyHandle;		//桟橋画像ハンドル
	int scoreImageHandle;	//スコアボード画像ハンドル

	//魚とルアーが当たったかどうかの確認フラグ
	bool IsFishToLureHit;

	float caughtCountTime;
	int fishingChanceNum;
	

	//確認用変数
	float num = 0;
	char moji[256] = "x";

public:
	//プレイシーンの初期化
	void Init();

	//プレイシーンの初期値設定
	void SetDefaultValue();

	//プレイシーンの読み込み
	void Load();

	//プレイシーンの通常処理
	void Step();

	//プレイシーンの描画処理
	void Draw();

	//プレイシーンの終了処理
	void Fin();

	//魚とルアーの当たり判定
	bool FishToLureCollision();

	//魚とルアーが当たった時
	void FishToLureHit();

};
