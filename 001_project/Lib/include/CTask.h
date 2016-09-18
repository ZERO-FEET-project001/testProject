#pragma once
#include "stdafx.h"
#include "DxSprite.h"
#include "DxTexture.h"
#include "Define.h"

//-----------------------------------------------------------------------------
// m_dwTaskFlag
#define	TASK_FLAG_NONE		(0)			// 初期化状態
#define	TASK_FLAG_USE		( 1 <<  0 )	// Taskがヒープエリアを使用中
#define	TASK_FLAG_ENABLE	( 1 <<  1 )	// Taskが初期化を完了
#define	TASK_FLAG_OBJECT	( 1 <<  2 )	// Objectを表示する
#define	TASK_FLAG_CLEAR		( 1 <<  3 )	// TASK消去(自分自身の消去)
#define	TASK_FLAG_COL_ACT	( 1 <<  4 )	// Colにおいて当たり元（弾など）
#define	TASK_FLAG_COL_PSV	( 1 <<  5 )	// Colにおいて当てられる側（自機、敵など）
#define	TASK_FLAG_HIT		( 1 <<  6 )	// Colにおいて当たれれた
#define	TASK_FLAG_NOMOVE	( 1 <<  7 )	// 1フレーム移動しない
#define	TASK_FLAG_TEX		( 1 <<  8 )	// テクスチャーの実態を保有している
//-----------------------------------------------------------------------------

/*--------------------------------------------------------
	タスク制御クラス
--------------------------------------------------------*/
class CTaskCtrl
{
	
	INT		m_iGamemode ;		//現在のゲームモードを保持
	BOOL	m_bNewDownObject ;  //何か落下するフラグ
	FLOAT	m_fLineAlpha ;		//線をアルファ
	BOOL	m_bLineTurn ;		//線の向き　TURE＝右上がり　FALSE＝右下がり
	FLOAT	m_fLineRadian;		//線のラジアン
	INT		m_iLineCount;		//線の数
	INT		m_iScore;			//スコア(データ)
	INT		m_iScoreDisplay;	//スコア(表示用)
	INT		m_iLife;			//残機の保持
	BOOL	m_bGamePose;		//ゲームのポーズフラグ
	FLOAT	m_fBorderLine;		//境界線
	BOOL	m_bStartFlg;		//スタートフラグ

	BYTE	*m_pbTaskHeap ;		// ヒープエリア
	DWORD	m_dwMemSize ;		// ヒープサイズ		
	BOOL	m_bDefrag ;			//

	DWORD	m_dwMSPF ;
	DWORD	m_dwFPS ;
	DWORD	m_dwTime ;
	DWORD	m_dwTimePrev ;
	DWORD	m_dwTimeNow ;
	DWORD	m_dwTimeOver ; 

	DxSprite*	m_pSprite ;

public:
	BYTE	*m_pbTop	;		// 一番最初に実行するタスクの格納ポインタ
	BYTE	*m_pbFree ;			// ヒープエリアの空いている先頭ポインタ
	DWORD	m_dwSize ;			// 使用中のヒープサイズ
	DWORD	m_dwCount ;			// 使用中のタスク数

public:
	CTaskCtrl(DWORD dwMemSize,DWORD dwFPS = 60) ;
	~CTaskCtrl() ;

	void ClearTaskHeap(void) ;
	void main(void) ;
	void Defrag(void) ;

	HRESULT CreateSprite(DxWin* pDxw) ;
	HRESULT DrawAll();

	BOOL isSync() ;
	DWORD isTime() { return (m_dwTime) ; }	
	DWORD isTimeOver() { return (m_dwTimeOver) ; }	

	BYTE * isHeap() { return ( m_pbTaskHeap ) ; }
	DWORD isMemSize() { return ( m_dwMemSize ) ; }
	DWORD isUseSize() { return ( m_dwSize ) ; }
	DWORD isCount() { return ( m_dwCount ) ; }

	//ゲームモードを渡す
	INT isGetGameMode() { return (m_iGamemode); }
	//ゲームモードをセットする
	VOID SetGameMode(INT gamemode);
	
	//新しくオブジェクト落とすフラグを渡す
	BOOL isGetNewDownObject() { return (m_bNewDownObject); }
	//新しくオブジェクト落とすフラグをセットする
	VOID SetNewDownObject(BOOL downflg);

	//線アルファを渡す
	FLOAT isGetLineAlpha() { return (m_fLineAlpha); }
	//線アルファをセットする
	VOID SetLineAlpha(FLOAT linealpha);

	//線の向きを渡す
	BOOL isGetLineTurn() { return (m_bLineTurn); }
	//線の向きをセットする
	VOID SetLineTurn(BOOL turnflg);

	//線のラジアンを渡す
	FLOAT isGetLineRadian() { return (m_fLineRadian); }
	//線のラジアンをセットする
	VOID SetLineDegree(FLOAT radian);

	//スコア（表示用）を数を渡す
	INT isGetScoreDisplay() { return (m_iScoreDisplay); }
	//スコア（表示用）をセットする
	VOID SetScoreDisplay(INT displayscore);

	//スコア(データ)を渡す
	INT isGetScore() { return (m_iScore); }
	//スコア(データ)をセットする
	VOID SetScore(INT score);

	//スコアを初期化する
	VOID InitScore() ;
	VOID InitScoreDisplay();

	//残機を取得
	INT isGetLife(){ return (m_iLife); };
	//残機のせっと（TRUE＝減算、FALSE＝加算）
	VOID SetLife(BOOL life);
	//残機の初期化
	VOID InitLife();

	//ゲームのポーズフラグを渡す
	BOOL isGetGamePose() { return (m_bGamePose); }
	//ゲームのポーズフラグをセットする
	VOID SetGamePose(BOOL poseflg);

	//境界線を渡す
	FLOAT isGetBorderLine() { return (m_fBorderLine); }
	//境界線をセットする
	VOID SetBorderLine(FLOAT borderline);

	//線の数を渡す
	INT isGetLineCount() { return (m_iLineCount); }
	FLOAT isGetLinePoint(INT linecount);
	//線の数をセットする
	VOID SetLineCount(INT linecount);


	//ゲームスタートフラグを渡す
	BOOL isGetStartFlg() { return (m_bStartFlg); }
	//ゲームスタートフラグをセットする
	VOID SetStartFlg(BOOL startflg);

	void  setDefrag() { m_bDefrag = TRUE ; }
	DxWin* isDxWin() { return ( m_pSprite->isDxWin() ) ; } 


};


/*--------------------------------------------------------
	タスク本体クラス
--------------------------------------------------------*/
class CTaskFunc {
	DWORD	m_dwTaskFlag;			// タスク制御用フラグ

public:
	static CTaskCtrl *m_spCTaskCtrl ;

	CTaskFunc*		m_pTaskPrev;	// 前のタスクバッファポインタ
	CTaskFunc*		m_pTaskNext;	// 次のタスクバッファポインタ
	CTaskFunc*		m_pTaskParent;	// 親タスクバッファポインタ
	CTaskFunc*		m_pTaskChild;	// 子タスクバッファポインタ

	FLOAT	m_fPriority ;			// タスクの優先度
	BYTE	m_iGroup ;				// タスクのグループ指定
	DWORD	m_dwSize ;				// タスククラスのサイズ

	// 座標
	FLOAT	x ;
	FLOAT	y ;
	FLOAT	z ;						//0.0f が一番手前、1.0f が一番奥。）

	// 移動量
	FLOAT	dx ;
	FLOAT	dy ;

	RECT	m_rect ;					//RECT

	// 当たりの大きさ
	FLOAT	colx ;
	FLOAT	coly ;

	INT	 m_alpha;

protected:
	char*	m_cpName ;				// タスクの名称

	DWORD  m_color ;				//カラー

	FLOAT	m_rotate ;				// 回転
	D3DXVECTOR2	m_scale ;			// 拡大縮小

	//RECT切り替えようの変数
	INT m_iPtntimer_Max ;//RECT切り替え時間の最大
	INT m_iPtntimer ;//RECTの切り替え時間
	INT m_iPtn ;//現在の画像のパターン番号
	INT m_iPtninit ;
	INT m_iPtn_Right_Max ;
	INT m_iPtn_Max ;//最大の画像のパターン番号
	RECT m_rectSize ;//変更RECT
	FLOAT m_fPtn_x ;//パターンの座標X
	FLOAT m_fPtn_y ;//パターンの座標Y
	BOOL m_bPtnLoopflg ;//
	BOOL m_bPtnRetunflg ;//

	//画面移行の際のNEWのカウント
	FLOAT m_fNew_Count;
	//画面移行の際のDELETEのカウント
	FLOAT m_fDelete_Count;
	//画面移行の際のNEWのフラグ
	BOOL m_bNew_Flg;
	//画面移行の際のDELETEのフラグ
	BOOL m_bDelete_Flg;
	//自分がどの時に出現するか消えるか持っておく
	INT m_iMode;

	DxTexture*	m_pDxT ;			// テクスチャー格納ポインタ

public:
	void* operator new(size_t size, float priority=1.0f, int group = 0 );
	void operator delete(void *pTask, float priority,int group){} ;	// 警告対策
    void operator delete(void *pTask);

	CTaskFunc() ;
	~CTaskFunc() ;
	void Delete() ;
	void DeleteGroup( int group ) ;
	void DeleteAll() ;

	virtual void main() = 0 ;
	void After() ;
	virtual void Hit(CTaskFunc* task) ;
	HRESULT Texture(LPCTSTR lpszFilename) { return ( Texture(lpszFilename, TRUE) ) ; }
	HRESULT Texture(LPCTSTR lpszFilename, BOOL bMode) ;
	void Draw( DxSprite* pSprite ) ;

	void SetPriority(float priority) ;
	void Link( CTaskFunc* pTaskParent, CTaskFunc* pTaskChild ) ;
	void LinkOff() ;
	void DeleteOwnChild() ;
	void DeleteOwnParent() ;
	void HitOwnChild() ;
	void HitOwnParent() ;

	BOOL isUse() ;
	void setTaskFlag( DWORD flag ) ; 
	void resetTaskFlag( DWORD flag ) ;
	BOOL isTaskFlag( DWORD flag ) ;
	DxTexture* TextureSet( );
	void GetTexture( DxTexture* g_tex );
	void SetRect(long left, long top, long right, long bottom);
	void SetAlpha();
	void SetAlpha(int a);
	void PtnChange();
	//ゲームモードで自分が出現するかを判断する関数
	void	ModeNew(CTaskCtrl* g_pCTaskCtrl ,BOOL dispflg);
	//ゲームモードで自分が消えるか消えないかを判断する関数
	void	ModeDelete(CTaskCtrl* g_pCTaskCtrl );
};

