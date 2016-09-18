#include "GameSystem.h"

/*========================================================

			GameSystem
			コンストラクタ

========================================================*/
GameSystem::GameSystem(DxInput *pDxi,CTaskCtrl*	g_pCTaskCtrl,POINT* Mpt){

	//キーボードポインタの保持
	m_pDxi = pDxi ;
	//タスクコントロールのポインタの保持
	m_g_pCTaskCtrl = g_pCTaskCtrl ;

	//画像の読み込み
	m_pt_Texture = new SetTexture();

	//サウンド
	m_ps_Sound = new SetSound();

	//タスクを生成するかしないかのフラグ
	m_bNewtask_flg = true ;

	//マウスのモードセット
	m_iMousemode = -1;

	//マウスポインタの保持
	m_Mpt = Mpt ;

	//初期起動かの判断
	m_starting_flg = true;

	//キャラクターのカウント
	m_character_count = 0;

	m_iGamemode_Old = GAME_TITLE;
	//スコア管理クラスをNEWする
	m_pScore_Control = new ScoreControl(m_g_pCTaskCtrl , m_pt_Texture );
	//残機管理クラスをNEWする
	m_pLife_Control = new LifeControl(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt,m_ps_Sound);
	//ゲームのポーズ管理クラスをNEWする
	m_pGamePose_Control = new GamePoseControl(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt,m_ps_Sound);
	m_bgm = NULL ;
};
/*========================================================

			GameSystemask
			メイン関数
			ゲームモードによって処理を変えたり
			タスクの実行を行ったりする

========================================================*/
void GameSystem::main(){

	//ゲームモードを保持しておく
	m_iGamemode_Old = m_g_pCTaskCtrl->isGetGameMode();
	//タスクコントロールからゲームモードをもらい
	//どの処理にするかを判断する
	switch(m_g_pCTaskCtrl->isGetGameMode())
	{
		//タイトル
		case GAME_TITLE:
			TitleMain();
			break;
		//メイン処理
		case GAME_MAIN:
			GameMain();
			break;
		//ゲームオーバー
		case GAME_OVER:
			GameOverMain();
			break;	
	}

	// すべてのタスクを実行
	m_g_pCTaskCtrl->main() ;

	//この時にゲームモードが変更されるとタスクの生成のフラグをTRUE
	if(m_iGamemode_Old != m_g_pCTaskCtrl->isGetGameMode())
	{
		m_bNewtask_flg = true ;
		new Darken(m_g_pCTaskCtrl,m_pt_Texture ,m_pDxi);
	}
	
};
/*========================================================

			GameSystemask
			タイトル関数

========================================================*/
void GameSystem::TitleMain(){
	//MouseSystmMain();
	if(m_bNewtask_flg)
	{
		//NEWは一回のみ
		m_bNewtask_flg = false ;
		if(m_starting_flg == false)
		{
			StopSound(BGM_MAIN);
			StopSound(BGM_GAMEOVER);
		}
		PlaySound(BGM_TITLE,TRUE);
		m_g_pCTaskCtrl->SetStartFlg(FALSE);
		new Cursor(m_pt_Texture ,m_g_pCTaskCtrl , m_Mpt, m_pDxi , GAME_TITLE , m_starting_flg,m_ps_Sound);
		new GameTitle(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt , m_starting_flg);
		m_starting_flg = false ;
	}
	m_character_count++;
	if(m_character_count >= 100)
	{
		m_character_count = 0;
		new CharacterTitle(m_pt_Texture , m_g_pCTaskCtrl,m_Mpt,m_pDxi,m_ps_Sound);
	}
};
/*========================================================

			GameSystemask
			ゲームメイン関数

========================================================*/
void GameSystem::GameMain(){
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		MouseSystmMain();
	}
	if(m_bNewtask_flg)
	{ 
		m_character_count = 0;
		//NEWは一回のみ
		m_bNewtask_flg = false ;
		StopSound(BGM_TITLE);
		PlaySound(BGM_MAIN,TRUE);
		//背景のNEW
		new Bg(m_pt_Texture , m_g_pCTaskCtrl);
		//境界線
		new BorderLine( m_g_pCTaskCtrl ,m_pt_Texture,m_ps_Sound);
		//鳥の巣
		new NibuAvis(m_pt_Texture , m_g_pCTaskCtrl,m_ps_Sound);
		//スタート文字
		new StartLetter(m_pt_Texture , m_g_pCTaskCtrl,m_ps_Sound);
		//スコア管理クラスの初期化
		m_pScore_Control->Init();
		//残機管理クラスの初期化
		m_pLife_Control->Init();
	}
	//スコア管理クラスのメイン
	m_pScore_Control->main();
	//残機管理クラスのメイン
	m_pLife_Control->main();
	//ゲームのポーズ管理クラスのメイン
	m_pGamePose_Control->main();
};
/*========================================================

			GameSystemask
			ゲームオーバー関数

========================================================*/
void GameSystem::GameOverMain(){
	
	if(m_bNewtask_flg)
	{
		//NEWは一回のみ
		m_bNewtask_flg = false ;
		StopSound(BGM_MAIN);
		PlaySound(BGM_GAMEOVER,TRUE);
		m_g_pCTaskCtrl->SetStartFlg(FALSE);
		new GameOver(m_g_pCTaskCtrl,m_pt_Texture ,m_pDxi,m_Mpt);
		m_pScore_Control->GameOverScoreDisplay();
	}
};

/*========================================================

			MouseSysytem
			マウスのシステム関数

========================================================*/
void GameSystem::MouseSystmMain(){

	//マウスが初めて押されたら！
	if(	m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT) && m_iMousemode == MOUSE_NO ) 
	{
		//マウスモードの変更
		m_iMousemode = MOUSE_START;

		//クリックされた場所を保持しておく
		m_PushMpt_x = m_Mpt->x;
		m_PushMpt_y = m_Mpt->y;

		//線の始まりをNEWする
		new Line(m_pDxi,m_pt_Texture , m_g_pCTaskCtrl,m_PushMpt_x,m_PushMpt_y);
	}
	//クリックが離れたら
	else if(m_pDxi,m_pDxi->isMouseRelease(DXI_MOUSE_LEFT) && m_iMousemode == MOUSE_START)
	{
		//マウスモードの変更
		m_iMousemode++;
		//クリックが離された時の場所を保持しておく
		m_Mpt_Release_x = m_Mpt->x;
		m_Mpt_Release_y = m_Mpt->y;
		//線のシステムを呼び出す
		LineNewSystem();
		//マウスのモードを初期化
		m_iMousemode = MOUSE_NO;
	}
};
/*========================================================

			LineNewSystem
			線をNEWする関数

========================================================*/
void GameSystem::LineNewSystem(){

	//二点の座標の長さを出す。
	m_Line_Long = (LONG)(sqrt((float)((m_Mpt_Release_x - m_PushMpt_x)*(m_Mpt_Release_x - m_PushMpt_x) + (m_Mpt_Release_y - m_PushMpt_y)*(m_Mpt_Release_y - m_PushMpt_y))));
	//線の数を出す。
	m_Line_count = m_Line_Long  / LINE_WIDTH;

	//線が右上がりか、右下がりか判断する
	if(m_PushMpt_x < m_Mpt_Release_x && m_PushMpt_y > m_Mpt_Release_y || m_PushMpt_x > m_Mpt_Release_x && m_PushMpt_y < m_Mpt_Release_y)
	{
		//右上がりの線
		m_g_pCTaskCtrl->SetLineTurn(true);
	}
	else
	{
		//右下がりの線
		m_g_pCTaskCtrl->SetLineTurn(false);
	}

	//ラジアンを求めるため
	float rx = fabs( (float)(m_Mpt_Release_x - m_PushMpt_x) );
	float ry = fabs( (float)(m_Mpt_Release_y - m_PushMpt_y) );

	//ラジアンを求める
	m_arctan = atan2f( ry , rx );

	//ラジアンからの角度の計算
//	m_degree = m_arctan * M_TRIANGLE / M_PI;
	
	//角度をCTaskに教える
	m_g_pCTaskCtrl->SetLineDegree(m_arctan);
	m_g_pCTaskCtrl->SetLineCount(m_Line_count);

	//線のNEWを行う。
	for(int i=0 ; i < m_Line_count ; i++)
	{
		//比例を使用してNEWを行う
		new Line(m_pDxi,m_pt_Texture , m_g_pCTaskCtrl,(LONG)(m_PushMpt_x + (m_Mpt_Release_x - m_PushMpt_x) / m_Line_count * i),(LONG)(m_PushMpt_y + (m_Mpt_Release_y - m_PushMpt_y) / m_Line_count * i));
	}
};