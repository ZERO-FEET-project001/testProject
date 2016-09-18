#include "TaskFuncs.h"


/*------------------------------------------------------

				ゲームのポーズ

------------------------------------------------------*/
/*======================================================

			ゲームのポーズのコンストラクタ

=======================================================*/
GamePose::GamePose(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "GamePose" ;
	//タスクの優先度
	m_fPriority = 1;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//キーボードポインタ
	m_pDxi = pDxi;
	//マウスのポインタ
	m_Mpt = Mpt;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_pose->TextureSet() );
	SetRect(GAMEPOSE_RECT_LEFT,GAMEPOSE_RECT_TOP,GAMEPOSE_RECT_RIGHT,GAMEPOSE_RECT_BOTTOM);
	//座標の設定
	x = GAMEPOSE_X;
	y = GAMEPOSE_Y;
	z = GAMEPOSE_Z;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha();

};
/*======================================================

			ゲームのポーズのMain

=======================================================*/
void GamePose::main() {

	ModeDelete(m_g_pCTaskCtrl);

	if(m_Mpt->x >= 235 && m_Mpt->x <= 525 && m_Mpt->y >= 245 && m_Mpt->y <= 285)
	{
		if(m_pDxi->isMouse(DXI_MOUSE_LEFT) && m_g_pCTaskCtrl->isGetGamePose())
		{
			m_g_pCTaskCtrl->SetGamePose(FALSE);
			Delete();
		}
	}
	else if(m_Mpt->x >= 220 && m_Mpt->x <= 550 && m_Mpt->y >= 365 && m_Mpt->y <= 400)
	{
		if(m_pDxi->isMouse(DXI_MOUSE_LEFT) && m_g_pCTaskCtrl->isGetGamePose())
		{
			m_g_pCTaskCtrl->SetGameMode(GAME_TITLE);
			m_g_pCTaskCtrl->SetGamePose(FALSE);
			Delete();
		}
	}

};
