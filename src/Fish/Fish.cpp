#include "Fish.h"
#include "../Scene/Scene.h"
#include "../FrameRate/FrameRate.h"
#include "../Player/Lure/Lure.h"
#include "../MathPlus/MathPlus.h"

#include "DxLib.h"

Fish::Fish()
{
	//魚の最大数までfor分を回す
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// ハンドル
		handle[IMAGE_TYPE_NORMAL][FishIndex] = -1;
		handle[IMAGE_TYPE_CAUGHT][FishIndex] = -1;

		// 現在の座標
		_X[FishIndex] = 0.0f;
		_Y[FishIndex] = 0.0f;
		// 直前の座標
		_SaveX[FishIndex] = 0.0f;
		_SaveY[FishIndex] = 0.0f;
		
		// 魚の移動速度
		fishSpeed[FishIndex] = 0;

		isLeft[FishIndex] = true; // 左を向いているかどうか
		isActive[FishIndex] = false; // 生きているかどうか
		isCaught[FishIndex] = false; // かかっているかどうか
	}

	//魚が出てくるまでの時間
	Poptime = 0;
	countTime = 0;

	CaughtNum = 0; // 何匹釣れているか
}

// 座標更新用
void Fish::UpdatePos()
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) 
	{
		_X[FishIndex] = _SaveX[FishIndex];
		_Y[FishIndex] = _SaveY[FishIndex];
	}
}

// isCaught変更用(引数:配列番号,変更先)
void Fish::SetisCaught(int FishIndex, bool _isCaught)
{
	isCaught[FishIndex] = _isCaught; // かかっているかどうか
}

// 初期化
void Fish::Init()
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// 現在の座標
		_X[FishIndex] = 0.0f;
		_Y[FishIndex] = 0.0f;

		// 直前の座標
		_SaveX[FishIndex] = _X[FishIndex];
		_SaveY[FishIndex] = _Y[FishIndex];

		isLeft[FishIndex] = true; // 左を向いているかどうか
		isActive[FishIndex] = false; // 生きているかどうか
		isCaught[FishIndex] = false; // かかっているかどうか

		//左を向いているかどうか
		if (GetRand(1) == 0)
		{
			isLeft[FishIndex] = true;
		}
		else
		{
			isLeft[FishIndex] = false;
		}
		
	}

	//魚が出てくるまでの時間
	Poptime = 0;
	countTime = 0;

	CaughtNum = 0; // 何匹釣れているか

	fishingChance = false;

	//得点加算の画像読み込み
	scoreImageHandle = LoadGraph(SCORE_IMAGE_PATH);
	//得点加算の座標追加文設定
	scoreAddY = 0;
	//得点加算の透明度設定
	scoreFade = 0;
	//得点加算演出実行フラグ
	addScore = false;
}

// 画像ロード
void Fish::Load()
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// 魚の画像ロード
		handle[IMAGE_TYPE_NORMAL][FishIndex] = LoadGraph(FISH_PATH);
		handle[IMAGE_TYPE_CAUGHT][FishIndex] = LoadGraph(CAUGHT_FISH_PATH);
	}
}

// 通常処理(引数:ルアーの座標)
void Fish::Step(float lureX,float lureY, bool lureIsUse, bool lureIsCaught)
{
	//移動処理
	Move(lureX, lureY, lureIsUse, lureIsCaught);

	//出現処理
	Pop();

	//魚かかったとき
	Caught(lureX, lureY);

	//座標更新処理
	//UpdatePos();

	//得点加算演出
	ScoreAddMove();
}

// 画像描画
void Fish::Draw()
{
	//60%で描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * 0.6));

	//魚の最大数までfor分を回す
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) 
	{
		//魚が使用中なら描画
		if (isActive[FishIndex])
		{
			if (!isCaught[FishIndex]) {
				// かかっていないときは魚のかたち
				DrawRotaGraph((int)_X[FishIndex], (int)_Y[FishIndex],
					1.0f, angle[FishIndex], handle[IMAGE_TYPE_NORMAL][FishIndex], true, isLeft[FishIndex]);
			}
			else {
				// かかったときは影
				DrawRotaGraph((int)_X[FishIndex], (int)_Y[FishIndex],
					1.0f, 0.0f, handle[IMAGE_TYPE_CAUGHT][FishIndex], true, isLeft[FishIndex]);
			}
		}

		//DrawFormatString(30, 30, GetColor(255, 0, 0), "%d", Poptime);
	}

	//表示を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//文字の大きさを変更
	SetFontSize(40);
	// 釣れた数の表示
	DrawFormatString(657, 600 - 80, GetColor(59, 45, 45), "%d", CaughtNum);
	//文字の大きさを元に戻す
	SetFontSize(20);

	//透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, scoreFade);
	DrawRotaGraph(700, 500+ scoreAddY, 1.0f, 0.0f, scoreImageHandle, true);
	//表示を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 終了処理
void Fish::Fin()
{
	//魚の最大数までfor分を回す
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		// 魚の画像削除
		DeleteGraph(handle[IMAGE_TYPE_NORMAL][FishIndex]);
	}
}

//移動処理
void Fish::Move(float lureX,float lureY,bool lureIsUse,bool lureIsCaught)
{	
	fishingChance = false;
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) 
	{
		//生存で以下
		if (isActive[FishIndex])
		{
			//ルアーの一定距離に入ったらルアーを追跡==================================
			if (GetDistance(_X[FishIndex], _Y[FishIndex], lureX, lureY) <= 100&&
				lureIsUse&&	//ルアーを投げている
				!lureIsCaught&&	//hitしていない
				!fishingChance)	//まだ一匹も反応してない
			{
				_X[FishIndex] += GetDirection(lureX, lureY, _X[FishIndex], _Y[FishIndex], 'x', 0.5f);
				_Y[FishIndex] += GetDirection(lureX, lureY, _X[FishIndex], _Y[FishIndex], 'y', 0.5f);

				//向きを変える
				if (isLeft[FishIndex])
				{
					
					angle[FishIndex] = GetAngle(_X[FishIndex], _Y[FishIndex], lureX, lureY);
				}
				else
				{
					angle[FishIndex] = GetAngle(lureX, lureY, _X[FishIndex], _Y[FishIndex]);
				}

				//一匹だけルアーに反応するようにする
				fishingChance = true;
			}

			//通常移動===============================================================
			else
			{
				// 魚の移動処理
				if (isLeft[FishIndex]) {
					_X[FishIndex] -= fishSpeed[FishIndex]; // 左を向いているとき左に動く
					angle[FishIndex] = 0;
				}
				else {
					_X[FishIndex] += fishSpeed[FishIndex]; // 右を向いているときに右に動く
					angle[FishIndex] = 0;
				}

				// 魚が画面外に行ったとき
				//→
				if (isLeft[FishIndex])
				{
					if (_X[FishIndex] < -(FISH_X_SIZE / 2))
					{
						isActive[FishIndex] = false; // 魚を殺す
					}
				}
				//←
				else
				{
					if (_X[FishIndex] > SCREEN_SIZE_X + FISH_X_SIZE / 2)
					{
						isActive[FishIndex] = false; // 魚を殺す
					}
				}
			}
		}
	}

}

//出現時間管理処理
void Fish::SetPopTime()
{
	countTime += 1.0f / FRAME_RATE;	//時間をカウント
}

//魚出現
void Fish::Pop()
{
	//出現時間管理処理
	SetPopTime();

	//カウントが出現時間を越えたら
	if (countTime > Poptime)
	{
		for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++)
		{
			//使用されてなかったら以下実行
			if (!isActive[FishIndex])
			{
				//左を向いているかどうか　ランダムで決定
				//←
				if (GetRand(1) == 0)
				{
					isLeft[FishIndex] = true;
				}
				//→
				else
				{
					isLeft[FishIndex] = false;
				}

				//左右から位置を設定
				if (isLeft[FishIndex])
				{
					//右端に設定
					_X[FishIndex] = (float)(SCREEN_SIZE_X + FISH_X_SIZE / 2);
					_Y[FishIndex] = (float)(GetRand(SCREEN_SIZE_Y - 145 - 30) + 30);
				}
				else
				{
					//左端に設定
					_X[FishIndex] = 0 - FISH_X_SIZE / 2;
					_Y[FishIndex] = (float)(GetRand(SCREEN_SIZE_Y - 145 - 30) + 30);
				}

				//魚を使用中にする
				isActive[FishIndex] = true;

				// かかっていないにする
				isCaught[FishIndex] = false;

				//魚のスピードを設定
				fishSpeed[FishIndex] = GetRand((int)FISH_SPEED - 1) + 1;

				//次の出現時間を設定
				Poptime = GetRand(FISH_POP_TIME) + 1;
				//カウントをリセット
				countTime = 0;

				break;
			}
		}
	}
}

//魚かかったとき(引数:ルアーの座標)
void Fish::Caught(float lureX, float lureY)
{
	for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
		if (isCaught[FishIndex]) {
			// 魚をルアーの位置まで移動
			_X[FishIndex] = lureX;
			_Y[FishIndex] = lureY;

			//釣れた
			if (_X[FishIndex] == LURE_POS_X && _Y[FishIndex] == LURE_POS_Y) {
				// フラグを初期化
				isCaught[FishIndex] = false;
				isActive[FishIndex] = false;

				CaughtNum++; // 釣れている数を加算

				fishChance = false;

				//得点加算演出==========================
		
				//得点加算の座標追加文設定
				scoreAddY = 0;
				//得点加算の透明度設定
				scoreFade = 255;
				//得点加算演出へ
				addScore = true;
			}
		}
	}
}

//得点加算の動き
void Fish::ScoreAddMove()
{
	if (addScore)
	{
		if (scoreAddY < 50)
		{
			scoreAddY += 2;
		}
		else
		{
			scoreAddY = 50;
		}

		if (scoreFade > 0)
		{
			scoreFade -= 20;
		}
		else
		{
			scoreFade = 0;
		}

		if (scoreAddY == 50 && scoreFade == 0)
		{
			addScore = false;
		}
	}
	
}