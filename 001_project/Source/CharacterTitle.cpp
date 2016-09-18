#include "TaskFuncs.h"


/*------------------------------------------------------

				�^�C�g���̃L�����N�^�[

------------------------------------------------------*/
/*======================================================

			�^�C�g���̃L�����N�^�[�̃R���X�g���N�^

=======================================================*/
CharacterTitle::CharacterTitle(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,POINT* Mpt,DxInput *pDxi,SetSound* ps_Sound) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "CharacterTitle" ;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//�T�E���h
	m_ps_Sound = ps_Sound;
	m_kind= CHARACTERTITLE_RAND;
	m_Mpt = Mpt ;
	m_pDxi = pDxi ;
	switch(m_kind)
	{
		case 0:
			//Texture�̃Z�b�g���s��
			GetTexture( pt_Texture->m_pg_egg->TextureSet() );
			//RECT�̎w��
			SetRect(EGG_RECT_LEFT,EGG_RECT_TOP,EGG_RECT_RIGHT,EGG_RECT_BOTTOM);
			break;
		default:
			//Texture�̃Z�b�g���s��
			GetTexture( pt_Texture->m_pg_smallbird->TextureSet() );
			//RECT�̎w��
			SetRect(SMALLBIRD_RECT_LEFT_R,SMALLBIRD_RECT_TOP_R,SMALLBIRD_RECT_RIGHT_R,SMALLBIRD_RECT_BOTTOM_R);

			break;
	}


	//���W�̐ݒ�
	x = CHARACTERTITLE_X;
	y = CHARACTERTITLE_Y;
	z = CHARACTERTITLE_Z;

	dx = CHARACTERTITLE_DX;
	
	colx = SMALLBIRD_RECT_RIGHT_R;
	coly = SMALLBIRD_RECT_BOTTOM_R;

	//�p�^�[���ύX�̐ݒ�
	m_iPtntimer_Max = 5 ;
	m_iPtntimer = 0 ;
	m_iPtn = 0 ;
	m_iPtninit = 0 ;
	m_iPtn_Right_Max = 96 ;
	m_iPtn_Max = 2 ;
	m_rectSize.right = SMALLBIRD_RECT_RIGHT_R ;

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_TITLE;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();

};
/*======================================================

			�^�C�g���̃L�����N�^�[��Main

=======================================================*/
void CharacterTitle::main() {
	ModeDelete(m_g_pCTaskCtrl);
	//����
	Move();
	switch(m_kind)
	{
		case 0:
			MouseHitEgg();
			break;
		default:
			MouseHitBird();
			break;
	}
	
};
/*======================================================

			�^�C�g���̃L�����N�^�[�̓���

=======================================================*/
void CharacterTitle::Move() {
	if(m_kind != 0)
	{
		PtnChange();
	}
	else if (m_kind == 0) 
	{
		//��]
		m_rotate += CHARACTERTITLE_ROTATE ;
	}
	if(x > ( WID_MAX + colx ))
	{
		Delete();
	}
};
/*======================================================

			�^�C�g���̃L�����N�^�[�Ƀ}�E�X�ŃN���b�N����Ɓi�����j

=======================================================*/
void CharacterTitle::MouseHitBird() {

	if(m_Mpt->x > (this->x - this->colx) && m_Mpt->x < (this->x + this->colx) 
		&& m_Mpt->y > (this->y - this->coly) && m_Mpt->y < (this->y + this->coly) && m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotori_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		dy = -3;
	}
};
/*======================================================

			�^�C�g���̃L�����N�^�[�Ƀ}�E�X�ŃN���b�N����Ɓi���j

=======================================================*/
void CharacterTitle::MouseHitEgg() {

	if(m_Mpt->x > (this->x - this->colx) && m_Mpt->x < (this->x + this->colx) 
		&& m_Mpt->y > (this->y - this->coly) && m_Mpt->y < (this->y + this->coly) && m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
	{
		//SE�Đ�
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_eggbreak_se);
		//���[�v���Ȃ��ōĐ�
		m_se->Play(FALSE);
		Delete();
		for(int i=0 ; i < EGGSHELL_MAX ; i++)
		{
			//���̊k
			new EggShell(m_pt_Texture , m_g_pCTaskCtrl , x , y , GAME_TITLE);
		}
	}
};
