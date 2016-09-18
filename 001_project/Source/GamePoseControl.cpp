#include "GamePoseControl.h"

/*========================================================

			GamePoseControl
			コンストラクタ

========================================================*/
GamePoseControl::GamePoseControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt,SetSound* ps_Sound){

	//タスクコントロールのポインタの保持
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	//画像の読み込み
	m_pt_Texture = pt_Texture;
	//キーボードポインタ
	m_pDxi = pDxi;
	//マウスのポインタ
	m_Mpt = Mpt;
	//サウンド
	m_ps_Sound = ps_Sound;
};
/*========================================================

			GamePoseControl
			メイン関数
			
========================================================*/
void GamePoseControl::main(){

	if(m_pDxi->isKeyTrigger(DIK_SPACE) && m_g_pCTaskCtrl->isGetGamePose() == false)
	{
		new Cursor(m_pt_Texture , m_g_pCTaskCtrl , m_Mpt , m_pDxi , GAME_MAIN , TRUE , m_ps_Sound);
		new GamePose(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt);
		m_g_pCTaskCtrl->SetGamePose(true);
	}
};
