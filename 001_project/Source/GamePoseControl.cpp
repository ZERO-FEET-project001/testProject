#include "GamePoseControl.h"

/*========================================================

			GamePoseControl
			�R���X�g���N�^

========================================================*/
GamePoseControl::GamePoseControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt,SetSound* ps_Sound){

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

			GamePoseControl
			���C���֐�
			
========================================================*/
void GamePoseControl::main(){

	if(m_pDxi->isKeyTrigger(DIK_SPACE) && m_g_pCTaskCtrl->isGetGamePose() == false)
	{
		new Cursor(m_pt_Texture , m_g_pCTaskCtrl , m_Mpt , m_pDxi , GAME_MAIN , TRUE , m_ps_Sound);
		new GamePose(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt);
		m_g_pCTaskCtrl->SetGamePose(true);
	}
};
