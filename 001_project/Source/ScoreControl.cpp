#include "ScoreControl.h"

/*========================================================

			ScoreControl
			�R���X�g���N�^

========================================================*/
ScoreControl::ScoreControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture){

	//�^�X�N�R���g���[���̃|�C���^�̕ێ�
	m_g_pCTaskCtrl = g_pCTaskCtrl ;

	//�摜�̓ǂݍ���
	m_pt_Texture = pt_Texture;

};
/*========================================================

			ScoreControl
			�������֐�
			
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
			���C���֐�
			
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

			GameOver���̕\���֐�
			
========================================================*/
void ScoreControl::GameOverScoreDisplay(){

	for(int i = 0 ; i < COUNTER_MAX ; i++)
	{
		new GameScore(m_pt_Texture , i , m_g_pCTaskCtrl );
	}

};