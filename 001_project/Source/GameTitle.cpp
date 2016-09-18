#include "TaskFuncs.h"


/*------------------------------------------------------

				�^�C�g��

------------------------------------------------------*/
/*======================================================

			�^�C�g���̃R���X�g���N�^

=======================================================*/
GameTitle::GameTitle(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt, BOOL starting_flg) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "GameTitle" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�L�[�{�[�h�|�C���^
	m_pDxi = pDxi;
	//�}�E�X�̃|�C���^
	m_Mpt = Mpt;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_title->TextureSet() );
	//���N�g�̐ݒ�
	SetRect(GAMETITLE_RECT_LEFT,GAMETITLE_RECT_TOP,GAMETITLE_RECT_RIGHT,GAMETITLE_RECT_BOTTOM);
	//���W�̐ݒ�
	x = GAMETITLE_X;
	y = GAMETITLE_Y;
	z = GAMETITLE_Z;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_TITLE;
	m_starting_flg = starting_flg ;
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	if(m_starting_flg)
	{
		SetAlpha();
	}
};
/*======================================================

			�^�C�g����Main

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

			�Q�[�����[�h��ύX����֐�

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
