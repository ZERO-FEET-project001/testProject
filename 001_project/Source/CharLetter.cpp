#include "TaskFuncs.h"
/*========================================================

			Score�R���X�g���N�^

========================================================*/
CharLetter::CharLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl ,SetSound* ps_Sound)
{
	// ����������
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME�ݒ�
	m_cpName = "CharLetter" ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_char->TextureSet());
	//�T�E���h
	m_ps_Sound = ps_Sound;
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	//�T�E���h
	m_ps_Sound = ps_Sound;	
	//RECT�̎w��
	SetRect(0,0,520,80);
	
	//�X�R�A�����ʒu�̐ݒ�i�j
	this->x = CHARLETTER_X;
	this->y = CHARLETTER_Y ;
	this->z = CHARLETTER_Z ;

	dy = CHARLETTER_SOEED ;

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
void CharLetter::main()
{
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}
};
/*========================================================

			�����֐�

========================================================*/
void CharLetter::Move()
{
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(m_alpha);

	//�����t���O��FALSE�̎�
	if(m_move_flg == false)
	{
		//�A���t�@�l�𑝂₵�Ă���
		m_alpha +=	CHARLETTER_APLHA;
	}

	//�����W�����ɍs���Ă���ɓ����t���O��FALSE�̎�
	if(y <= CHARLETTER_Y_MAX && m_move_flg == false)
	{
		//�����J�E���g�𑫂��Ă���
		m_move_count++;
		//�������~�߂�
		dy = 0;
		//�A���t�@��255�Ɏw��
		m_alpha = ALPHA_MAX;
		//�J�E���g��MAX�𒴂�����
		if(m_move_count >= CHARLETTER_COUNT_MAX)
		{
			//TRUE�ɐݒ�
			m_move_flg = true;
		}
	}

	//�����t���O��TRUE�̎�
	if(m_move_flg)
	{
		//�ړ��ʂ�ݒ�
		dy = CHARLETTER_SOEED;
		//�A���t�@�����炵�Ă���
		m_alpha -= CHARLETTER_APLHA;
		//�A���t�@��0�ɂȂ�����폜
		if(m_alpha <= 0)
		{
			Delete();
		}

	}

};