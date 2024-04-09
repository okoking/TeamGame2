//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"					//DXライブラリのインクルード
#include "FrameRate/FrameRate.h"	//フレームレート
#include "Input/Input.h"			//入力機能
#include "Scene/Scene.h"			//シーン関連
#include "Scene/Title/Title.h"		//タイトル
#include "Scene/Play/Play.h"
#include "Scene/Result/Result.h"	//リザルト

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//ウィンドウの名前を変える
	SetMainWindowText("釣りキング");

	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) 
	{
		return -1;
	}

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);

	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;		//シーンID

	//シーンクラス宣言
	Title title;
	Play play;				//プレイシーン
	Rasult rasult;

	//入力制御初期化
	Input::Init();

	//サウンド初期化
	Sound::Init();

	//-----------------------------------------
	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		//フレームレート管理
		if (FPS())
		{
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}

			//画面に表示されたものを初期化
			ClearDrawScreen();

			//入力処理通常処理
			Input::Step();

			//-----------------------------------------
			//ここからゲームの本体を書くことになる
			//-----------------------------------------

			//火山
			//シーン遷移
			switch (g_CurrentSceneID)
			{
				//タイトルシーン初期化
			case SCENE_ID_INIT_TITLE:

				//初期化
				title.Init();

				break;

				//タイトルシーン通常処理
			case SCENE_ID_LOOP_TITLE:

				//通常処理
				title.Step();

				//描画
				title.Draw();

				break;

				//タイトルシーン終了処理
			case SCENE_ID_FIN_TITLE:

				//終了処理
				title.Fin();

				break;


				//プレイシーン初期化
			case SCENE_ID_INIT_PLAY:

				play.Init();	//プレイシーン初期化

				play.Load();	//プレイシーンの読み込み

				play.SetDefaultValue();

				break;
				//プレイシーン通常処理
			case SCENE_ID_LOOP_PLAY:

				play.Step();	//プレイシーンの通常処理

				play.Draw();	//プレイシーンの描画処理

				break;
				//プレイシーン終了処理
			case SCENE_ID_FIN_PLAY:

				play.Fin();		//プレイシーンの終了処理

				break;


				//リザルトシーン初期化処理
			case SCENE_ID_INIT_RESULT:

				rasult.Init();

				break;
				//リザルトシーン通常処理
			case SCENE_ID_LOOP_RESULT:

				rasult.Step();
				rasult.Draw();

				break;
				//リザルトシーン終了処理
			case SCENE_ID_FIN_RESULT:

				rasult.Fin();

				break;
			}


			//-----------------------------------------
			//ループの終わりに

			//FPS計算
			CalcFPS();

			//FPS表示（デバック用）
			DrawFPS();

			//フリップ関数
			ScreenFlip();
		}
	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く


	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

