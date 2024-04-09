#include"DxLib.h"
#include"input.h"

//現在フレームのキー情報
char Input::currentKeyBuf[KEY_BUF_LEN];
//現在フレームのマウス情報
char Input::currentMouseBuf[MOUSE_BUF_LEN];

//前のフレームのキー情報
char Input::preKeyBuf[KEY_BUF_LEN];
//前のフレームのキー情報
char Input::preMouseBuf[MOUSE_BUF_LEN];

//入力制御初期化
void Input::Init()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}

	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		currentMouseBuf[index] = '\0';
		preMouseBuf[index] = '\0';
	}
}

//入力制御ステップ
//他のStepより早く呼ぶ
void Input::Step()
{
	//前フレームのキー情報変数に記録しておく
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}

	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		preMouseBuf[index] = currentMouseBuf[index];
	}

	//現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		currentMouseBuf[MOUSE_INPUT_LEFT] = 1;
	}
	else
	{
		currentMouseBuf[MOUSE_INPUT_LEFT] = 0;
	}

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		currentMouseBuf[MOUSE_INPUT_RIGHT] = 1;
	}
	else
	{
		currentMouseBuf[MOUSE_INPUT_RIGHT] = 0;
	}
}

/*==========================================================
						キーボード
==========================================================*/

//今押された：KEY_INPUT_～
bool Input::Key::Push(int key_code)
{
	//前フレで押されてない　かつ　現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	//押されてないので false
	return false;
}

//押し続けられている：KEY_INPUT_～
bool Input::Key::Keep(int key_code)
{
	//前フレで押されている　かつ　現フレで押されている
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	//押されてないので false
	return false;
}

//たった今離された：KEY_INPUT_～
bool Input::Key::Release(int key_code)
{
	//前フレで押されている　かつ　現フレで押されていない
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
	{
		return true;
	}

	//押されてるので false
	return false;
}

//=========================================================================================================

//単純に押されているか：KEY_INPUT_～
bool Input::Key::Down(int key_code)
{
	//現フレで押されている（前フレの状態は関係なし）
	if (currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

/*==========================================================
							マウス
==========================================================*/
//今押された：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Push(int key_code)
{
	//前フレで押されてない　かつ　現フレで押されている
	if (preMouseBuf[key_code] == 0 && currentMouseBuf[key_code] == 1)
	{
		return true;
	}

	//押されてないので false
	return false;
}

//押し続けられている：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Keep(int key_code)
{
	//前フレで押されている　かつ　現フレで押されている
	if (preMouseBuf[key_code] == 1 && currentMouseBuf[key_code] == 1)
	{
		return true;
	}

	//押されてないので false
	return false;
}

//たった今離された：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Release(int key_code)
{
	//前フレで押されている　かつ　現フレで押されていない
	if (preMouseBuf[key_code] == 1 && currentMouseBuf[key_code] == 0)
	{
		return true;
	}

	//押されてるので false
	return false;
}
