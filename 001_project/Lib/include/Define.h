#pragma once

//ゲームモードの種類
typedef enum GAME{
	GAME_TITLE,//タイトル
	GAME_MANUAL,//説明文Manual
	GAME_MAIN,//ゲームメイン
	GAME_OVER,//ゲームオーバー
	GAME_CLEAR,//clear
}GAME;

//マウスの入力の種類
typedef enum Mouse{
	MOUSE_NO = -1 ,//何もしてない
	MOUSE_START,//始まり
	MOUSE_MOVE,//動いてるとき
	MOUSE_STOP,//終わり
}Mouse;

//スコアナンバー
typedef enum SCORE{
	SCORE0,//初期値
	SCORE1,//１
	SCORE2,//２
	SCORE3,//３
	SCORE4,//４
	SCORE5,//５

}SCORE;
//スコア文字
typedef enum SCORELETTER{
	SCORELETTER0,//+100
	SCORELETTER1,//+500
	SCORELETTER2,//-200
	SCORELETTER3,//-500
}SCORELETTER;

//スコアポイント
typedef enum SCOREPOINT{
	SCOREPOINT0 = 100,//+100
	SCOREPOINT1 = 500,//+500
	SCOREPOINT2 = -200,//-200
	SCOREPOINT3 = -600,//-600
}SCOREPOINT;

//BGM
typedef enum BGM{
	BGM_TITLE,
	BGM_MAIN,
	BGM_GAMEOVER,
}BGM;

//サウンド
//ループしない
#define SOUND_NOT_LOOP 0
//ループする
#define SOUND_LOOP 1

//画面のサイズ
#define WID_MAX 800
#define HI_MAX 600

//アルファ値
#define ALPHA_MAX 255

//
#define FAILE_NAME_MAX 256

//NEWカウントMAX
#define NEW_COUNT_MAX 255
#define NEW_COUNT_PLUS 10.0f

//消すカウントMAX
#define DELETE_COUNT_MAX 255
#define DELETE_COUNT_PLUS 10.0f

//重力
#define GRAVITY 0.15f
//反発係数
#define E 0.8f
#define E_DX dx*1.5f

//背景
#define BG_X 400.0f
#define BG_Y 300.0f
#define BG_Z 1.0f
#define BG_RECT_LEFT 0
#define BG_RECT_TOP 0
#define BG_RECT_RIGHT 800
#define BG_RECT_BOTTOM 600

//鳥の巣
#define NIBUAVIS_X 400.0f
#define NIBUAVIS_Y 150.0f
#define NIBUAVIS_Z 0.1f
#define NIBUAVIS_RECT_LEFT 0
#define NIBUAVIS_RECT_TOP 0
#define NIBUAVIS_RECT_RIGHT 125
#define NIBUAVIS_RECT_BOTTOM 80
#define NIBUAVIS_COLX 55.0f
#define NIBUAVIS_COLY 25.0f
#define NIBUAVIS_SWING_COUNT_RAND (float)((rand() % 100) + 150)
#define NIBUAVIS_SWING_COUNT_MAX 100
#define NIBUAVIS_SWING 5.0f
#define NIBUAVIS_SWING_X_MAX x + 5.0f
#define NIBUAVIS_SWING_X_MIN x - 5.0f

//鳥の卵
#define EGG_X 400.0f
#define EGG_Y 150.0f
#define EGG_Z 0.05f
#define EGG_BORDER_Z 0.15f
#define EGG_RECT_LEFT 0
#define EGG_RECT_TOP 0
#define EGG_RECT_RIGHT 32
#define EGG_RECT_BOTTOM 32
#define EGG_COLX 12.0f
#define EGG_COLY 12.0f
#define EGG_DX (float)((rand() % 5))
#define EGG_DY -(float)((rand() % 5)+2)
#define EGG_RORATE dx/50
#define EGG_LEFT_MAX 50
#define EGG_RIGHT_MAX 750
#define EGG_LIFE_MAX 3
#define EGG_HI_MAX 180

//鳥の卵殻
#define EGGSHELL_Z 0.05f
#define EGGSHELL_RECT_LEFT 0
#define EGGSHELL_RECT_TOP 0
#define EGGSHELL_RECT_RIGHT 4
#define EGGSHELL_RECT_BOTTOM 4
#define EGGSHELL_COLX 2.0f
#define EGGSHELL_COLY 2.0f
#define EGGSHELL_DX (float)((rand() % 5))
#define EGGSHELL_DY -(float)((rand() % 5)+2)
#define EGGSHELL_RORATE dx/50
#define EGGSHELL_LEFT_MAX 50
#define EGGSHELL_RIGHT_MAX 750
#define EGGSHELL_MAX 20

//小鳥
#define SMALLBIRD_X 400.0f
#define SMALLBIRD_Y 150.0f
#define SMALLBIRD_Z 0.05f
#define SMALLBIRD_BORDER_Z 0.15f
#define SMALLBIRD_RECT_LEFT_L 0
#define SMALLBIRD_RECT_TOP_L 0
#define SMALLBIRD_RECT_RIGHT_L 32
#define SMALLBIRD_RECT_BOTTOM_L 32
#define SMALLBIRD_RECT_LEFT_R 0
#define SMALLBIRD_RECT_TOP_R 32
#define SMALLBIRD_RECT_RIGHT_R 32
#define SMALLBIRD_RECT_BOTTOM_R 64
#define SMALLBIRD_COLX 12.0f
#define SMALLBIRD_COLY 12.0f
#define SMALLBIRD_DX (float)((rand() % 5))
#define SMALLBIRD_DY -(float)((rand() % 5)+2)
#define SMALLBIRD_RORATE dx/50
#define SMALLBIRD_LEFT_MAX 50
#define SMALLBIRD_RIGHT_MAX 750
#define SMALLBIRD_LIFE_MAX 3
#define SMALLBIRD_HI_MAX 20
#define SMALLBIRD_GRAVITY 0.1f
#define SMALLBIRD_FLY_COUNT_MAX 100
//線の幅
#define LINE_WIDTH 5
#define LINE_RECT_LEFT 0
#define LINE_RECT_TOP 0
#define LINE_RECT_RIGHT 62
#define LINE_RECT_BOTTOM 62
#define LINE_COLX 12.0f
#define LINE_COLY 12.0f
#define LINE_LEFT_MAX 50
#define LINE_RIGHT_MAX 750


//スコアカウンター
#define COUNTER_MAX 7//7桁
#define COUNTER_X 720//X座標
#define COUNTER_Y 30//Y座標
#define COUNTER_Z 0.1f
#define COUNTER_GAP_X 30//横幅
#define COUNTER_PLACE 10//計算


//スコアの＋－の文字
#define SCORELETTER_X 700//X座標
#define SCORELETTER_Y 125//Y座標
#define SCORELETTER_Z 0.15f
#define SCORELETTER_SOEED -1.0f
#define SCORELETTER_APLHA 5
#define SCORELETTER_Y_MAX 75
#define SCORELETTER_COUNT_MAX 100

//残機
#define LIFE_MAX 3
#define LIFE_X 28.0f
#define LIFE_Y (28.0f + (32 * kind))
#define LIFE_Z 0.07f
#define LIFE_RECT_LEFT 0
#define LIFE_RECT_TOP 0
#define LIFE_RECT_RIGHT 32
#define LIFE_RECT_BOTTOM 32
//バツ
#define CROSS_MAX 3
#define CROSS_X 28.0f
#define CROSS_Y (92.0f - (32 * kind))
#define CROSS_Z 0.06f
#define CROSS_RECT_LEFT 0
#define CROSS_RECT_TOP 0
#define CROSS_RECT_RIGHT 32
#define CROSS_RECT_BOTTOM 32

//ゲームのポーズ
#define GAMEPOSE_X 400.0f
#define GAMEPOSE_Y 300.0f
#define GAMEPOSE_Z 0.05f
#define GAMEPOSE_RECT_LEFT 0
#define GAMEPOSE_RECT_TOP 0
#define GAMEPOSE_RECT_RIGHT 800
#define GAMEPOSE_RECT_BOTTOM 600

//ゲームのタイトル
#define GAMETITLE_X 400.0f
#define GAMETITLE_Y 300.0f
#define GAMETITLE_Z 1.0f
#define GAMETITLE_RECT_LEFT 0
#define GAMETITLE_RECT_TOP 0
#define GAMETITLE_RECT_RIGHT 800
#define GAMETITLE_RECT_BOTTOM 600


//暗転
#define DARKEN_X 400.0f
#define DARKEN_Y 300.0f
#define DARKEN_Z 0.0f
#define DARKEN_RECT_LEFT 0
#define DARKEN_RECT_TOP 0
#define DARKEN_RECT_RIGHT 800
#define DARKEN_RECT_BOTTOM 600

//境界線
#define BORDERLINE_X 400.0f
#define BORDERLINE_Y 200.0f
#define BORDERLINE_Z 0.9f
#define BORDERLINE_RECT_LEFT 0
#define BORDERLINE_RECT_TOP 0
#define BORDERLINE_RECT_RIGHT 800
#define BORDERLINE_RECT_BOTTOM 32
#define BORDERLINE_MOVE_Y 20
#define	BORDERSCORE 1500//境界線が動くスコア

//ゲームオーバー
#define GAMEOVER_X 400.0f
#define GAMEOVER_Y 300.0f
#define GAMEOVER_Z 1.0f
#define GAMEOVER_RECT_LEFT 0
#define GAMEOVER_RECT_TOP 0
#define GAMEOVER_RECT_RIGHT 800
#define GAMEOVER_RECT_BOTTOM 600

//GameOverの時のスコア
#define GAMEOVER_SCORE_MAX 7//7桁
#define GAMEOVER_SCORE_X 650//X座標
#define GAMEOVER_SCORE_Y 320//Y座標
#define GAMEOVER_SCORE_Z 0.1f
#define GAMEOVER_SCORE_GAP_X 50//横幅
#define GAMEOVER_SCORE_PLACE 10//計算

//文字
#define CHARLETTER_X 400//X座標
#define CHARLETTER_Y 250//Y座標
#define CHARLETTER_Z 0.1f
#define CHARLETTER_SOEED -2.0f
#define CHARLETTER_APLHA 5
#define CHARLETTER_Y_MAX 250
#define CHARLETTER_COUNT_MAX 100

//タイトルのキャラクター
#define CHARACTERTITLE_X 50.0f
#define CHARACTERTITLE_Y 550.0f
#define CHARACTERTITLE_Z 0.05f
#define CHARACTERTITLE_DX 2.0f
#define CHARACTERTITLE_LEFT_MAX 50
#define CHARACTERTITLE_RIGHT_MAX 750
#define CHARACTERTITLE_RAND rand() % 10
#define CHARACTERTITLE_ROTATE 0.25f

//スタート文字
#define STARTLETTER_X 400//X座標
#define STARTLETTER_Y 250//Y座標
#define STARTLETTER_Z 0.1f
#define STARTLETTER_SOEED -2.0f
#define STARTLETTER_APLHA 5
#define STARTLETTER_Y_MAX 250
#define STARTLETTER_COUNT_MAX 100

//各グループ(グループ数 0～255)
#define GROUP_LINE 0//線
#define GROUP_EGG 1//卵
#define GROUP_NIBUAVIS 2//鳥の巣
#define GROUP_SMALLBIRD 3//小鳥


//extern
extern BOOL g_bLoop ;//ループするかの変数
extern int SetReadFile(unsigned char *work,char *filename);//ファイル読み込み
extern void SetReadDate(int *work,unsigned char *datework,int count);
extern HRESULT InitDirectSound(HWND hWnd);
extern void ReleaseSound(void);
extern BOOL LoadSoundData(LPCWSTR file_name,BYTE buffer_num);
extern void PlaySound(BYTE play_num,bool LOOPFLG);
extern void StopSound(BYTE play_num);