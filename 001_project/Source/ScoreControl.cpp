#include "ScoreControl.h"

/*========================================================

			ScoreControl
			コンストラクタ

========================================================*/
ScoreControl::ScoreControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture){

	//タスクコントロールのポインタの保持
	m_g_pCTaskCtrl = g_pCTaskCtrl ;

	//画像の読み込み
	m_pt_Texture = pt_Texture;

};
/*========================================================

			ScoreControl
			初期化関数
			
========================================================*/
void ScoreControl::Init(){

	m_g_pCTaskCtrl->InitScore();
	m_g_pCTaskCtrl->InitScoreDisplay();

	m_Score = m_g_pCTaskCtrl->isGetScore();
	m_ScoreDisplay = m_g_pCTaskCtrl->isGetScoreDisplay();

	
	for(int i = 0 ; i < COUNTER_MAX ; i++)
	{
		new ScoreNumber(m_pt_Texture , i , m_g_pCTaskCtrl );
	}
};
/*========================================================

			ScoreControl
			メイン関数
			
========================================================*/
void ScoreControl::main(){

	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		if(m_g_pCTaskCtrl->isGetScore() >= 0)
		{
			if(m_g_pCTaskCtrl->isGetScore() > m_g_pCTaskCtrl->isGetScoreDisplay())
			{
				m_g_pCTaskCtrl->SetScoreDisplay(5);
			}
			else if(m_g_pCTaskCtrl->isGetScore() < m_g_pCTaskCtrl->isGetScoreDisplay())
			{
				m_g_pCTaskCtrl->SetScoreDisplay(-5);
			}
		}
	}
	if(m_g_pCTaskCtrl->isGetScore() < 0)
	{
		m_g_pCTaskCtrl->InitScore();
	}

};
/*========================================================

			GameOver時の表示関数
			
========================================================*/
void ScoreControl::GameOverScoreDisplay(){

	for(int i = 0 ; i < COUNTER_MAX ; i++)
	{
		new GameScore(m_pt_Texture , i , m_g_pCTaskCtrl );
	}

};