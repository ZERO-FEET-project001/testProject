#include "TaskFuncs.h"


/*------------------------------------------------------

				ゲームオーバー

------------------------------------------------------*/
/*======================================================

			ゲームオーバーのコンストラクタ

=======================================================*/
GameOver::GameOver(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "GAMEOVER" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//キーボードポインタ
	m_pDxi = pDxi;
	//マウスのポインタ
	m_Mpt = Mpt;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_gameover->TextureSet() );
	//レクトの設定
	SetRect(GAMEOVER_RECT_LEFT,GAMEOVER_RECT_TOP,GAMEOVER_RECT_RIGHT,GAMEOVER_RECT_BOTTOM);
	//座標の設定
	x = GAMEOVER_X;
	y = GAMEOVER_Y;
	z = GAMEOVER_Z;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_OVER;

	//アルファ値の指定引数なしで255をセット

	SetAlpha(0);
};
/*======================================================

			ゲームオーバーのMain

=======================================================*/
void GameOver::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeChange();
	ModeDelete(m_g_pCTaskCtrl);
};
/*======================================================

			ゲームモードを変更する関数

=======================================================*/
void GameOver::ModeChange() {

	if(m_Mpt->x >= 200 && m_Mpt->x <= 715 && m_Mpt->y >= 440 && m_Mpt->y <= 500)
	{
		if(m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
		{
			m_g_pCTaskCtrl->SetGameMode(GAME_TITLE);
		}
	}

};
