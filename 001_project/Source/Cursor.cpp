#include "TaskFuncs.h"

/*------------------------------------------------------

				�J�[�\��

------------------------------------------------------*/
/*======================================================

			�J�[�\���̃R���X�g���N�^

=======================================================*/
Cursor::Cursor(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl ,POINT* Mpt , DxInput* pDxi,int kind, BOOL starting_flg,SetSound* ps_Sound) {

	// ����������
	setTaskFlag( TASK_FLAG_OBJECT) ;

	//NAME�ݒ�
	m_cpName = "Cursor" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�T�E���h
	m_ps_Sound = ps_Sound;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_cursor->TextureSet() );

	//RECT�̎w��
	SetRect(0,0,76,60);

	m_Mpt = Mpt;

	m_pDxi = pDxi;

	//�����ʒu�̎w��
	x = -100;
	y = -100 ;
	z =  0.0f;

	m_iPtntimer_Max = 5  ;//RECT�؂�ւ����Ԃ̍ő�
	m_iPtntimer = 0 ;//RECT�̐؂�ւ�����
	m_iPtn = 0 ;//���݂̉摜�̃p�^�[���ԍ�
	m_iPtn_Max = 3 ;//�ő�̉摜�̃p�^�[���ԍ�
	m_rectSize.right = 76;//�ύXRECT
	m_iPtn_Right_Max = 225;

	m_iMode = kind ;
	m_starting_flg = starting_flg ;
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	if(m_starting_flg)
	{
		SetAlpha();
	}
};
/*======================================================

			�J�[�\����Main

=======================================================*/
void Cursor::main() {
	if(!m_starting_flg)
	{
		ModeNew(m_g_pCTaskCtrl,TRUE);
	}
	ModeDelete(m_g_pCTaskCtrl);
	Animation();
	PointChange();

};
/*======================================================

			�J�[�\���̃A�j���[�V����

=======================================================*/
void Cursor::Animation() {
	PtnChange();
};
/*======================================================

			�J�[�\���̍��W�̕ύX

=======================================================*/
void Cursor::PointChange() {

	//�Q�[�����̉�ʂ�������
	if(m_g_pCTaskCtrl->isGetGameMode() == GAME_MAIN)
	{
		if(m_Mpt->x >= 235 && m_Mpt->x <= 525 && m_Mpt->y >= 245 && m_Mpt->y <= 285)
		{
			x = 200 ;
			y = 250 ;
			if(m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
			{
				//SE�Đ�
				SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_corsor_ok_se);
				//���[�v���Ȃ��ōĐ�
				m_se->Play(FALSE);
				Delete();
			}
		}
		else if(m_Mpt->x >= 220 && m_Mpt->x <= 550 && m_Mpt->y >= 365 && m_Mpt->y <= 400)
		{
			x = 180 ;
			y = 380 ;
			if(m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
			{
				//SE�Đ�
				SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_corsor_ok_se);
				//���[�v���Ȃ��ōĐ�
				m_se->Play(FALSE);
				Delete();
			}
		}
	}
	//�Q�[�����̉�ʂ�������
	else if(m_g_pCTaskCtrl->isGetGameMode() == GAME_TITLE)
	{
		if(m_Mpt->x >= 280 && m_Mpt->x <= 490 && m_Mpt->y >= 320 && m_Mpt->y <= 365)
		{
			x = 250 ;
			y = 340 ;
		}
		else if(m_Mpt->x >= 280 && m_Mpt->x <= 490 && m_Mpt->y >= 390 && m_Mpt->y <= 440)
		{
			x = 250 ;
			y = 410 ;
		}	
	}
};
