#include "Lure.h"
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Scene/Scene.h"
#include "../../MathPlus/MathPlus.h"
#include "../../Effect/Effect.h"
#include "../../FrameRate/FrameRate.h"

// コンストラクタ
Lure::Lure()
{
	// ルアー画像ハンドル
	for (int i = 0; i < LURE_IMAGE_TYPE_NUM; i++) {
		handle[i] = -1;
	}

	// 現在の座標
	_X = 0.0f;
	_Y = 0.0f;
	// 移動後の座標
	_SaveX = 0.0f;
	_SaveY = 0.0f;

	// 使用中かどうか
	isActive = true;

	//ルアーを投げたら
	isUse = false;
	// ルアーを投げているか
	isThrow = false;
	// ルアーが画面の左半分にあるか
	isLureLeft = false;
	// かかっているかどうか
	isCaught = false;

	fade = -1; //透明度
	fishingpower = 0; // 竿を引く力

	// ルアーのマウス
	LureMouse = {};
}

// 座標更新用
void Lure::UpdatePos()
{
	_X = _SaveX;
	_Y = _SaveY;
}

// 初期化
void Lure::Init()
{ 
	// 使用中かどうか
	isActive = false;
	//ルアーを投げたら
	isUse = false;
	// ルアーを投げているか
	isThrow = false;
	// かかっているかどうか
	isCaught = false;

	// 現在の座標
	_X = LURE_POS_X;
	_Y = LURE_POS_Y;

	// 直前の座標
	_SaveX = _X;
	_SaveY = _Y;

	// ルアーのマウス処理初期化
	LureMouse.Init();

	//透明度
	fade = 255;

	// 竿を引く力
	fishingpower = 0;

	//エフェクトの初期化
	Effect::Init();
	//エフェクトを指定の数読み込む
	Effect::Load(EFFECT_TYPE_RIPPLE,20);
	//間隔をリセット
	effectInterval = 0;
	seFrg = false;
}

// 画像ロード
void Lure::Load()
{
	// ルアーの画像ロード
	handle[LURE_IMAGE_TYPE_LURE] = LoadGraph(LURE_PATH);
	handle[LURE_IMAGE_TYPE_GAUGE] = LoadGraph(GAUGE_PATH);
	handle[LURE_IMAGE_TYPE_BAR] = LoadGraph(BAR_PATH);

}

// マウス処理
void Lure::Mouse()
{
	//ルアーが投げられていなかったら
	if (!isUse)
	{
		int zX = 0, zY = 0;	//一時保存用の座標

		// マウスの位置を取得
		GetMousePoint(&zX, &zY);

		//左クリックを押された かつ 投げている途中じゃない
		if (Input::Mouse::Push(MOUSE_INPUT_LEFT) && !isThrow)
		{
			//ルアー設置範囲内なら以下実行
			if (zX >= 30 && zX <= SCREEN_SIZE_X - 30 &&
				zY >= 30 && zY <= SCREEN_SIZE_Y - 145)
			{
				//クリックした位置にルアーを表示
				_SaveX = (float)zX;
				_SaveY = (float)zY;

				// 投げている判定にする
				isThrow = true;

				// 投げられた位置が画面の左半分かどうか
				if (_SaveX < LURE_POS_X) {
					isLureLeft = true;
				}
				else {
					isLureLeft = false;
				}

				//se
				Sound::Se::Play(SE_FISHING_ROD);

				//isActive = true;
			}
		}
	}
}

// 移動処理
void Lure::Move()
{
	if (!isCaught) {
		// ルアーを投げたなら
		if (isThrow) {
			// ルアーをクリックしたところまでゆっくり移動させる
			_X += GetDirection(_SaveX, _SaveY, _X, _Y, 'x', 10);
			_Y += GetDirection(_SaveX, _SaveY, _X, _Y, 'y', 10);

			// クリックしたところまで動いたら止まる
			if ((isLureLeft && _X <= _SaveX) ||
				(!isLureLeft && _X >= _SaveX)) {
				_X = _SaveX; // クリックしたところまで動いたら止まる
			}

			if (_Y < _SaveY) {
				_Y = _SaveY; // クリックしたところまで動いたら止まる
			}

			// クリックしたところまで移動したら
			if (_X == _SaveX && _Y == _SaveY) {
				// 投げていない
				isThrow = false;

				// 使用中にする
				isUse = true;

				//波紋を出す
				effectInterval = 0.5f;

				//se
				Sound::Se::Play(SE_LURE);
			}
		}

		//ルアーを投げれたら
		if (isUse)
		{
			//左クリックが押し続けられていたら
			if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
			{
				//初期値に向かって進行
				_X += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'x', 3);
				_Y += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'y', 3);

				//波紋の間隔を加速
				effectInterval += 3.0f / FRAME_RATE;

				//初期値の範囲、20以内に入ったら
				if (GetDistance(LURE_POS_X, LURE_POS_Y, _X, _Y) <= 20)
				{
					//初期値を代入
					_X = LURE_POS_X;
					_Y = LURE_POS_Y;

					//使用フラグを折る
					isUse = false;


					//isActive = false;
				}
			}

			//se用処理
			//左クリックが押されたら
			if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
			{
				Sound::Bgm::Play(BGM_RECOVERY);
			}

			if(Input::Mouse::Release(MOUSE_INPUT_LEFT))
			{
				Sound::Bgm::StopSound(BGM_RECOVERY);
			}
		}
		else
		{
			//se
			Sound::Bgm::StopSound(BGM_RECOVERY);
		}
	}
}

// 通常処理
void Lure::Step()
{
	//ルアー投げる処理
	Mouse();
	//巻き取り
	Move();
	// 釣り処理
	Fishing();

	//以下演出
	//ルアーが投げられていたら以下
	if (isUse)
	{
		//波紋の間隔を加算
		effectInterval += 1.0f / FRAME_RATE;
		//指定の時間になったら
		if (effectInterval >= 0.7f)
		{
			//エフェクトを出す
			Effect::Play(EFFECT_TYPE_RIPPLE, _X, _Y);
			//時間を初期化
			effectInterval = 0.0f;
		}
	}

	//エフェクトの通常処理
	Effect::Step();
}

// 画像描画
void Lure::Draw()
{

	//デバック用　ルアーの範囲
	DrawBox(30, 30, SCREEN_SIZE_X - 30, SCREEN_SIZE_Y - 145, GetColor(0, 0, 255), false);

	/*if (isActive) {*/

	//エフェクト描画
	Effect::Draw();

	//透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawRotaGraph((int)_X, (int)_Y, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_LURE], true, false);
	//表示を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//DrawRotaGraph(500, 500, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_LURE], true, false);
	//}
	
	//釣り糸
	DrawLine((int)_X, (int)_Y, (int)(LURE_POS_X - 2), (int)(LURE_POS_Y - 5), GetColor(255, 255, 255));

	if (isCaught) {
		DrawRotaGraph(GAUGE_POS_X, GAUGE_POS_Y, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_GAUGE], true, false);
		DrawRotaGraph(GAUGE_POS_X - GAUGE_SIZE_X / 2 + fishingpower, GAUGE_POS_Y, 1.0f, 0.0f, handle[LURE_IMAGE_TYPE_BAR], true, false);
	}
}

// 終了処理
void Lure::Fin()
{
	// ルアーの画像削除
	for (int i = 0; i < LURE_IMAGE_TYPE_NUM; i++) {
		DeleteGraph(handle[i]);
	}
}

// 釣り処理
void Lure::Fishing()
{
	if (isCaught) {
		if (!seFrg)
		{
			seFrg = true;
			Sound::Bgm::Play(BGM_FISHING);
			Sound::Bgm::Play(BGM_FISH);
		}

		if (Input::Mouse::Keep(MOUSE_INPUT_LEFT)) {
			fishingpower += 3; // 左クリックが押されている間powerが高くなる
		}
		else {
			fishingpower -= 3; // 押されていないと減っていく
		}

		if (fishingpower > MAX_FISHING_POWER) {
			fishingpower = MAX_FISHING_POWER;
		}
		else if (fishingpower < 0) {
			fishingpower = 0;
		}

		// fishingpowerが中央の範囲なら
		// ※難易度要調整
		if (fishingpower >= 75 && fishingpower <= MAX_FISHING_POWER - 75) {
			//初期値に向かって進行
			_X += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'x', 1);
			_Y += GetDirection(LURE_POS_X, LURE_POS_Y, _X, _Y, 'y', 1);

			//波紋間隔を加速
			effectInterval += 3.0f / FRAME_RATE;
		}

		//初期値の範囲、10以内に入ったら
		if (GetDistance(LURE_POS_X, LURE_POS_Y, _X, _Y) <= 10)
		{
			//初期値を代入
			_X = LURE_POS_X;
			_Y = LURE_POS_Y;

			//使用フラグを折る
			isUse = false;

			// fishingpowerを初期化
			fishingpower = 0;

			//かかっていないにする
			isCaught = false;

			//se
			Sound::Se::Play(SE_FISH_GET);
		}

		////se用処理
		//	//左クリックが押されたら
		//if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
		//{
		//	Sound::Bgm::Play(BGM_FISHING);
		//	Sound::Bgm::Play(BGM_FISH);
		//}

		//if (Input::Mouse::Release(MOUSE_INPUT_LEFT))
		//{
		//	Sound::Bgm::StopSound(BGM_FISHING);
		//	Sound::Bgm::StopSound(BGM_FISH);
		//}
	}
	else
	{
		seFrg = false;
		Sound::Bgm::StopSound(BGM_FISHING);
		Sound::Bgm::StopSound(BGM_FISH);
	}
}
