#pragma once

#define KEY_BUF_LEN		256
#define MOUSE_BUF_LEN	3

class Input
{
private:
	//現在フレームのキー情報
	static char currentKeyBuf[KEY_BUF_LEN];
	//現在フレームのマウス情報
	static char currentMouseBuf[MOUSE_BUF_LEN];


	//前のフレームのキー情報
	static char preKeyBuf[KEY_BUF_LEN];
	//前のフレームのキー情報
	static char preMouseBuf[MOUSE_BUF_LEN];

public:
	//入力制御初期化
	static void Init();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void Step();

	/*==========================================================
							キーボード
	==========================================================*/
	class Key
	{
	public:
		//今押された：KEY_INPUT_～
		static bool Push(int key_code);

		//押し続けられている：KEY_INPUT_～
		static bool Keep(int key_code);

		//たった今離された：KEY_INPUT_～
		static bool Release(int key_code);

		//=======================================

		//単純に押されているか：KEY_INPUT_～
		static bool Down(int key_code);
	};

	/*==========================================================
								マウス
	==========================================================*/
	class Mouse
	{
	public:
		//今押された：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Push(int key_code);

		//押し続けられている：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Keep(int key_code);

		//たった今離された：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Release(int key_code);
	};
};