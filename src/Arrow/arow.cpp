#include "DxLib.h"
#include "arow.h"
#include "../Collision/Collision.h"
Arrow::Arrow() {}
Arrow::~Arrow() {}


// 弾初期化
void Arrow::Init()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		arrowInfo[i].handle = LoadGraph("data/play/kari_arrow.png");
		arrowInfo[i].x = 0;
		arrowInfo[i].y = 0;
		arrowInfo[i].isUse = false;
	}
}

// 弾発射処理
bool Arrow::IsShot(int shotPosX, int shotPosY)
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		if (!arrowInfo[i].isUse) {
			// 左右上下から出現
			// 弾座標の初期位置に設定
			arrowInfo[i].x = shotPosX;
			arrowInfo[i].y = shotPosY;
			arrowInfo[i].isUse = true;

			// 発射成功
			return true;
		}
	}

	// 発射失敗
	return false;
}

// 弾の移動処理
void Arrow::Move()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			// 弾が使用中なら移動させる
			arrowInfo[i].x += 3;

			// ハートに当たったら未使用に戻すIsHitRect使う
			if (Collision::Rect(326,225,148,149, arrowInfo[i].x, arrowInfo[i].y,108,56)) {
				arrowInfo[i].isUse = false;
			}
		}
	}
}

// 弾の描画
void Arrow::Draw()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			DrawGraph(arrowInfo[i].x+(i*2), arrowInfo[i].y, arrowInfo[i].handle, true);
		}
	}
}