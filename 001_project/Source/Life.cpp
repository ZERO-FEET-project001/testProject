#include "TaskFuncs.h"


/*------------------------------------------------------

				�c�@

------------------------------------------------------*/
/*======================================================

			�c�@�̃R���X�g���N�^

=======================================================*/
Life::Life(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,int kind) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "Life" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_life->TextureSet() );
	//RECT�̎w��
	SetRect(LIFE_RECT_LEFT,LIFE_RECT_TOP,LIFE_RECT_RIGHT,LIFE_RECT_BOTTOM);
	//���W�̐ݒ�
	x = LIFE_X;
	y = LIFE_Y;
	z = LIFE_Z;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(0);

};
/*======================================================

			�c�@��Main

=======================================================*/
void Life::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);
};

