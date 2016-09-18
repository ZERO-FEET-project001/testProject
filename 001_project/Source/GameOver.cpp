#include "TaskFuncs.h"


/*------------------------------------------------------

				�Q�[���I�[�o�[

------------------------------------------------------*/
/*======================================================

			�Q�[���I�[�o�[�̃R���X�g���N�^

=======================================================*/
GameOver::GameOver(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "GAMEOVER" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�L�[�{�[�h�|�C���^
	m_pDxi = pDxi;
	//�}�E�X�̃|�C���^
	m_Mpt = Mpt;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_gameover->TextureSet() );
	//���N�g�̐ݒ�
	SetRect(GAMEOVER_RECT_LEFT,GAMEOVER_RECT_TOP,GAMEOVER_RECT_RIGHT,GAMEOVER_RECT_BOTTOM);
	//���W�̐ݒ�
	x = GAMEOVER_X;
	y = GAMEOVER_Y;
	z = GAMEOVER_Z;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_OVER;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g

	SetAlpha(0);
};
/*======================================================

			�Q�[���I�[�o�[��Main

=======================================================*/
void GameOver::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeChange();
	ModeDelete(m_g_pCTaskCtrl);
};
/*======================================================

			�Q�[�����[�h��ύX����֐�

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
