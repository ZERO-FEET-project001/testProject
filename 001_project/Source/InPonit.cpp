#include "TaskFuncs.h"

/*------------------------------------------------------

				���̑��ɓ��������̃G�t�F�N�g

------------------------------------------------------*/
/*======================================================

			���̑��ɓ��������̃G�t�F�N�g�̃R���X�g���N�^

=======================================================*/
InPoint::InPoint( SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y , int line_count) {

	// ����������
	setTaskFlag( TASK_FLAG_OBJECT) ;

	//NAME�ݒ�
	m_cpName = "InPoint" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_point->TextureSet() );

	//RECT�̎w��
	if(m_g_pCTaskCtrl->isGetLinePoint(line_count) == 2.0f)
	{
		SetRect(128,0,192,64);
	}
	else if(m_g_pCTaskCtrl->isGetLinePoint(line_count) == 1.5f)
	{
		SetRect(64,0,128,64);
	}
	else if(m_g_pCTaskCtrl->isGetLinePoint(line_count) == 1.0f)
	{
		SetRect(0,0,64,64);
	}

	//�����ʒu�̎w��
	x = nibus_x ;
	y = nibus_y ;
	z =  0.1f;

	dy = -0.5f;
	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;
	//�A���t�@�̃Z�b�g
	m_alpha = ALPHA_MAX;
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();

};
/*======================================================

			���̑��ɓ��������̃G�t�F�N�g��Main

=======================================================*/
void InPoint::main() {

	ModeDelete(m_g_pCTaskCtrl);

	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}

};
/*======================================================

			����

=======================================================*/
void InPoint::Move() {
	SetAlpha(m_alpha);

	if(m_alpha >= 0)
	{
		m_alpha -= 5;
		if(m_alpha <= 0)
		{
			Delete();
		}
	}
};
