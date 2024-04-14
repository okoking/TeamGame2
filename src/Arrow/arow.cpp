#include "DxLib.h"
#include "arow.h"
#include "../Collision/Collision.h"
#include "../Player/Player.h"
#include "../Scene/Scene.h"
#include "math.h"

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
		arrowInfo[ArrowIndex].isInversion = false; // 矢反転中フラグ
		arrowInfo[ArrowIndex].isInversioned = false;
	}
	// 同時に発射されないようにする
	Recoverycnt = -1;
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

		arrowInfo[ArrowIndex].arrowtype = (ARROW_TYPE)GetRand(2);

		arrowInfo[ArrowIndex].isInversion = false; // 矢反転中フラグ
		arrowInfo[ArrowIndex].ShotTimeCnt = 0;
		arrowInfo[ArrowIndex].InversionAngle = 0; // 反転中回転しているしている角度
	}
	// 同時に発射されないようにする
	Recoverycnt = RECOVERY_MAX_FRAME;
}

// データロード
void Arrow::Load()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		arrowInfo[i].handle[ARROW_TYPE_NORMAL] = LoadGraph(NORMALARROW_PATH);
		arrowInfo[i].handle[ARROW_TYPE_RED] = LoadGraph(REDARROW_PATH);
		arrowInfo[i].handle[ARROW_TYPE_YELLOW] = LoadGraph(YELLOWARROW_PATH);
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
				arrowInfo[i].x = HEART_INIT_POS_X - HEART_INIT_POS_Y;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = 0;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
				arrowInfo[i].x = HEART_INIT_POS_X + HEART_INIT_POS_Y;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = HEART_INIT_POS_Y + HEART_INIT_POS_Y;
			}

			arrowInfo[i].ShotInterval++;

			Recoverycnt++;

			if (arrowInfo[i].ShotInterval > ARROW_MAX_INTERVAL) {
				if (Recoverycnt > RECOVERY_MAX_FRAME) {
					Recoverycnt = 0;

					arrowInfo[i].ShotInterval = ARROW_MAX_INTERVAL;
					arrowInfo[i].isUse = true;
				}
			}
		}
	}
}

// 矢の移動処理
void Arrow::Move()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (arrowInfo[i].isUse && !arrowInfo[i].isInversion) {
			// 矢が使用中かつ反転中じゃないなら移動させる
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

			arrowInfo[i].ShotTimeCnt++;

			if (arrowInfo[i].ShotTimeCnt > INVERSION_FRAME) {
				arrowInfo[i].ShotTimeCnt = INVERSION_FRAME;
			}
		}

		// 矢が黄色なら
		if (arrowInfo[i].arrowtype == ARROW_TYPE_YELLOW) {
			if (arrowInfo[i].ShotTimeCnt == INVERSION_FRAME) {
				// 矢の発射方向に対応するように矢を移動させる
				if(!arrowInfo[i].isInversioned)
					arrowInfo[i].isInversion = true;
			}
		}

		// 矢反転フラグがONなら
		if (arrowInfo[i].isInversion) {
			arrowInfo[i].InversionAngle += 9.0f;
			arrowInfo[i].x = HEART_INIT_POS_X + cosf(((arrowInfo[i].angle) * 90 + arrowInfo[i].InversionAngle) * 3.14 / 180) * 120;
			arrowInfo[i].y = HEART_INIT_POS_Y + sinf(((arrowInfo[i].angle) * 90 + arrowInfo[i].InversionAngle) * 3.14 / 180) * 120;

			if (arrowInfo[i].InversionAngle > 180.0f) {
				// 矢の向きを変更する
				if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
					arrowInfo[i].angle = ARROW_ANGLE_RIGHT;
					arrowInfo[i].y = HEART_INIT_POS_Y;
				}
				else if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
					arrowInfo[i].angle = ARROW_ANGLE_DOWN;
					arrowInfo[i].x = HEART_INIT_POS_X;
				}
				else if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
					arrowInfo[i].angle = ARROW_ANGLE_LEFT;
					arrowInfo[i].y = HEART_INIT_POS_Y;
				}
				else if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
					arrowInfo[i].angle = ARROW_ANGLE_UP;
					arrowInfo[i].x = HEART_INIT_POS_X;
				}
				arrowInfo[i].InversionAngle = 0.0f;
				arrowInfo[i].isInversioned = true;
				arrowInfo[i].isInversion = false;
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
				((arrowInfo[i].angle + 2) * 90 + arrowInfo[i].InversionAngle) * 3.14 / 180, arrowInfo[i].handle[arrowInfo[i].arrowtype], true);
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
	arrowInfo[_index].arrowtype = (ARROW_TYPE)GetRand(2);

	arrowInfo[_index].ShotInterval = GetRand(ARROW_MAX_INTERVAL);
	arrowInfo[_index].ShotTimeCnt = 0;
	arrowInfo[_index].InversionAngle = 0.0f;

	arrowInfo[_index].isInversioned = false;
}
