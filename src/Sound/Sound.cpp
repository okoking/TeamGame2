#include"sound.h"
#include"DxLib.h"

int Sound::Bgm::handle[BGM_MAX_NUM];
int Sound::Se::handle[SE_MAX_NUM];

//BGMのパス
char bgmSoundPath[BGM_MAX_NUM][255] =
{
	//音楽
	"data/sound/bgm/titleBGM.mp3",	//タイトル
	"data/sound/bgm/playBGM.mp3",	//プレイ
	"data/sound/bgm/resultBGM.mp3",	//リザルト

	//環境音
	"data/sound/bgm/fish.mp3",		//魚が暴れる
	"data/sound/bgm/fishing.mp3",	//釣り中
	"data/sound/bgm/recovery.mp3",	//ルアー巻き取り
	"data/sound/bgm/sea.mp3",		//海
};

//音量
int soundVolume_bgm[BGM_MAX_NUM] =
{
	70,	//タイトル
	55,	//プレイ
	60,	//リザルト

	90,		//魚が暴れる
	70,		//釣り中
	70,		//ルアー巻き取り
	50,		//海
};

//SEのパス
char seSoundPath[SE_MAX_NUM][255] =
{
	"data/sound/se/system.mp3",		//システム
	"data/sound/se/fishingRod.mp3",	//釣り竿
	"data/sound/se/lure.mp3",		//ルアー着水
	"data/sound/se/hit.mp3",		//魚がルアーに反応
	"data/sound/se/fishGet.mp3",	//魚を釣った
	"data/sound/se/timeLimit.mp3",	//時間制限
	"data/sound/se/finish.mp3",		//ゲーム終了
};

//音量
int soundVolume_se[SE_MAX_NUM] =
{
	80,			//システム
	70,			//釣り竿
	75,			//ルアー着水
	70,			//魚がルアーに反応
	90,			//魚を釣った
	100,			//時間制限
	70,			//ゲーム終了
};

//サウンドまとめ初期化
void Sound::Init()
{
	Bgm::Init();
	Se::Init();
}

//BGMの初期化
void Sound::Bgm::Init()
{
	for (int i = 0; i < BGM_MAX_NUM; i++)
	{
		//読み込み
		handle[i] = LoadSoundMem(bgmSoundPath[i]);
		//ボリュームの設定
		ChangeVolumeSoundMem(255 * soundVolume_bgm[i] / 100, handle[i]);
	}
}
//BGMの通常処理：種類
void Sound::Bgm::Play(int type)
{
	//BGMの再生
	PlaySoundMem(handle[type], DX_PLAYTYPE_LOOP, true);
}
//BGMの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
void Sound::Bgm::SetVolume(int type, int volume)
{
	//音量の設定（0～255）（↓はvolume％の音量で出力）
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}
//BGMの停止：種類
void Sound::Bgm::StopSound(int type)
{
	//BGMの停止
	StopSoundMem(handle[type]);
}

//SEの初期化
void Sound::Se::Init()
{
	for (int i = 0; i < SE_MAX_NUM; i++)
	{
		//読み込み
		handle[i] = LoadSoundMem(seSoundPath[i]);
		//ボリュームの設定
		int vo = soundVolume_se[i];
		SetVolume(i, vo);
	}
}
//SEの通常処理：種類
void Sound::Se::Play(int type)
{
	//効果音の再生
	PlaySoundMem(handle[type], DX_PLAYTYPE_BACK, true);
}
//SEの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
void Sound::Se::SetVolume(int type, int volume)
{
	//音量の設定（0～255）（↓はvolume％の音量で出力）
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}