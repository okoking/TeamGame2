#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include"MathPlus.h"

//２から１への進行方向と移動量：向かう場所XY1  動かしたいものXY2  XとYのどちらを出すか  増加量
float GetDirection(float x1, float y1, float x2, float y2, char moji,float s)
{
	float x = x1 - x2;
	float y = y1 - y2;

	float n = x * x + y * y;

	n = sqrtf(n);

	if (moji == 'x')
	{
		return x / n * s;
	}
	else if (moji == 'y')
	{
		return y / n * s;
	}
	return 0;
}

//2点間の距離：開始地点XY　終了地点XY
float GetDistance(float startX, float startY, float endX, float endY)
{
	float num = 0.0f;
	num = ((startX - endX) * (startX - endX)) + ((startY - endY) * (startY - endY));
	num = sqrtf(num);

	return num;
}

//1から2への角度(ラジアン)：開始地点XY　終了地点XY
float GetAngle(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;
	num=atan2f(Ay - By, Ax - Bx);

	return num;
}

//ベクトルの内積を求めて正か負を返す：向かせる場所XY　向かせたいものXY
bool GetInnerProduct(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;

	num = Ax * Bx + Ay * By;
	if (num > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//度をラジアンに変換（引数：度）
float DegToRad(float degree)
{
	return degree * (float)M_PI / 180.0f;
}