#include "TaskFuncs.h"


/*------------------------------------------------------

				�Q�[���I�[�o�[

------------------------------------------------------*/
/*======================================================

			�Q�[���I�[�o�[�̃R���X�g���N�^

=======================================================*/
BorderLine::BorderLine(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture,SetSound* ps_Sound) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "BORDERLINE" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�T�E���h
	m_ps_Sound = ps_Sound;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_border->TextureSet() );
	//���N�g�̐ݒ�
	SetRect(BORDERLINE_RECT_LEFT,BORDERLINE_RECT_TOP,BORDERLINE_RECT_RIGHT,BORDERLINE_RECT_BOTTOM);
	//���W�̐ݒ�
	x = BORDERLINE_X;
	y = BORDERLINE_Y;
	z = BORDERLINE_Z;

	//���W���Z�b�g
	m_move_y = y ;
	m_move_flg = false ;
	m_move_count = 1;
	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(0);
	
};
/*======================================================

			���E����Main

=======================================================*/
void BorderLine::main() {

	ModeNew(m_g_pCTaskCtrl,TRUE);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}
	ModeDelete(m_g_pCTaskCtrl);
};
/*======================================================

			���E���̓���

=======================================================*/
void BorderLine::Move() {

	if(m_move_flg == false)
	{
		if(m_g_pCTaskCtrl->isGetScore() >= BORDERSCORE * m_move_count)
		{
			m_move_count++;
			m_move_flg = true ;
			m_move_y += BORDERLINE_MOVE_Y * m_move_count ;
			new CharLetter(m_pt_Texture,m_g_pCTaskCtrl,m_ps_Sound);
		}
	}

	if(m_move_flg)
	{
		if(y < m_move_y)
		{
			y += 0.5f;
			if(y >= m_move_y)
			{
				m_move_flg = false;
			}
		}
	}

	m_g_pCTaskCtrl->SetBorderLine(y);
};

