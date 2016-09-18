#include "TaskFuncs.h"
/*========================================================

			Score�R���X�g���N�^

========================================================*/
ScoreNumber::ScoreNumber(SetTexture* pt_Texture ,int kurai , CTaskCtrl* g_pCTaskCtrl )
{
	// ����������
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME�ݒ�
	m_cpName = "Score" ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_scorenumber->TextureSet());

	//�ʂ̑��
	m_kurai = kurai;
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	//�������ǂ̂��炢�����v�Z����
	m_place = (  m_g_pCTaskCtrl->isGetScoreDisplay() / (int)( pow((float)COUNTER_PLACE,(float)m_kurai))) % COUNTER_PLACE ;

	//RECT�̎w��
	ChangeRect();

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_MAIN;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(0);

	//�X�R�A�����ʒu�̐ݒ�i�j
	this->x = (FLOAT)(COUNTER_X - kurai % COUNTER_MAX * COUNTER_GAP_X);
	this->y = COUNTER_Y ;
	this->z = COUNTER_Z ;

};
/*========================================================

			Score���C���֐�

========================================================*/
void ScoreNumber::main()
{
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);
	//�v�Z����
	m_place = ( m_g_pCTaskCtrl->isGetScoreDisplay() / (int)( pow((float)COUNTER_PLACE,(float)m_kurai))) % COUNTER_PLACE ;
	//RECT��ς���
	ChangeRect();

};
/*========================================================

			RECT�ύX�֐�

========================================================*/
void ScoreNumber::ChangeRect()
{
	switch(m_place)
	{
		case 0:
			SetRect(0,0,50,50);
			break;
		case 1:
			SetRect(50,0,100,50);
			break;
		case 2:
			SetRect(100,0,150,50);
			break;
		case 3:
			SetRect(150,0,200,50);
			break;
		case 4:
			SetRect(200,0,250,50);
			break;
		case 5:
			SetRect(250,0,300,50);
			break;
		case 6:
			SetRect(300,0,350,50);
			break;
		case 7:
			SetRect(350,0,400,50);
			break;
		case 8:
			SetRect(400,0,450,50);
			break;
		case 9:
			SetRect(450,0,500,50);
			break;
		default:
			break;
		
	}
};