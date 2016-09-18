#include "TaskFuncs.h"


/*------------------------------------------------------

				�w�i

------------------------------------------------------*/
/*======================================================

			�w�i�̃R���X�g���N�^

=======================================================*/
Bg::Bg(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "Bg" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_bg->TextureSet() );
	//RECT�̎w��
	SetRect(BG_RECT_LEFT,BG_RECT_TOP,BG_RECT_RIGHT,BG_RECT_BOTTOM);

	//���W�̐ݒ�
	x = BG_X;
	y = BG_Y;
	z = BG_Z;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(0);

};
/*======================================================

			�w�i��Main

=======================================================*/
void Bg::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);

	ModeDelete(m_g_pCTaskCtrl);
};
