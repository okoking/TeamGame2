#include "DxLib.h"
#include "arow.h"
#include "../Collision/Collision.h"
#include "../Player/Player.h"
#include "../Scene/Scene.h"

// コンストラクタ
Arrow::Arrow() 
{
	for (int ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			arrowInfo[ArrowIndex].handle[ArrowType] = -1;
		}

		arrowInfo[ArrowIndex].x = 0;
		arrowInfo[ArrowIndex].y = 0;
		arrowInfo[ArrowIndex].isUse = false;
		arrowInfo[ArrowIndex].ShotInterval = ARROW_MAX_INTERVAL;

		arrowInfo[ArrowIndex].angle = ARROW_ANGLE_UP;
		arrowInfo[ArrowIndex].arrowtype = ARROW_TYPE_NORMAL;
	}
}
Arrow::~Arrow() {}


// 矢初期化
void Arrow::Init()
{
	for (int  ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			arrowInfo[ArrowIndex].handle[ArrowType] = 0;
		}

		arrowInfo[ArrowIndex].x = 0;
		arrowInfo[ArrowIndex].y = 0;
		arrowInfo[ArrowIndex].isUse = false;

		arrowInfo[ArrowIndex].angle = (ARROW_ANGLE)GetRand(3);
		arrowInfo[ArrowIndex].ShotInterval = GetRand(ARROW_MAX_INTERVAL);

		arrowInfo[ArrowIndex].arrowtype = ARROW_TYPE_NORMAL;
	}
}

// データロード
void Arrow::Load()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		arrowInfo[i].handle[ARROW_TYPE_NORMAL] = LoadGraph(NORMALARROW_PATH);
	}
}

// 矢発射処理
void Arrow::IsShot()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (!arrowInfo[i].isUse) {
			// 左右上下から出現
			// 矢座標の初期位置に設定
			// 矢の発射方向に対応した値を入れる

			if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
				arrowInfo[i].x = 0;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = 0;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
				arrowInfo[i].x = SCREEN_SIZE_X;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = SCREEN_SIZE_Y;
			}

			arrowInfo[i].ShotInterval++;

			if (arrowInfo[i].ShotInterval > ARROW_MAX_INTERVAL) {
				arrowInfo[i].ShotInterval = ARROW_MAX_INTERVAL;
				arrowInfo[i].isUse = true;
			}
		}
	}
}

// 矢の移動処理
void Arrow::Move()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			// 矢が使用中なら移動させる
			// 矢の発射方向に対応した値を入れる
			if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
				arrowInfo[i].x += ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
				arrowInfo[i].y += ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
				arrowInfo[i].x -= ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
				arrowInfo[i].y -= ARROW_SPEED;
			}
		}
	}
}

// 矢の通常処理
void Arrow::Step()
{
	// 矢発射処理
	IsShot();

	// 矢の移動処理
	Move();
}

// 矢の描画
void Arrow::Draw()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			DrawRotaGraph((int)arrowInfo[i].x, (int)arrowInfo[i].y, 1.0f, 
				(arrowInfo[i].angle + 2) * 3.14 / 2, arrowInfo[i].handle[arrowInfo[i].arrowtype], true);
		}
	}
}

// 矢終了処理
void Arrow::Fin()
{
	for (int ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			DeleteGraph(arrowInfo[ArrowIndex].handle[ArrowType]);
		}
	}
}

// 矢のランダム要素をリセット
void Arrow::ResetArrow(int _index)
{
	arrowInfo[_index].angle = (ARROW_ANGLE)GetRand(3);

	arrowInfo[_index].ShotInterval = GetRand(ARROW_MAX_INTERVAL);

}
