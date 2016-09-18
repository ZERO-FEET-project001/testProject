#include "TaskFuncs.h"


/*------------------------------------------------------

				���̗�

------------------------------------------------------*/
/*======================================================

			���̗��̃R���X�g���N�^

=======================================================*/
Egg::Egg(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl, float nibus_x ,float nibus_y,SetSound* ps_Sound) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT  | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT ) ;
	//NAME�ݒ�
	m_cpName = "EGG" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_egg->TextureSet() );
	//�T�E���h
	m_ps_Sound = ps_Sound;
	//�O���[�v�̐ݒ�
	m_iGroup = GROUP_EGG ;
	//RECT�̎w��
	SetRect(EGG_RECT_LEFT,EGG_RECT_TOP,EGG_RECT_RIGHT,EGG_RECT_BOTTOM);
	//���W�̐ݒ�
	x = nibus_x;
	y = nibus_y;
	z = EGG_Z;
	//������̃R���W����
	colx = EGG_COLX ;
	coly = EGG_COLY ;

	int kind = rand()%2;
	//�ǂ����������𔻒f���Ĉړ��ʂ�����
	if(kind == 0)
	{
		dx = EGG_DX;
	}
	else
	{
		dx = -EGG_DX;
	}
	dy = EGG_DY;

	//���Ƃ̓����蔻��
	m_hit_line = false;

	//���̃��C�t
	m_life = EGG_LIFE_MAX;

	//���̑��ɂ������Ă�����
	m_hit_nibus = false ;

	//�����z��������J�E���g
	m_smallbird_count = 0;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	m_linecount = 0;
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();

};
/*======================================================

			���̗���Main

=======================================================*/
void Egg::main() {
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		//����
		Move();
		//���˕Ԃ�
		Spring();
		//�T��
		EggSplit();
	}
};
/*======================================================

			���̗��̓���

=======================================================*/
void Egg::Move() {

	//�������Ă�����

	if(y >= m_g_pCTaskCtrl->isGetBorderLine())
	{
		m_hit_nibus = true ;//���̑�
		if(z == EGG_Z)
		{
			m_hit_line = true;//��
			z = EGG_BORDER_Z;//���̑����O��
		}
	}
	else if(y <= m_g_pCTaskCtrl->isGetBorderLine() && z == EGG_BORDER_Z)
	{
		m_hit_line = true;//��
	}

	//�d��
	dy += GRAVITY;

	//��]
	m_rotate += EGG_RORATE ;

	//�z��
	if(m_smallbird_count >= 5)
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_eggbreak_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		//�폜
		Delete();
		for(int i=0 ; i < EGGSHELL_MAX ; i++)
		{
			//���̊k
			new EggShell(m_pt_Texture , m_g_pCTaskCtrl , x , y , GAME_MAIN);
		}

		//�����z��������
		new SmallBird(m_pt_Texture , m_g_pCTaskCtrl , x ,y,m_ps_Sound);
	}

	//��ʂ𒴂�����f���[�g
	if(y >= HI_MAX)
	{
		//�|200�ƕ\��
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER2);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT2);//�X�R�A���Z
		Delete();//�폜
	}
};
/*======================================================

			���̗��̒��˕Ԃ�

=======================================================*/
void Egg::Spring() {
	
	//�[�̕ǂɓ��������璵�˕Ԃ�
	//��
	if( x < ( EGG_LEFT_MAX + colx ))
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		x = EGG_LEFT_MAX + colx;
		dx = -dx;
		m_life--;
	}
	//�E
	else if(x > ( EGG_RIGHT_MAX - colx ))
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		x = EGG_RIGHT_MAX - colx;
		dx = -dx;
		m_life--;
	}
};
/*======================================================

			���̗��̓����蔻��

=======================================================*/
void Egg::Hit(CTaskFunc* task) {
	
	switch(task->m_iGroup)
	{
		//���ɓ���������
		case GROUP_LINE:
			if(m_hit_line)
			{
				LineHit(task);
			}
			break;
		//���̑��ɓ���������
		case GROUP_NIBUAVIS:
			if(m_hit_nibus)
			{
				NibusHit(task);
			}
			break;
	}
};
/*======================================================

			���̗��̓�����i���j����

=======================================================*/
void Egg::LineHit(CTaskFunc* line) {

		
	if(this->y - this->coly < line->y - line->coly
		&& this->x > line->x - line->colx 
		&& this->x < line->x + line->colx)  
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		m_hit_line = false ;
		m_linecount = m_g_pCTaskCtrl->isGetLineCount();
		//�E�オ��
		if(m_g_pCTaskCtrl->isGetLineTurn())
		{
			x = x - E_DX;
			y = y - dy;
			//�����E�Ɍ������Ă鎞
			if(dx >= 0)
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
			//�������Ɍ������Ă鎞
			else if(dx < 0)
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
		}
		//�E������
		else
		{
			x = x + E_DX;
			y = y - dy;
			
			//�����E�Ɍ������Ă鎞
			if(dx >= 0)
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
				
			}
			//�������Ɍ������Ă鎞
			else if(dx < 0)
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
		}

		//���������獂����΂��I
		dy = -dy * 1.03f;
		//�z���ւ̃J�E���g�_�E��
		m_smallbird_count++;
		
	}
	

};
/*======================================================

			���̗��̓�����i���̑��j����

=======================================================*/
void Egg::NibusHit(CTaskFunc* nibus) {

	//���̉��ɒ��̑�������
	if(this->y - this->coly < nibus->y - nibus->coly
		&& this->x > nibus->x - nibus->colx 
		&& this->x < nibus->x + nibus->colx)  
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_in_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		new InPoint(m_pt_Texture , m_g_pCTaskCtrl , x , y ,m_linecount);
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER0);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT0 * m_g_pCTaskCtrl->isGetLinePoint(m_linecount));
		Delete();
	}
	//���̏�ɒ��̑�������
	else if(this->y + this->coly > nibus->y + nibus->coly
			&& this->x > nibus->x - nibus->colx 
			&& this->x < nibus->x + nibus->colx)  
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		m_hit_nibus = false ;
		if(dy <= 0)
		{
			y += -dy;
			dy = 0;
		}
	}

	//���̉E�ɒ��̑�������
	if(this->x - this->colx - 32< nibus->x - nibus->colx 
		&& this->y > nibus->y - nibus->coly 
		&& this->y < nibus->y + nibus->coly)
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		x -= dx;
		dx = -(dx * E);
	}
	//���̍��ɒ��̑�������
	else if(this->x + this->colx + 32 > nibus->x + nibus->colx
			&& this->y > nibus->y - nibus->coly 
			&& this->y < nibus->y + nibus->coly)
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		x += dx;
		dx = -(dx * E);
	}
};
/*======================================================

			���̗��̋T��

=======================================================*/
void Egg::EggSplit() {

	switch(m_life)
	{
		case 2:
			//RECT�̎w��
			SetRect(32,0,64,32);
			break;
		case 1:
			//RECT�̎w��
			SetRect(64,0,96,32);

			break;
		case 0:
			//�폜
			Delete();
			//�X�R�A���}�C�i�X
			new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER2);
			m_g_pCTaskCtrl->SetScore(SCOREPOINT2);
			//SE�Đ�
			SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_eggbreak_se);
			//���[�v���Ȃ��ōĐ�
			m_se->Play(FALSE);
			//�k�������ς��o��
			for(int i=0 ; i < EGGSHELL_MAX ; i++)
			{
				new EggShell(m_pt_Texture , m_g_pCTaskCtrl , x , y ,GAME_MAIN);
			}
			break;
	}
};