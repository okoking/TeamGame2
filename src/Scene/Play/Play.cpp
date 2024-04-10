#include "Play.h"
#include "../../FrameRate/FrameRate.h"

//画像パス
const char BACKGROUND_PATH[] = { "data/play/backGround.png" };		//プレイシーンの背景画像のパス

//プレイシーンの初期化
void Play::Init()
{
	//プレイヤー関連
	player.Init();

	//プレイシーンの通常処理に遷移
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイシーンの読み込み
void Play::Load()
{
	//画像読み込み
	//背景関連
	backgroundHandle = LoadGraph(BACKGROUND_PATH);	//背景
	
	//プレイヤー関連
	player.Load();									//プレイヤー画像の読み込み
}

//プレイシーンの通常処理
void Play::Step()
{
	player.Step();			//プレイヤーの通常処理
}

//プレイシーンの描画処理
void Play::Draw()
{
	//背景描画
	//DrawGraph(0, 0, backgroundHandle, true);	//背景

	player.Draw();		//プレイヤー画像の描画

	//文字の大きさを変更
	SetFontSize(20);
	//操作説明を書く
	DrawFormatString(20, 465, GetColor(255, 255, 255), "来る方向に盾を向けろ");
	//文字の大きさを元に戻す
	SetFontSize(20);
}

//プレイヤーシーンの終了処理
void Play::Fin()
{
	player.Fin();		//プレイヤーの終了処理

	//gem
	Sound::Bgm::StopSound(BGM_PLAY);
	Sound::Bgm::StopSound(BGM_SEA);

	Sound::Bgm::StopSound(BGM_FISH);
	Sound::Bgm::StopSound(BGM_FISHING);
	Sound::Bgm::StopSound(BGM_RECOVERY);


	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
