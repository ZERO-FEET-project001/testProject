#include "LifeControl.h"

/*========================================================

			LifeControl
			コンストラクタ

========================================================*/
LifeControl::LifeControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt,SetSound* ps_Sound){

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

			LifeControl
			初期化関数
			
========================================================*/
void LifeControl::Init(){
	m_Life = 0;
	m_g_pCTaskCtrl->InitLife();
	for(int i = 0 ; i < LIFE_MAX ; i++)
	{
		new Life(m_pt_Texture , m_g_pCTaskCtrl , i );
	}

};
/*========================================================

			LifeControl
			メイン関数
			
========================================================*/
void LifeControl::main(){

	if(m_g_pCTaskCtrl->isGetLife() != m_Life )
	{
		for(int i = m_Life ; i < m_g_pCTaskCtrl->isGetLife() ; i++)
		{
			m_Life = m_g_pCTaskCtrl->isGetLife();
			new Cross(m_pt_Texture , m_g_pCTaskCtrl , i ,m_ps_Sound);
		}
	}

	//if(m_g_pCTaskCtrl->isGetLife() == LIFE_MAX && m_g_pCTaskCtrl->isGetScore() == m_g_pCTaskCtrl->isGetScoreDisplay())
	//{
	//	m_g_pCTaskCtrl->SetGameMode(GAME_OVER);
	//}
	if(m_g_pCTaskCtrl->isGetLife() == LIFE_MAX)
	{
		m_g_pCTaskCtrl->SetGameMode(GAME_OVER);
	}

};
