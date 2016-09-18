#include "TaskFuncs.h"
#include <math.h> 
#include "ScoreControl.h"
#include "LifeControl.h"
#include "GamePoseControl.h"

/*========================================================

				GameSystemMain

========================================================*/

class GameSystem {


	//キーボードポインタの保持
	DxInput* m_pDxi;
	//タスクコントロールのポインタの保持
	CTaskCtrl*	m_g_pCTaskCtrl;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	//画像用ポインタの保持
	SetTexture* m_pt_Texture ;
	//マウスのポインターセット
	POINT* m_Mpt;

	//クリックされた場所を保持しておく
	LONG m_PushMpt_x;
	LONG m_PushMpt_y;
	//クリックが離された時の場所を保持しておく
	LONG m_Mpt_Release_x;
	LONG m_Mpt_Release_y;

	//線の長さ
	LONG m_Line_Long;
	//線の数
	LONG m_Line_count;

	//変数
	//ゲームモードの保持
	INT	m_iGamemode_Old ;

	//タスクを生成するかしないかの判断
	BOOL m_bNewtask_flg ;

	//マウスのモード -1入力なし　0入力はじめ　1動き中　2離した
	INT m_iMousemode;
	//逆正接(アークタンジェント)ラジアン
	FLOAT m_arctan;
	//スコア管理クラス
	ScoreControl* m_pScore_Control;
	//残機管理クラス
	LifeControl* m_pLife_Control;
	//ゲームのポーズ管理クラス
	GamePoseControl* m_pGamePose_Control;
	//初期起動かの判断
	BOOL m_starting_flg;

	//キャラクターのカウント
	INT m_character_count;
	SoundFuncs* m_bgm ;
public:

	//コンストラクタ
	GameSystem(DxInput* pDxi,CTaskCtrl* g_pCTaskCtrl,POINT* Mpt);
	//main関数
	void	main();
	//画面のコントロール関数
	void	PictureCtrl();
	//タイトル関数
	void	TitleMain();
	//ゲームのメイン関数
	void	GameMain();
	//ゲームオーバー
	void	GameOverMain();
	//ゲームクリア
	void	GameClearMain();
	//マウスのシステム
	void	MouseSystmMain();
	//線をNEWする関数
	void	LineNewSystem();
};

