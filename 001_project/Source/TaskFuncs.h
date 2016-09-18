#pragma once
#include "CTask.h"
#include "DxInput.h"
#include "Define.h"	
#include "DxSound.h"
#include <math.h>

/*========================================================

				サウンド

========================================================*/
class SoundFuncs : public CTaskFunc {
	DxSound* m_pSound;
	BOOL m_stop_flg;
	BOOL m_loop_flg;
public:
	SoundFuncs(DxSound*);
	void main();
	void Play(bool loop);
	void Stop();
	void EnableDeleteByEnd();
	void ChangeSound(DxSound*);
};

class SetSound {

public:
	//BGM
	DxSound* m_title_bgm ;//タイトルBGM
	DxSound* m_main_bgm ;//ゲームメインBGM
	DxSound* m_gameover_bgm;//ゲームオーバーBGM
	//SE
	DxSound* m_kotori_se ;//小鳥SE
	DxSound* m_corsor_se ;//カーソルSE
	DxSound* m_corsor_ok_se ;//カーソル決定音SE
	DxSound* m_egg_se ;//卵SE
	DxSound* m_eggbreak_se ;//卵割れるSE
	DxSound* m_start_se ;//スタートSE
	DxSound* m_in_se ;//入った時のSE
	DxSound* m_kotorihit_se ;//小鳥が跳ね返るのSE
	DxSound* m_batu_se ;//小鳥が落ちた時のSE
	DxSound* m_swing_se ;//鳥の巣が揺れるSE

	SetSound();
	void main();
};


/*========================================================

				TextureTask

========================================================*/
class TextureFuncs : public CTaskFunc {

public:
	//コンストラクタ
	TextureFuncs(LPCTSTR filename);
	//main関数
	void	main();

};

class SetTexture{

public:
	//背景
	TextureFuncs* m_pg_bg ;
	//線
	TextureFuncs* m_pg_line ;
	//鳥の巣
	TextureFuncs* m_pg_nibu ;
	//鳥の卵
	TextureFuncs* m_pg_egg ;
	//卵の殻
	TextureFuncs* m_pg_eggshell ;
	//小鳥
	TextureFuncs* m_pg_smallbird ;
	//入った時のポイント
	TextureFuncs* m_pg_point;
	//数字
	TextureFuncs* m_pg_scorenumber;
	//残機
	TextureFuncs* m_pg_life;
	//バツ
	TextureFuncs* m_pg_cross;
	//ポーズ
	TextureFuncs* m_pg_pose;
	//カーソル
	TextureFuncs* m_pg_cursor;
	//タイトル
	TextureFuncs* m_pg_title;
	//黒
	TextureFuncs* m_pg_black;
	//境界線
	TextureFuncs* m_pg_border;
	//ゲームオーバー
	TextureFuncs* m_pg_gameover;
	//文字
	TextureFuncs* m_pg_char;
	TextureFuncs* m_pg_start;

	//コンストラクタ
	SetTexture();
	//main関数
	void	main();

};

/*========================================================

				背景

========================================================*/
class Bg : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
public:
	//コンストラクタ
	Bg(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl );
	//main関数
	void	main();

};
/*========================================================

				線

========================================================*/
class Line : public CTaskFunc {

	//ポインタ保持
	//キーボードポインタの保持
	DxInput* m_pDxi;
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;

	//変数
	BOOL m_hit_egg;	//卵と当たった！
	//次の線のポインタ
	Line* m_pLineNext;
	//前のポインタ
	Line* m_pLinePrev;


public:
	//コンストラクタ
	Line(DxInput* pDxi,SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,LONG Mpt_x,LONG Mpt_y);
	//main関数
	void	main();
	//Key操作
	void	Key();
	//あたり判定
	void	Hit(CTaskFunc* task);
	//ポインター保持関数
	void	Chain(Line* pLineNext ,Line* pLinePrev);
	//
	void	EggHit(CTaskFunc* egg);

};
/*========================================================

				鳥の巣

========================================================*/
class NibuAvis : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	//揺らすか揺らさないか
	BOOL m_swing_flg ;
	//揺れてる時のカウントをする
	INT m_swing_count;
	//揺れをスタートさせるカウント
	INT m_swing_start_count;
	//右か左か
	BOOL m_swing_left_right_flg ;
	//移動量を保持しておく
	FLOAT m_tmp_dx;


public:
	//コンストラクタ
	NibuAvis(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound);
	//main関数
	void	main();
	//揺れ関数
	void	Swing();
	//動き
	void	Move();
	//当たり関数
	void	Hit(CTaskFunc* task);

};

/*========================================================

				鳥の卵

========================================================*/
class Egg : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	//変数
	BOOL m_hit_line;//線にあたったフラグ
	BOOL m_hit_nibus;//鳥の巣にあたっていいよ！
	INT m_life;//卵のライフ
	INT m_smallbird_count;//卵が孵化をするカウント
	
	INT m_linecount;
public:
	//コンストラクタ
	Egg(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y,SetSound* ps_Sound);
	//main関数
	void	main();
	//動き
	void	Move();
	//跳ね返り
	void	Spring();
	//あたり判定
	void	Hit(CTaskFunc* task);
	//線と当たった時
	void	LineHit(CTaskFunc* line);
	//鳥の巣との当たり判定
	void	NibusHit(CTaskFunc* nibus);
	//卵の亀裂
	void	EggSplit();


};
/*========================================================

				鳥の殻

========================================================*/
class EggShell : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	
	//変数
	BOOL m_hit_line;//線にあたったフラグ

public:
	//コンストラクタ
	EggShell(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,float egg_x,float egg_y, int gamemode);
	//main関数
	void	main();
	//動き
	void	Move();
	//跳ね返り
	void	Spring();



};
/*========================================================

				小鳥

========================================================*/
class SmallBird : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	//変数
	BOOL m_hit_line;//線にあたったフラグ
	BOOL m_hit_nibus;//鳥の巣にあたっていいよ！
	BOOL m_fly_flg;//飛ぶフラグ
	INT  m_fly_start_count;//飛ぶスタートカウント
	INT  m_fly_end_count;//飛ぶ終わりカウント
	
	INT m_linecount;
public:
	//コンストラクタ
	SmallBird(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y,SetSound* ps_Sound);
	//main関数
	void	main();
	//動き
	void	Move();
	//跳ね返り
	void	Spring();
	//あたり判定
	void	Hit(CTaskFunc* task);
	//線と当たった時
	void	LineHit(CTaskFunc* line);
	//鳥の巣との当たり判定
	void	NibusHit(CTaskFunc* nibus);
	//飛ぶ
	void	Fly();
	//向き
	void	Turn();


};
/*========================================================

				鳥の巣入った時のポイント

========================================================*/
class InPoint : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	
public:
	//コンストラクタ
	InPoint(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y, int line_count);
	//main関数
	void	main();
	void	Move();
};
/*========================================================

				スコア

========================================================*/
class ScoreNumber : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	int m_kurai;//位
	int m_place;//値


public:
	//コンストラクタ;
	ScoreNumber(SetTexture* pt_Texture , int kurai , CTaskCtrl* g_pCTaskCtrl) ;
	//main関数
	void	main() ;
	//RECTの変更
	void	ChangeRect();
};
/*========================================================

				スコア

========================================================*/
class ScoreLetter : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;

	int m_kind ;
	bool m_move_flg;
	int m_move_count;


public:
	//コンストラクタ;
	ScoreLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl , int kind) ;
	//main関数
	void	main() ;
	//RECTの変更
	void	ChangeRect();
	//動き
	void	Move();
};
/*========================================================

				残機

========================================================*/
class Life : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	
public:
	//コンストラクタ
	Life(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,int kind);
	//main関数
	void	main();

};
/*========================================================

				バツ

========================================================*/
class Cross : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;

public:
	//コンストラクタ
	Cross(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,int kind,SetSound* ps_Sound);
	//main関数
	void	main();
};
/*========================================================

				ゲームのポーズ

========================================================*/
class GamePose: public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//キーボードポインタの保持
	DxInput* m_pDxi;
	//マウスのポインターセット
	POINT* m_Mpt;


public:
	//コンストラクタ
	GamePose(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt);
	//main関数
	void	main();
};
/*========================================================

				選択時のカーソル

========================================================*/
class Cursor : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//マウスのポインターセット
	POINT* m_Mpt;
	DxInput* m_pDxi;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	INT m_kind;
	BOOL m_starting_flg;

public:
	//コンストラクタ
	Cursor(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl ,POINT* Mpt , DxInput* pDxi , int kind, BOOL starting_flg,SetSound* ps_Sound);
	//main関数
	void	main();
	//アニメーション関数
	void	Animation();
	//マウスの座標でカーソルの場所を変更する関数
	void	PointChange();
};
/*========================================================

				ゲームのタイトル

========================================================*/
class GameTitle: public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//キーボードポインタの保持
	DxInput* m_pDxi;
	//マウスのポインターセット
	POINT* m_Mpt;

	//変数
	BOOL m_starting_flg;

public:
	//コンストラクタ
	GameTitle(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt , BOOL starting_flg );
	//main関数
	void	main();
	//ゲームモードを変更する関数
	void	ModeChange();

};
/*========================================================

				暗転

========================================================*/
class Darken: public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//キーボードポインタの保持
	DxInput* m_pDxi;
	//マウスのポインターセット
	POINT* m_Mpt;

	//変数
	BOOL m_alpha_flg;
	INT m_alpha_count;
public:
	//コンストラクタ
	Darken(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi);
	//main関数
	void	main();
};
/*========================================================

				ゲームオーバー

========================================================*/
class GameOver: public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//キーボードポインタの保持
	DxInput* m_pDxi;
	//マウスのポインターセット
	POINT* m_Mpt;
public:
	//コンストラクタ
	GameOver(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt);
	//main関数
	void	main();
	//ゲームモードを変更する関数
	void	ModeChange();

};
/*========================================================

				境界線

========================================================*/
class BorderLine: public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	//変数
	FLOAT m_move_y;//ｙ座標の変更
	BOOL  m_move_flg;
	INT m_move_count;



public:
	//コンストラクタ
	BorderLine(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture,SetSound* ps_Sound);
	//main関数
	void	main();
	//動き
	void	Move();

};
/*========================================================

				GameOverの時のスコア

========================================================*/
class GameScore : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	int m_kurai;//位
	int m_place;//値


public:
	//コンストラクタ;
	GameScore(SetTexture* pt_Texture , int kurai , CTaskCtrl* g_pCTaskCtrl) ;
	//main関数
	void	main() ;
	//RECTの変更
	void	ChangeRect();
};
/*========================================================

				スコア

========================================================*/
class CharLetter : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	int m_kind ;
	bool m_move_flg;
	int m_move_count;


public:
	//コンストラクタ;
	CharLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound) ;
	//main関数
	void	main() ;
	//動き
	void	Move();
};
/*========================================================

				小鳥

========================================================*/
class CharacterTitle : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;

	POINT* m_Mpt;
	DxInput* m_pDxi;
	INT m_kind;
public:
	//コンストラクタ
	CharacterTitle(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,POINT* Mpt,DxInput *pDxi,SetSound* ps_Sound);
	//main関数
	void	main();
	//動き
	void	Move();
	//マウスでクリックすると
	void	MouseHitBird();
	void	MouseHitEgg();

};
/*========================================================

				スタートの文字

========================================================*/
class StartLetter : public CTaskFunc {

	//ポインタ保持
	//タスクコントロールのポインタ
	CTaskCtrl* m_g_pCTaskCtrl ;
	//画像のポインタ
	SetTexture* m_pt_Texture ;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	int m_kind ;
	bool m_move_flg;
	int m_move_count;
	int m_start_count;


public:
	//コンストラクタ;
	StartLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound) ;
	//main関数
	void	main() ;
	//動き
	void	Move();
	void	StartMove();
};