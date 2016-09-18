#include "TaskFuncs.h"


/*------------------------------------------------------

				���̑�Task

------------------------------------------------------*/
/*======================================================

			���̑��̃R���X�g���N�^

=======================================================*/
NibuAvis::NibuAvis(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT) ;
	//NAME�ݒ�
	m_cpName = "NibuAvis" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�T�E���h
	m_ps_Sound = ps_Sound;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_nibu->TextureSet() );
	//RECT�̎w��
	SetRect(NIBUAVIS_RECT_LEFT,NIBUAVIS_RECT_TOP,NIBUAVIS_RECT_RIGHT,NIBUAVIS_RECT_BOTTOM);
	//�O���[�v�̐ݒ�
	m_iGroup = GROUP_NIBUAVIS ;
	//���W�̐ݒ�
	x = NIBUAVIS_X;
	y = NIBUAVIS_Y;
	z = NIBUAVIS_Z;
	//�ړ���
	dx = -3;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(0);
	//������̃R���W����
	colx = NIBUAVIS_COLX ;
	coly = NIBUAVIS_COLY ;

	//�h�炷���h�炳�Ȃ���
	m_swing_flg = false;
	//�h��Ă鎞�̃J�E���g������
	m_swing_count = 0;
	//�h����X�^�[�g������
	m_swing_start_count = 0;
	//�E������
	m_swing_left_right_flg = true;
};
/*======================================================

			���̑���Main

=======================================================*/
void NibuAvis::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose() && m_bNew_Flg == false && m_g_pCTaskCtrl->isGetStartFlg())
	{
		Swing();
		Move();
	}
};
/*======================================================

			���̑��̓���

=======================================================*/
void NibuAvis::Move() {
	if(x <= 80 || x > 700)
	{
		dx = -dx;
	}
};
/*======================================================

			���̑��̗h��֐�

=======================================================*/
void NibuAvis::Swing() {

	//�h�炵�J�n
	if(m_swing_start_count >= NIBUAVIS_SWING_COUNT_RAND)
	{
		if(m_swing_flg == false)
		{
			m_tmp_dx = dx;
			//�ړ��X�g�b�v
			dx = 0;
		}
		m_swing_flg = true ;
	}
	else
	{
		//�h�炵�J�E���g
		m_swing_start_count++;
	}

	//�h�炵�J�n��������
	if(m_swing_flg)
	{
		//�h�炵�Ă��鎞��
		m_swing_count++;
		if(m_swing_count % 5 == 1)
		{
			//SE�Đ�
			SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_swing_se);
			//���[�v���Ȃ��ōĐ�
			m_se->Play(FALSE);
		}
		//�E�ɗh���
		if(m_swing_left_right_flg)
		{
			//���ɗh���悤�ɂ���
			m_swing_left_right_flg = false ;
			//���ɍ��W��ύX
			this->x = NIBUAVIS_SWING_X_MIN;
		}
		else 
		{
			//�E�ɗh���悤�ɂ���
			m_swing_left_right_flg = true ;
			//�E�ɍ��W���Z�b�g����
			this->x = NIBUAVIS_SWING_X_MAX;
		}
		//�h��Ă�J�E���g�����ɂ�������
		if(m_swing_count >= NIBUAVIS_SWING_COUNT_MAX)
		{
			dx = m_tmp_dx ;
			int kind = rand()%5;
			switch(kind)
			{
				case 0:
					//�������o��������
					new SmallBird(m_pt_Texture , m_g_pCTaskCtrl , x , y,m_ps_Sound);
					break;
				default:
					//�����o��������
					new Egg(m_pt_Texture , m_g_pCTaskCtrl , x , y,m_ps_Sound);
					break;
			}
			//���̂��̂͂��ׂď�����
			m_swing_count = 0;
			m_swing_start_count = 0;
			m_swing_flg = false ;
		}
	}

};
/*======================================================

			���̑��̓�����

=======================================================*/
void NibuAvis::Hit(CTaskFunc* task) {

	switch(task->m_iGroup)
	{
		case GROUP_EGG:
			
			break;
		case GROUP_SMALLBIRD:
			
			break;
	}
};