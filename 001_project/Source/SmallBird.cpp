#include "TaskFuncs.h"


/*------------------------------------------------------

				����

------------------------------------------------------*/
/*======================================================

			�����̃R���X�g���N�^

=======================================================*/
SmallBird::SmallBird(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl, float nibus_x ,float nibus_y,SetSound* ps_Sound) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT  | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT ) ;
	//NAME�ݒ�
	m_cpName = "SmallBird" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�T�E���h
	m_ps_Sound = ps_Sound;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_smallbird->TextureSet() );
	//�O���[�v�̐ݒ�
	m_iGroup = GROUP_SMALLBIRD ;
	//���W�̐ݒ�
	x = nibus_x;
	y = nibus_y;
	z = SMALLBIRD_Z;
	//������̃R���W����
	colx = SMALLBIRD_COLX ;
	coly = SMALLBIRD_COLY ;

	int kind = rand()%2;
	//�ǂ����������𔻒f���Ĉړ��ʂ�����
	if(kind == 0)
	{
		dx = SMALLBIRD_DX;
	}
	else
	{
		dx = -SMALLBIRD_DX;
	}
	dy = SMALLBIRD_DY;
	if(dx <= 0)
	{
		//RECT�̎w��
		SetRect(SMALLBIRD_RECT_LEFT_L,SMALLBIRD_RECT_TOP_L,SMALLBIRD_RECT_RIGHT_L,SMALLBIRD_RECT_BOTTOM_L);
	}
	else
	{
		//RECT�̎w��
		SetRect(SMALLBIRD_RECT_LEFT_R,SMALLBIRD_RECT_TOP_R,SMALLBIRD_RECT_RIGHT_R,SMALLBIRD_RECT_BOTTOM_R);
	}
	//���Ƃ̓����蔻��
	m_hit_line = false;

	//���̑��ɂ������Ă�����
	m_hit_nibus = false ;
	//��ԃt���O
	m_fly_flg = false ;
	//��ԃX�^�[�g�J�E���g
	m_fly_start_count = 0;
	//��ԏI���J�E���g
	m_fly_end_count = 0;
	
	//�p�^�[���ύX�̐ݒ�
	m_iPtntimer_Max = 5 ;
	m_iPtntimer = 0 ;
	m_iPtn = 0 ;
	m_iPtninit = 0 ;
	m_iPtn_Right_Max = 96 ;
	m_iPtn_Max = 2 ;
	m_rectSize.right = SMALLBIRD_RECT_RIGHT_R ;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();
	//SE�Đ�
	SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotori_se);
	//���[�v���Ȃ��ōĐ�
	m_se->Play(FALSE);
};
/*======================================================

			������Main

=======================================================*/
void SmallBird::main() {
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		//����
		Move();
		//���˕Ԃ�
		Spring();
		//���
		Fly();
	}
};
/*======================================================

			�����̓���

=======================================================*/
void SmallBird::Move() {

	//�A�j���[�V����
	PtnChange();

	//�d��
	dy += SMALLBIRD_GRAVITY;

	//�������Ă�����
	if(y >= m_g_pCTaskCtrl->isGetBorderLine())
	{
		m_hit_nibus = true ;//���̑�
		if(z == SMALLBIRD_Z)
		{
			m_hit_line = true;//��
			z = SMALLBIRD_BORDER_Z;//���̑����O��
		}
	}
	else if(y <= m_g_pCTaskCtrl->isGetBorderLine() && z == SMALLBIRD_BORDER_Z)
	{
		m_hit_line = true;//��
	}

	if(y >= m_g_pCTaskCtrl->isGetBorderLine() && m_hit_line == false)
	{
		m_fly_start_count = SMALLBIRD_FLY_COUNT_MAX;
	}
	//�V�����ɍs�����Ȃ�
	if(y <= SMALLBIRD_HI_MAX)
	{
		y += dy;
		dy = 0;
		//��ԃt���O
		m_fly_flg = false ;
		//��ԃX�^�[�g�J�E���g
		m_fly_start_count = 0;
		//��ԏI���J�E���g
		m_fly_end_count = 0;
	}
	//��ʂ𒴂�����f���[�g
	if(y >= HI_MAX)
	{
		//-600�ƕ\��
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER3);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT3);//�X�R�A�̌��Z
		m_g_pCTaskCtrl->SetLife(FALSE);//�c�@���}�C�i�X
		Delete();//�폜
	}
};
/*======================================================

			�����̒��˕Ԃ�

=======================================================*/
void SmallBird::Spring() {
	
	//�[�̕ǂɓ��������璵�˕Ԃ�
	//��
	if( x < ( SMALLBIRD_LEFT_MAX + colx ))
	{
		x = SMALLBIRD_LEFT_MAX + colx;
		dx = -dx;
		Turn();
	}
	//�E
	else if(x > ( SMALLBIRD_RIGHT_MAX - colx ))
	{
		x = SMALLBIRD_RIGHT_MAX - colx;
		dx = -dx;
		Turn();
	}
};
/*======================================================

			�����̓����蔻��

=======================================================*/
void SmallBird::Hit(CTaskFunc* task) {
	
	switch(task->m_iGroup)
	{
		//���ɓ���������
		case GROUP_LINE:
			if(m_hit_line)
			{
				LineHit(task);
			}
			break;
		case GROUP_NIBUAVIS:
			if(m_hit_nibus && z == SMALLBIRD_BORDER_Z)
			{
				NibusHit(task);
			}
			break;
	}
};
/*======================================================

			�����̓�����i���j����

=======================================================*/
void SmallBird::LineHit(CTaskFunc* line) {

		
	if(this->y - this->coly < line->y - line->coly
		&& this->x > line->x - line->colx 
		&& this->x < line->x + line->colx)  
	{		
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		m_hit_line = false ;
		m_linecount = m_g_pCTaskCtrl->isGetLineCount();
		//�E�オ��
		if(m_g_pCTaskCtrl->isGetLineTurn())
		{
			x -= E_DX;
			y -= dy;
			//�����E�Ɍ������Ă鎞
			if(dx >= 0)
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
			//�������Ɍ������Ă鎞
			else
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
		}
		//�E������
		else
		{
			
			x += E_DX;
			y -= dy;
			
			//�����E�Ɍ������Ă鎞
			if(dx >= 0)
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
				
			}
			//�������Ɍ������Ă鎞
			else
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
				
			}
		}
		dy = -dy * 1.01f;
		Turn();
		
	}
	

};
/*======================================================

			�����̓�����i���̑��j����

=======================================================*/
void SmallBird::NibusHit(CTaskFunc* nibus) {


	//�����̉��ɒ��̑�������
	if(this->y - this->coly < nibus->y - nibus->coly
		&& this->x > nibus->x - nibus->colx 
		&& this->x < nibus->x + nibus->colx)  
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_in_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		new InPoint(m_pt_Texture , m_g_pCTaskCtrl , x , y ,m_linecount);
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER1);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT1 * m_g_pCTaskCtrl->isGetLinePoint(m_linecount));
		Delete();
	}
	//�����̏�ɒ��̑�������
	else if(this->y + this->coly > nibus->y + nibus->coly
			&& this->x > nibus->x - nibus->colx 
			&& this->x < nibus->x + nibus->colx)  
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		m_hit_nibus = false ;
		y += -dy;
		dy = 0;
		//��ԃt���O
		m_fly_flg = false ;
		//��ԃX�^�[�g�J�E���g
		m_fly_start_count = 0;
		//��ԏI���J�E���g
		m_fly_end_count = 0;
	}

	//�����̉E�ɒ��̑�������
	if(this->x - this->colx < nibus->x - nibus->colx 
		&& this->y > nibus->y - nibus->coly 
		&& this->y < nibus->y + nibus->coly)
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		//m_hit_nibus = false ;
		x -= dx;
		dx = dx * E;
	}
	//�����̍��ɒ��̑�������
	else if(this->x + this->colx > nibus->x + nibus->colx
			&& this->y > nibus->y - nibus->coly 
			&& this->y < nibus->y + nibus->coly)
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		//m_hit_nibus = false ;
		x += dx;
		dx = dx * E;
	}
};
/*======================================================

			���

=======================================================*/
void SmallBird::Fly() {

	if(m_fly_flg)
	{
		if(dy >= 0)
		{
			dy -= 3.0f;
		}

		m_fly_end_count++;

		if(m_fly_end_count >= SMALLBIRD_FLY_COUNT_MAX)
		{
			dy = 0;
			m_fly_flg = false;
			m_fly_end_count = 0;
		}

	}
	else
	{
		m_fly_start_count ++;
		if(m_fly_start_count >= SMALLBIRD_FLY_COUNT_MAX)
		{
			m_hit_nibus = true ;
			m_fly_flg = true;
			m_fly_start_count = 0;
			
		}
	}
};
/*======================================================

			����

=======================================================*/
void SmallBird::Turn() {

	if( dx > 0)
	{
		//�������E��
		SetRect(SMALLBIRD_RECT_LEFT_R,SMALLBIRD_RECT_TOP_R,SMALLBIRD_RECT_RIGHT_R,SMALLBIRD_RECT_BOTTOM_R);
		m_iPtntimer = 0 ;
		m_iPtn = 0 ;
		m_iPtninit = 0 ;
	}
	else if( dx < 0)
	{
		//����������
		SetRect(SMALLBIRD_RECT_LEFT_L,SMALLBIRD_RECT_TOP_L,SMALLBIRD_RECT_RIGHT_L,SMALLBIRD_RECT_BOTTOM_L);
		m_iPtntimer = 0 ;
		m_iPtn = 0 ;
		m_iPtninit = 0 ;
	}
};