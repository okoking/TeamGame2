#pragma once

//設定フレームレート（60FPS）
#define FRAME_RATE	(60)

//1フレームの時間（ミリ秒）
#define FRAME_TIME	(1000/FRAME_RATE)

//強引FPS関数
bool FPS();

//FPS計算
void CalcFPS();

//FPS表示（デバック用）
void DrawFPS();