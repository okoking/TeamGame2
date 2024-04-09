#include "Collision.h"

//IsHitRectの定義（四角）
bool Collision::Rect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)		//X,Yは座標、wが横幅、hが縦幅、画像はDrawGraphで表示してﾈ
{
	if (Bx< Ax + Aw &&
		Bx + Bw>Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		return true;
	}
	return false;
}

bool Collision::Rect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
	if (Bx< Ax + Aw &&
		Bx + Bw>Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		return true;
	}
	return false;
}

//IsHitCircleの定義（円形）
bool Collision::Circlr(int Ra, int Rb, int Xa, int Ya, int Xb, int Yb)					//Rが半径、X,Yは中央、画像はDrawRotaGraphで表示してﾈ
{
	if ((Ra + Rb) * (Ra + Rb) > (Xa - Xb) * (Xa - Xb) + (Ya - Yb) * (Ya - Yb))
	{
		return true;
	}
	return false;
}
