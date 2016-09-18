#include "TaskFuncs.h"


/*------------------------------------------------------

				�c�@

------------------------------------------------------*/
/*======================================================

			�c�@�̃R���X�g���N�^

=======================================================*/
Cross::Cross(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,int kind,SetSound* ps_Sound) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "Cross" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�T�E���h
	m_ps_Sound = ps_Sound;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_cross->TextureSet() );
	//RECT�̎w��
	SetRect(CROSS_RECT_LEFT,CROSS_RECT_TOP,CROSS_RECT_RIGHT,CROSS_RECT_BOTTOM);
	//���W�̐ݒ�
	x = CROSS_X;
	y = CROSS_Y;
	z = CROSS_Z;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();
	//SE�Đ�
	SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_batu_se);
	//���[�v���Ȃ��ōĐ�
	m_se->Play(FALSE);

};
/*======================================================

			�c�@��Main

=======================================================*/
void Cross::main() {
	ModeDelete(m_g_pCTaskCtrl);
};

