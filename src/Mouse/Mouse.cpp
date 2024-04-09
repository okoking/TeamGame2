#include"DxLib.h"
#include"mouse.h"
#include"../Collision/Collision.h"
#include"../MathPlus/MathPlus.h"
#include"../input/input.h"

int zX, zY;

//画像パス
char path[255][50] = {
	"",
};

//初期化
void Mouse::Init(int pathNum)
{
	Load(pathNum);
	size = 1.0f;
	angle = 0.0f;
	// マウスの位置をセット
	//SetMousePoint(1000, 500);
}

//画像読み込み
void Mouse::Load(int pathNum)
{
	handle = LoadGraph(path[pathNum]);
}


//マウスの動き
void Mouse::Move()
{
	zX = x;
	zY = y;
	// マウスの位置を取得
	GetMousePoint(&zX, &zY);

	x = zX;
	y = zY;
}

//通常処理
void Mouse::Step()
{
	//動き
	Move();

	//左クリック反応（クリック音とか）
	if (Input::Mouse::Push(MOUSE_INPUT_LEFT))
	{
	}
}

//描画
void Mouse::Draw(int type)
{
	//通常描画
	if (type == 0)
	{
		DrawRotaGraph(x, y, 1.0f, 0.0f, handle, true);
	}

	//大きさと回転付き描画
	else if (type == 1)
	{
		DrawRotaGraph(x, y, size, angle, handle, true);
	}

	//透過なし描画
	else if (type == 2)
	{
		DrawRotaGraph(x, y, 1.0f, 0.0f, handle, false);
	}
}

//終了処理
void Mouse::FIn()
{
	//画像を削除
	DeleteGraph(handle);

	handle = -1;
}

//マウス当たり判定（円形）
bool Mouse::MouseColli(int Ra, int Rx, int Ry)
{
	if (Collision::Circlr(Ra, 10, Rx, Ry, x, y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//マウス当たり判定（四角）
bool Mouse::MouseColli(int Ax, int Ay, int Aw, int Ah)
{
	if (Collision::Rect(Ax, Ay, Aw, Ah, x-10, y-10, 10, 10))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//使用中セット：！でfalse
void Mouse::SetUse(char set)
{
	if (set == '!')
	{
		isUse = false;
	}
	else
	{
		isUse = true;
	}
}
