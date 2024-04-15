#pragma once
#include"../Sound/Sound.h"

// define
#define	SCREEN_SIZE_X	800	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	600	// Y方向の画面サイズを指定

enum SCENE_ID
{
	//タイトル関連
	SCENE_ID_INIT_TITLE = 100,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//プレイ関連
	SCENE_ID_INIT_PLAY = 200,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//ゲームクリア関連
	SCENE_ID_INIT_RESULT = 300,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,

};

enum GAME_MODE
{
	GAME_MODE_EASY=0,	// ノーマル
	GAME_MODE_NORMAL,
	GAME_MODE_HARD,

	GAME_MODE_NUM,
};
extern int Score;

extern SCENE_ID g_CurrentSceneID;
extern GAME_MODE g_GameModeID;
