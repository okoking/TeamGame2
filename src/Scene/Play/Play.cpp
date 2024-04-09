#include "Play.h"
#include "../../FrameRate/FrameRate.h"

//画像パス
const char BACKGROUND_PATH[] = { "data/play/backGround.png" };		//プレイシーンの背景画像のパス
const char JETTY_PATH[] = { "data/play/jetty.png" };					//プレイシーンの桟橋画像のパス
const char SCORE_BOARD_PATH[] = { "data/play/scoreBoard.png" };					//プレイシーンの桟橋画像のパス

TimeLimit timeLimit;	//時間制限

Fish fish;				//魚クラス

bool fishChance;	//hit状態フラグ

//プレイシーンの初期化
void Play::Init()
{
	
	IsFishToLureHit = false;		//魚とルアーが当たったかどうかの確認フラグの初期化

	player.Init();					//プレイヤーの初期化
	fish.Init();					//フィッシュの初期化
	lure.Init();					//ルアーの初期化

	//制限時間の初期化
	timeLimit.Init();

	caughtCountTime = 0;
	fishChance = false;
	fishingChanceNum = 0;

	//bgm
	Sound::Bgm::Play(BGM_PLAY);
	Sound::Bgm::Play(BGM_SEA);

	//プレイシーンの通常処理に遷移
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイシーンの初期値設定
void Play::SetDefaultValue()
{
	//プレイヤーの初期値設定
	player.SetDefaultValue();
}

//プレイシーンの読み込み
void Play::Load()
{
	//画像読み込み
	//背景関連
	backgroundHandle = LoadGraph(BACKGROUND_PATH);	//背景
	jettyHandle = LoadGraph(JETTY_PATH);			//桟橋
	scoreImageHandle = LoadGraph(SCORE_BOARD_PATH);			//スコアボード
	
	//プレイヤー関連
	player.Load();									//プレイヤー画像の読み込み
	fish.Load();									//フィッシュの画像の読み込み
	lure.Load();									//ルアー画像の読み込み
}

//プレイヤーシーンの通常処理
void Play::Step()
{
	player.Step();			//プレイヤーの通常処理
	fish.Step(lure.GetXPos(),lure.GetYPos(),lure.GetisUse(),lure.GetisCaught());			//フィッシュの通常処理
	lure.Step();			//ルアーの通常処理

	//魚とルアーが当たったかどうかを確認するフラグに代入
	IsFishToLureHit = FishToLureCollision();

	//確認
	FishToLureHit();

	//制限時間の通常処理
	timeLimit.Step();
	
}

//プレイヤーシーンの描画処理
void Play::Draw()
{
	//背景描画
	DrawGraph(0, 0, backgroundHandle, true);	//背景
	DrawGraph(0, 0, jettyHandle, true);	//桟橋
	DrawGraph(600, 500, scoreImageHandle, true);	//スコアボード

	//制限時間の描画
	timeLimit.Draw();

	fish.Draw();		//フィッシュ画像の描画
	lure.Draw();		//ルアー画像の描画		
	player.Draw();		//プレイヤー画像の描画

	//文字の大きさを変更
	SetFontSize(20);
	//操作説明を書く
	DrawFormatString(20, 465, GetColor(255, 255, 255), "クリックした位置にルアーを投げる");
	//文字の大きさを元に戻す
	SetFontSize(20);

	//確認
	//if (IsFishToLureHit)
		//DrawFormatString(100, 100, GetColor(255, 0, 0), "%f", num);

	//for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
	//	if (fish.GetisCaught(FishIndex))
	//		DrawFormatString(100, 100, GetColor(255, 0, 0), "%f", num);
	//}

}

//プレイヤーシーンの終了処理
void Play::Fin()
{
	lure.Fin();			//ルアーの終了処理
	player.Fin();		//プレイヤーの終了処理
	fish.Fin();			//フィッシュの終了処理

	//制限時間の終了処理
	timeLimit.Fin();

	//gem
	Sound::Bgm::StopSound(BGM_PLAY);
	Sound::Bgm::StopSound(BGM_SEA);

	Sound::Bgm::StopSound(BGM_FISH);
	Sound::Bgm::StopSound(BGM_FISHING);
	Sound::Bgm::StopSound(BGM_RECOVERY);

	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

//魚とルアーの当たり判定
bool Play::FishToLureCollision()
{
	//ルアーを投げているか
	if (lure.GetisUse())
	{
		//魚の数分for分を回す
		for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
			// 今あたっているなら飛ばす
			if (lure.GetisCaught())
				continue;

			//魚が生きているかどうか
			if (fish.GetIsActive(FishIndex)) {

				//一定距離に入ったら以下
				if (GetDistance(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex)) < 50)
				{
					if (!fishChance)
					{
						//３０％の確率でhit
						if (GetRand(100) < 30)
						{
							//se
							Sound::Se::Play(SE_LURE);

							//魚を影にする
							fish.SetisCaught(FishIndex, true);

							//チャンスに移行
							fishChance = true;
							//ルアーの透明度を変える
							lure.SetFade(255 * 0.5);

							//hitした魚を記録
							fishingChanceNum = FishIndex;
						}
						//hitしなかった
						else
						{
							//se
							Sound::Se::Play(SE_HIT);

							//魚を引かせる
							if (fish.GetIsLeft(FishIndex))
							{
								fish.AddPosX(FishIndex, -50);
							}
							else
							{
								fish.AddPosX(FishIndex, 50);
							}
						}
					}
				}
				//魚とルアーの当たり判定
				//if (GetDistance(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex)) < 70)
				//{
				//	// どの魚があたったかを同時にとる
				//	fish.SetisCaught(FishIndex, true);
				//	lure.SetisCaught(true);

				//	return true;
				//}
			}
		}

		//hitかつ釣りミニゲーム中じゃない
		if (fishChance&&!lure.GetisCaught())
		{
			//魚が影なら
			if (fish.GetisCaught(fishingChanceNum))
			{
				//座標をルアーに固定
				fish.SetPosX(fishingChanceNum, lure.GetXPos());
				fish.SetPosY(fishingChanceNum, lure.GetYPos());
			}

			//hit制限時間を加算
			caughtCountTime += 1.0f / FRAME_RATE;

			//制限時間が一秒以下なら以下
			if (caughtCountTime <= 1.0f)
			{
				//左クリックでミニゲームへ
				if (Input::Mouse::Push(MOUSE_INPUT_LEFT))
				{
					// どの魚があたったかを同時にとる
					fish.SetisCaught(fishingChanceNum, true);
					lure.SetisCaught(true);
					caughtCountTime = 0.0f;

					return true;
				}
			}
			//hit制限時間を越えた
			else
			{
				//魚が逃げる（生存フラグを折る）
				fish.SetIsActive(fishingChanceNum, false);
				//hitしてない
				fishChance = false;
				//制限時間のリセット
				caughtCountTime = 0.0f;

				//ルアーの透明度を元に戻す
				lure.SetFade(255);
			}
		}
	}

	//hitしていなかったらルアーの透明度は最大
	if (!fishChance)
	{
		lure.SetFade(255);
	}


	return false;
}

//魚とルアーが当たった時
void Play::FishToLureHit()
{
	if (IsFishToLureHit)
	{
		for (int FishIndex = 0; FishIndex < FISH_MAX_NUM; FishIndex++) {
			fish.SetHitUpdatePosX(GetDirection(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex), 'x', 1), FishIndex);
			fish.SetHitUpdatePosX(GetDirection(lure.GetXPos(), lure.GetYPos(), fish.GetXPos(FishIndex), fish.GetYPos(FishIndex), 'x', 1), FishIndex);
		}
	}
}
