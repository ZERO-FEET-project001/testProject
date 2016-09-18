#include "TaskFuncs.h"


/*------------------------------------------------------

				�Q�[���̃|�[�Y

------------------------------------------------------*/
/*======================================================

			�Q�[���̃|�[�Y�̃R���X�g���N�^

=======================================================*/
GamePose::GamePose(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "GamePose" ;
	//�^�X�N�̗D��x
	m_fPriority = 1;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�L�[�{�[�h�|�C���^
	m_pDxi = pDxi;
	//�}�E�X�̃|�C���^
	m_Mpt = Mpt;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_pose->TextureSet() );
	SetRect(GAMEPOSE_RECT_LEFT,GAMEPOSE_RECT_TOP,GAMEPOSE_RECT_RIGHT,GAMEPOSE_RECT_BOTTOM);
	//���W�̐ݒ�
	x = GAMEPOSE_X;
	y = GAMEPOSE_Y;
	z = GAMEPOSE_Z;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();

};
/*======================================================

			�Q�[���̃|�[�Y��Main

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
