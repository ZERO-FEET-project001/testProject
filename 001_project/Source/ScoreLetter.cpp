#include "TaskFuncs.h"
/*========================================================

			Score�R���X�g���N�^

========================================================*/
ScoreLetter::ScoreLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl , int kind)
{
	// ����������
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME�ݒ�
	m_cpName = "ScoreLetter" ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_scorenumber->TextureSet());

	m_g_pCTaskCtrl = g_pCTaskCtrl ;

	//�؂�ւ��p�ϐ�
	m_kind = kind ;
	
	//RECT�̎w��
	ChangeRect();
	
	//�X�R�A�����ʒu�̐ݒ�i�j
	this->x = SCORELETTER_X;
	this->y = SCORELETTER_Y ;
	this->z = SCORELETTER_Z ;

	dy = SCORELETTER_SOEED ;

	m_alpha = 0 ;
	m_move_count = 0 ;
	m_move_flg = false;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(m_alpha);
};
/*========================================================

			Score���C���֐�

========================================================*/
void ScoreLetter::main()
{
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}
};
/*========================================================

			RECT�ύX�֐�

========================================================*/
void ScoreLetter::ChangeRect()
{
	switch(m_kind)
	{
		//+100
		case SCORELETTER0:
			SetRect(0,50,75,100);
			break;
		//+500
		case SCORELETTER1:
			SetRect(75,50,150,100);
			break;
		//-200
		case SCORELETTER2:
			SetRect(150,50,225,100);
			break;
		//-600
		case SCORELETTER3:
			SetRect(225,50,300,100);
			break;
		default:
			break;
		
	}
};
/*========================================================

			�����֐�

========================================================*/
void ScoreLetter::Move()
{
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(m_alpha);
	//�����t���O��FALSE�̎�
	if(m_move_flg == false)
	{
		//�A���t�@�l�𑝂₵�Ă���
		m_alpha += SCORELETTER_APLHA;
	}

	//�����W�����ɍs���Ă���ɓ����t���O��FALSE�̎�
	if(y <= SCORELETTER_Y_MAX && m_move_flg == false)
	{
		//�����J�E���g�𑫂��Ă���
		m_move_count++;
		//�������~�߂�
		dy=0;
		//�A���t�@��255�Ɏw��
		m_alpha = ALPHA_MAX;
		//�J�E���g��MAX�𒴂�����
		if(m_move_count >= SCORELETTER_COUNT_MAX)
		{
			//TRUE�ɐݒ�
			m_move_flg = true;
		}
	}
	//�����t���O��TRUE�̎�
	if(m_move_flg)
	{
		//�ړ��ʂ�ݒ�
		dy = SCORELETTER_SOEED;
		//�A���t�@�����炵�Ă���
		m_alpha -= SCORELETTER_APLHA;
		//�A���t�@��0�ɂȂ�����폜
		if(m_alpha <= 0)
		{
			Delete();
		}

	}

};