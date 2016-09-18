#include "TaskFuncs.h"
/*========================================================

			�X�^�[�g�̕����R���X�g���N�^

========================================================*/
StartLetter::StartLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl ,SetSound* ps_Sound)
{
	// ����������
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME�ݒ�
	m_cpName = "StartLetter" ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_start->TextureSet());
	//�T�E���h
	m_ps_Sound = ps_Sound;
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	
	//RECT�̎w��
	SetRect(0,0,192,64);
	
	//�X�R�A�����ʒu�̐ݒ�i�j
	this->x = STARTLETTER_X;
	this->y = STARTLETTER_Y ;
	this->z = STARTLETTER_Z ;

	m_alpha = 0 ;
	m_move_count = 0 ;
	m_move_flg = false;
	m_kind = 0;
	m_start_count = 0;
	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(m_alpha);
};
/*========================================================

			���C���֐�

========================================================*/
void StartLetter::main()
{
	ModeNew(m_g_pCTaskCtrl,FALSE);

	if(!m_g_pCTaskCtrl->isGetGamePose()&& m_bNew_Flg == false )
	{
		if(m_kind == 0)
		{
			Move();
		}
		else if(m_kind == 1)
		{
			//RECT�̎w��
			SetRect(0,64,192,128);
			this->y = STARTLETTER_Y ;
			m_alpha = 0 ;
			m_move_count = 0 ;
			m_move_flg = false;
			m_kind = 2;

		}
		else if(m_kind == 2)
		{
			if(m_g_pCTaskCtrl->isGetStartFlg() == false)
			{
				//SE�Đ�
				SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_start_se);
				//���[�v���Ȃ��ōĐ�
				m_se->Play(FALSE);
			}
			m_g_pCTaskCtrl->SetStartFlg(TRUE);
			StartMove();
		}
	}
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(m_alpha);
	ModeDelete(m_g_pCTaskCtrl);
};
/*========================================================

			�����֐�

========================================================*/
void StartLetter::Move()
{
	m_start_count++;
	if(m_start_count >= 100)
	{
		//�����W�����ɍs���Ă���ɓ����t���O��FALSE�̎�
		if(m_move_flg == false)
		{
			//�A���t�@�l�𑝂₵�Ă���
			m_alpha +=	STARTLETTER_APLHA;

			//�����J�E���g�𑫂��Ă���
			m_move_count++;
			if(m_alpha > ALPHA_MAX)
			{
				//�A���t�@��255�Ɏw��
				m_alpha = ALPHA_MAX;
			}
			//�J�E���g��MAX�𒴂�����
			if(m_move_count >= STARTLETTER_COUNT_MAX)
			{
				//TRUE�ɐݒ�
				m_move_flg = true;
			}
		}

		//�����t���O��TRUE�̎�
		if(m_move_flg)
		{
			//�A���t�@�����炵�Ă���
			m_alpha -= STARTLETTER_APLHA;
			//�A���t�@��0�ɂȂ�����폜
			if(m_alpha <= 0)
			{
				m_kind = 1;
			}
		}
	}

};
/*========================================================

			�X�^�[�g�̓����֐�

========================================================*/
void StartLetter::StartMove()
{
	//�����W�����ɍs���Ă���ɓ����t���O��FALSE�̎�
	if(m_move_flg == false)
	{
		//�A���t�@�l�𑝂₵�Ă���
		m_alpha +=	STARTLETTER_APLHA;

		//�����J�E���g�𑫂��Ă���
		m_move_count++;
		//�A���t�@��255�Ɏw��
		m_alpha = ALPHA_MAX;
		//�J�E���g��MAX�𒴂�����
		if(m_move_count >= STARTLETTER_COUNT_MAX)
		{
			//TRUE�ɐݒ�
			m_move_flg = true;
			
		}
	}

	//�����t���O��TRUE�̎�
	if(m_move_flg)
	{
		//�A���t�@�����炵�Ă���
		m_alpha -= STARTLETTER_APLHA;
		//�A���t�@��0�ɂȂ�����폜
		if(m_alpha <= 0)
		{
			Delete();
		}
	}

};