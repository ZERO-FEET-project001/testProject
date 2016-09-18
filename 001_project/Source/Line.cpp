#include "TaskFuncs.h"


/*------------------------------------------------------

				��

------------------------------------------------------*/
/*======================================================

			���̃R���X�g���N�^

=======================================================*/
Line::Line(DxInput* pDxi,SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,LONG Mpt_x,LONG Mpt_y) {

	// �^�X�N�̃t���O�Z�b�g
	setTaskFlag( TASK_FLAG_OBJECT | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT) ;
	//NAME�ݒ�
	m_cpName = "Line" ;
	//�L�[�{�[�h�|�C���^�̕ێ�
	m_pDxi = pDxi;
	//�^�X�N�R���g���[���̃|�C���^
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//�摜�̃|�C���^
	m_pt_Texture = pt_Texture ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_line->TextureSet()  );
	//�O���[�v�̐ݒ�
	m_iGroup = GROUP_LINE ;
	//RECT�̎w��
	SetRect(LINE_RECT_LEFT,LINE_RECT_TOP,LINE_RECT_RIGHT,LINE_RECT_BOTTOM);


	//���W�̐ݒ�
	x = (float)Mpt_x;
	y = (float)Mpt_y;
	z = 0.2f;
	//������̃R���W����
	colx = LINE_COLX ;
	coly = LINE_COLY ;

	//���Ɠ��������I
	m_hit_egg = false ;
	m_alpha = ALPHA_MAX;
	m_g_pCTaskCtrl->SetLineAlpha(ALPHA_MAX);
	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha();
};
/*======================================================

			����Main

=======================================================*/
void Line::main() {

	ModeDelete(m_g_pCTaskCtrl);

	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		m_alpha = (INT)(m_g_pCTaskCtrl->isGetLineAlpha());

		//��ʊO�Ȃ�폜����
		if(this->x <= LINE_LEFT_MAX || this->y >= HI_MAX || this->x >= LINE_RIGHT_MAX|| this->y <= m_g_pCTaskCtrl->isGetBorderLine())
		{
			Delete();
		}


		if(m_g_pCTaskCtrl->isGetLineAlpha() <= 0)
		{
			Delete();
		}

		//�L�[����
		Key();

		SetAlpha(m_alpha);
	}
};
/*======================================================

			����Key����

=======================================================*/
void Line::Key() {


	//D�������Ɛ������ׂď�����
	if(m_pDxi->isKeyTrigger(DIK_D) || m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
	{
		Delete();
	}
};
/*======================================================

			���̓����蔻��

=======================================================*/
void Line::Hit(CTaskFunc* task) {

	switch(task->m_iGroup)
	{
		//���ɓ���������
		case GROUP_EGG:
			EggHit(task);
			break;
		//���ɓ���������
		case GROUP_SMALLBIRD:
			break;
	}
};
/*=====================================================

	�ׂ荇���Ă�����̃`�F�[���̃|�C���^�̊i�[�֐�
	�����@�F�@����LINE�|�C���^�A�O��LINE�|�C���^

=======================================================*/
void  Line::Chain(Line* pLineNext ,Line* pLinePrev){

	//���̃u���b�N�|�C���^�̊i�[
	m_pLineNext = pLineNext;
	//�O�̃u���b�N�|�C���^�̊i�[
	m_pLinePrev = pLinePrev;
};
/*======================================================

			���Ɨ��̂�����

=======================================================*/
void  Line::EggHit(CTaskFunc* egg){

	if(this->y + this->coly > egg->y + egg->coly
		&& this->x > egg->x - egg->colx 
		&& this->x < egg->x + egg->colx)  
	{
			m_alpha -= 85;
			m_g_pCTaskCtrl->SetLineAlpha((FLOAT)m_alpha);
	}
};