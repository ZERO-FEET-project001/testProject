#include "TaskFuncs.h"


/*------------------------------------------------------

				���̊k

------------------------------------------------------*/
/*======================================================

			���̊k�̃R���X�g���N�^

=======================================================*/
EggShell::EggShell(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,float egg_x,float egg_y , int gamemode) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "EggShell" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_eggshell->TextureSet() );
	//RECT�̎w��
	SetRect(EGGSHELL_RECT_LEFT,EGGSHELL_RECT_TOP,EGGSHELL_RECT_RIGHT,EGGSHELL_RECT_BOTTOM);
	//���W�̐ݒ�
	x = egg_x;
	y = egg_y;
	z = EGGSHELL_Z;
	//������̃R���W����
	colx = EGGSHELL_COLX ;
	coly = EGGSHELL_COLY ;

	int kind = rand()%2;
	//�ǂ����������𔻒f���Ĉړ��ʂ�����
	if(kind == 0)
	{
		dx = EGGSHELL_DX;
	}
	else
	{
		dx = -EGGSHELL_DX;
	}
	dy = EGGSHELL_DY;

	//���Ƃ̓����蔻��
	m_hit_line = false;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = gamemode;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();

};
/*======================================================

			���̊k��Main

=======================================================*/
void EggShell::main() {
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		//����
		Move();
		//���˕Ԃ�
		Spring();
	}
};
/*======================================================

			���̊k�̓���

=======================================================*/
void EggShell::Move() {

	if( m_hit_line == false )
	{
		//�d��
		dy += GRAVITY;
	}
	else
	{
		//dy = m_tmp_dy;
		m_hit_line = false ;
	}
	//��]
	m_rotate += EGGSHELL_RORATE ;

	//��ʂ𒴂�����f���[�g
	if(y >= HI_MAX)
	{
		Delete();
	}
};
/*======================================================

			���̊k�̒��˕Ԃ�

=======================================================*/
void EggShell::Spring() {
	
	//�[�̕ǂɓ��������璵�˕Ԃ�
	//��
	if( x < ( EGG_LEFT_MAX + colx ))
	{
		dx = -dx;
	}
	//�E
	else if(x > ( EGG_RIGHT_MAX - colx ))
	{
		dx = -dx;
	}
};

