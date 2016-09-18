#include "TaskFuncs.h"
/*========================================================

			GameOver�̎��̃X�R�A�R���X�g���N�^

========================================================*/
GameScore::GameScore(SetTexture* pt_Texture ,int kurai , CTaskCtrl* g_pCTaskCtrl )
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
	m_place = (  m_g_pCTaskCtrl->isGetScore() / (int)( pow((float)GAMEOVER_SCORE_PLACE,(float)m_kurai))) % GAMEOVER_SCORE_PLACE ;

	//RECT�̎w��
	ChangeRect();

	//���������݂���Q�[�����[�h�̐ݒ�
	m_iMode = GAME_OVER;

	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(0);

	m_scale = D3DXVECTOR2(2.0f,2.0f) ;

	//�X�R�A�����ʒu�̐ݒ�i�j
	this->x = (FLOAT)(GAMEOVER_SCORE_X - kurai % GAMEOVER_SCORE_MAX * GAMEOVER_SCORE_GAP_X);
	this->y = GAMEOVER_SCORE_Y ;
	this->z = GAMEOVER_SCORE_Z ;

};
/*========================================================

			GameOver�̎��̃X�R�A���C���֐�

========================================================*/
void GameScore::main()
{
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);

};
/*========================================================

			RECT�ύX�֐�

========================================================*/
void GameScore::ChangeRect()
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