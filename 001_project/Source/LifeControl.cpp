#include "LifeControl.h"

/*========================================================

			LifeControl
			�R���X�g���N�^

========================================================*/
LifeControl::LifeControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt,SetSound* ps_Sound){

	//�^�X�N�R���g���[���̃|�C���^�̕ێ�
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	//�摜�̓ǂݍ���
	m_pt_Texture = pt_Texture;
	//�L�[�{�[�h�|�C���^
	m_pDxi = pDxi;
	//�}�E�X�̃|�C���^
	m_Mpt = Mpt;
	//�T�E���h
	m_ps_Sound = ps_Sound;
};
/*========================================================

			LifeControl
			�������֐�
			
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
			���C���֐�
			
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
