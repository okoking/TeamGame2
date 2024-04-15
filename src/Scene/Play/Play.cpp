#include "Play.h"
#include "../../FrameRate/FrameRate.h"

//画像パス
const char BACKGROUND_PATH[] = { "data/play/backGround.png" };		//プレイシーンの背景画像のパス
const char ENEMY_PATH[] = { "data/play/move1.png" };				//プレイシーンの背景画像のパス

//プレイシーンの初期化
void Play::Init()
{
	//プレイヤー関連
	player.Init();

	// 矢
	arrow.Init();

	//音
	Sound::Bgm::Play(BGM_PLAY);
	Sound::Bgm::SetVolume(BGM_PLAY, 50);

	//プレイシーンの通常処理に遷移
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイシーンの読み込み
void Play::Load()
{
	//画像読み込み
	//背景関連
	backgroundHandle = LoadGraph(BACKGROUND_PATH);	//背景
	enemyhandle = LoadGraph(ENEMY_PATH);	//敵
	ImgHP = LoadGraph("data/play/HP.png");
	img_sikaku = LoadGraph("data/play/sikaku.png");
	//プレイヤー関連
	player.Load();									//プレイヤー画像の読み込み

	// 矢
	arrow.Load();
}

//プレイシーンの通常処理
void Play::Step()
{
	player.Step();			//プレイヤーの通常処理

	arrow.Step();			// 矢の通常処理

	// 矢の当たり判定
	ArrowCollision(player.GetShieldAngle());
}

//プレイシーンの描画処理
void Play::Draw()
{
	//敵500 0
	DrawGraph(500, 0,enemyhandle, true);
	//DrawRotaGraph(400, 300,1.0f,0.0f, enemyhandle, true);

	DrawLineBox(HEART_INIT_POS_X - HEART_INIT_POS_Y, 0, HEART_INIT_POS_X + HEART_INIT_POS_Y, HEART_INIT_POS_Y + HEART_INIT_POS_Y,
		GetColor(255, 255, 255));

	player.Draw();		//プレイヤー画像の描画
	arrow.Draw();		//矢の描画

	//文字の大きさを変更
	SetFontSize(20);
	//操作説明を書く
	DrawFormatString(20, 100, GetColor(255, 255, 255), "来る方向に盾を向けろ");
	DrawFormatString(20, 120, GetColor(255, 255, 255), "赤い矢は防ぐな");
	DrawFormatString(20, 140, GetColor(255, 255, 255), "後は雰囲気でなんとかしろ");
	DrawFormatString(500, 40, GetColor(255, 255, 255), "ガード成功数:%d",player.GetGuradCnt());
	
	DrawRotaGraph(400, 300, 1.0f, 0.0f, img_sikaku, true);
	
	//文字の大きさを元に戻す
	SetFontSize(20);
}

//プレイヤーシーンの終了処理
void Play::Fin()
{
	player.Fin();		//プレイヤーの終了処理
	arrow.Fin();		//矢終了処理
	DeleteGraph(enemyhandle);	// 敵画像処理
	//gem
	Sound::Bgm::StopSound(BGM_PLAY);	

	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

// 矢の当たり判定
void Play::ArrowCollision(SHIELD_ANGLE ShieldAngle)
{
	for (int ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		if (arrow.IsUse(ArrowIndex) && !arrow.GetisInversion(ArrowIndex)) {
			// 盾
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_RIGHT) {
				if (ShieldAngle == ARROW_ANGLE_RIGHT) {
					if (arrow.GetPosX(ArrowIndex) - ARROW_SIZE_X / 2 < HEART_INIT_POS_X + HEART_SIZE + SHIELD_HEIGHT / 2) {
						if (arrow.GetArrowType(ArrowIndex) == ARROW_TYPE_RED) {
							// ダメージ処理
							player.Damaged();
						}
						else {
							//se
							Sound::Se::Play(SE_GUARD);
							player.AddGuardCnt();
						}
						arrow.ResetArrow(ArrowIndex);
						arrow.SetUse(ArrowIndex, false);
						continue;
					}
				}
			}
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_DOWN) {
				if (ShieldAngle == ARROW_ANGLE_DOWN) {
					if (arrow.GetPosY(ArrowIndex) - ARROW_SIZE_X / 2 < HEART_INIT_POS_Y + HEART_SIZE + SHIELD_HEIGHT / 2) {
						if (arrow.GetArrowType(ArrowIndex) == ARROW_TYPE_RED) {
							// ダメージ処理
							player.Damaged();
						}
						else {
							//se
							Sound::Se::Play(SE_GUARD);
							player.AddGuardCnt();
						}
						arrow.ResetArrow(ArrowIndex);
						arrow.SetUse(ArrowIndex, false);
						continue;
					}
				}
			}
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_LEFT) {
				if (ShieldAngle == ARROW_ANGLE_LEFT) {
					if (arrow.GetPosX(ArrowIndex) + ARROW_SIZE_X / 2 > HEART_INIT_POS_X - HEART_SIZE - SHIELD_HEIGHT / 2) {
						if (arrow.GetArrowType(ArrowIndex) == ARROW_TYPE_RED) {
							// ダメージ処理
							player.Damaged();
						}
						else {
							//se
							Sound::Se::Play(SE_GUARD);
							player.AddGuardCnt();
						}
						arrow.ResetArrow(ArrowIndex);
						arrow.SetUse(ArrowIndex, false);
						continue;
					}
				}
			}
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_UP) {
				if (ShieldAngle == ARROW_ANGLE_UP) {
					if (arrow.GetPosY(ArrowIndex) + ARROW_SIZE_X / 2 > HEART_INIT_POS_Y - HEART_SIZE - SHIELD_HEIGHT / 2) {
						if (arrow.GetArrowType(ArrowIndex) == ARROW_TYPE_RED) {
							// ダメージ処理
							player.Damaged();
						}
						else {
							//se
							Sound::Se::Play(SE_GUARD);
							player.AddGuardCnt();
						}
						arrow.ResetArrow(ArrowIndex);
						arrow.SetUse(ArrowIndex, false);
						continue;
					}
				}
			}

			// ハート
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_RIGHT) {
				if (arrow.GetPosX(ArrowIndex) - ARROW_SIZE_X / 2 < HEART_INIT_POS_X + HEART_SIZE) {
					if (arrow.GetArrowType(ArrowIndex) != ARROW_TYPE_RED) {
						// 赤以外ダメージ処理
						player.Damaged();
					}
					else {
						//se
						Sound::Se::Play(SE_GUARD);
						player.AddGuardCnt();
					}
					arrow.ResetArrow(ArrowIndex);
					arrow.SetUse(ArrowIndex, false);
					continue;
				}
			}
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_DOWN) {
				if (arrow.GetPosY(ArrowIndex) - ARROW_SIZE_X / 2 < HEART_INIT_POS_Y + HEART_SIZE) {
					if (arrow.GetArrowType(ArrowIndex) != ARROW_TYPE_RED) {
						// 赤以外ダメージ処理
						player.Damaged();
					}
					else {
						//se
						Sound::Se::Play(SE_GUARD);
						player.AddGuardCnt();
					}
					arrow.ResetArrow(ArrowIndex);
					arrow.SetUse(ArrowIndex, false);
					continue;
				}
			}
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_LEFT) {
				if (arrow.GetPosX(ArrowIndex) + ARROW_SIZE_X / 2 > HEART_INIT_POS_X - HEART_SIZE) {
					if (arrow.GetArrowType(ArrowIndex) != ARROW_TYPE_RED) {
						// 赤以外ダメージ処理
						player.Damaged();
					}
					else {
						//se
						Sound::Se::Play(SE_GUARD);
						player.AddGuardCnt();
					}
					arrow.ResetArrow(ArrowIndex);
					arrow.SetUse(ArrowIndex, false);
					continue;
				}
			}
			if (arrow.GetArrowAngle(ArrowIndex) == ARROW_ANGLE_UP) {
				if (arrow.GetPosY(ArrowIndex) + ARROW_SIZE_X / 2 > HEART_INIT_POS_Y - HEART_SIZE) {
					if (arrow.GetArrowType(ArrowIndex) != ARROW_TYPE_RED) {
						// 赤以外ダメージ処理
						player.Damaged();
					}
					else {
						//se
						Sound::Se::Play(SE_GUARD);
						player.AddGuardCnt();
					}
					arrow.ResetArrow(ArrowIndex);
					arrow.SetUse(ArrowIndex, false);
					continue;
				}
			}
			
		}
	}
}


