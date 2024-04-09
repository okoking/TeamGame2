#pragma once

//２から１への進行方向と移動量：向かう場所XY1  動かしたいものXY2  XとYのどちらを出すか  増加量
float GetDirection(float x1, float y1, float x2, float y2, char moji, float s);

//2点間の距離：開始地点XY　終了地点XY
float GetDistance(float startX, float startY, float endX, float endY);

//1から2への角度(ラジアン)：向かせる場所XY　向かせたいものXY
float GetAngle(float Ax, float Ay, float Bx, float By);

//ベクトルの内積を求めて正か負を返す：向かせる場所XY　向かせたいものXY
bool GetInnerProduct(float Ax, float Ay, float Bx, float By);

//度をラジアンに変換（引数：度）
float DegToRad(float degree);