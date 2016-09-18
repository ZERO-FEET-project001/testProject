#include "TaskFuncs.h"


/*------------------------------------------------------

				タイトル

------------------------------------------------------*/
/*======================================================

			タイトルのコンストラクタ

=======================================================*/
GameTitle::GameTitle(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt, BOOL starting_flg) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "GameTitle" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//キーボードポインタ
	m_pDxi = pDxi;
	//マウスのポインタ
	m_Mpt = Mpt;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_title->TextureSet() );
	//レクトの設定
	SetRect(GAMETITLE_RECT_LEFT,GAMETITLE_RECT_TOP,GAMETITLE_RECT_RIGHT,GAMETITLE_RECT_BOTTOM);
	//座標の設定
	x = GAMETITLE_X;
	y = GAMETITLE_Y;
	z = GAMETITLE_Z;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_TITLE;
	m_starting_flg = starting_flg ;
	//アルファ値の指定引数なしで255をセット
	if(m_starting_flg)
	{
		SetAlpha();
	}
};
/*======================================================

			タイトルのMain

=======================================================*/
void GameTitle::main() {
	if(!m_starting_flg)
	{
		ModeNew(m_g_pCTaskCtrl,TRUE);
	}
	ModeChange();
	ModeDelete(m_g_pCTaskCtrl);
};
/*======================================================

			ゲームモードを変更する関数

=======================================================*/
void GameTitle::ModeChange() {

	if(m_Mpt->x >= 280 && m_Mpt->x <= 490 && m_Mpt->y >= 320 && m_Mpt->y <= 365)
	{
		if(m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
		{
			m_g_pCTaskCtrl->SetStartFlg(FALSE);
			m_g_pCTaskCtrl->SetGameMode(GAME_MAIN);
		}
	}
	else if(m_Mpt->x >= 280 && m_Mpt->x <= 490 && m_Mpt->y >= 390 && m_Mpt->y <= 440)
	{
		if(m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
		{
			g_bLoop = 0;
			PostQuitMessage(0);
		}

	}	
};
