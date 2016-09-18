#include "GameSystem.h"

/*========================================================

			GameSystem
			�R���X�g���N�^

========================================================*/
GameSystem::GameSystem(DxInput *pDxi,CTaskCtrl*	g_pCTaskCtrl,POINT* Mpt){

	//�L�[�{�[�h�|�C���^�̕ێ�
	m_pDxi = pDxi ;
	//�^�X�N�R���g���[���̃|�C���^�̕ێ�
	m_g_pCTaskCtrl = g_pCTaskCtrl ;

	//�摜�̓ǂݍ���
	m_pt_Texture = new SetTexture();

	//�T�E���h
	m_ps_Sound = new SetSound();

	//�^�X�N�𐶐����邩���Ȃ����̃t���O
	m_bNewtask_flg = true ;

	//�}�E�X�̃��[�h�Z�b�g
	m_iMousemode = -1;

	//�}�E�X�|�C���^�̕ێ�
	m_Mpt = Mpt ;

	//�����N�����̔��f
	m_starting_flg = true;

	//�L�����N�^�[�̃J�E���g
	m_character_count = 0;

	m_iGamemode_Old = GAME_TITLE;
	//�X�R�A�Ǘ��N���X��NEW����
	m_pScore_Control = new ScoreControl(m_g_pCTaskCtrl , m_pt_Texture );
	//�c�@�Ǘ��N���X��NEW����
	m_pLife_Control = new LifeControl(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt,m_ps_Sound);
	//�Q�[���̃|�[�Y�Ǘ��N���X��NEW����
	m_pGamePose_Control = new GamePoseControl(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt,m_ps_Sound);
	m_bgm = NULL ;
};
/*========================================================

			GameSystemask
			���C���֐�
			�Q�[�����[�h�ɂ���ď�����ς�����
			�^�X�N�̎��s���s�����肷��

========================================================*/
void GameSystem::main(){

	//�Q�[�����[�h��ێ����Ă���
	m_iGamemode_Old = m_g_pCTaskCtrl->isGetGameMode();
	//�^�X�N�R���g���[������Q�[�����[�h�����炢
	//�ǂ̏����ɂ��邩�𔻒f����
	switch(m_g_pCTaskCtrl->isGetGameMode())
	{
		//�^�C�g��
		case GAME_TITLE:
			TitleMain();
			break;
		//���C������
		case GAME_MAIN:
			GameMain();
			break;
		//�Q�[���I�[�o�[
		case GAME_OVER:
			GameOverMain();
			break;	
	}

	// ���ׂẴ^�X�N�����s
	m_g_pCTaskCtrl->main() ;

	//���̎��ɃQ�[�����[�h���ύX�����ƃ^�X�N�̐����̃t���O��TRUE
	if(m_iGamemode_Old != m_g_pCTaskCtrl->isGetGameMode())
	{
		m_bNewtask_flg = true ;
		new Darken(m_g_pCTaskCtrl,m_pt_Texture ,m_pDxi);
	}
	
};
/*========================================================

			GameSystemask
			�^�C�g���֐�

========================================================*/
void GameSystem::TitleMain(){
	//MouseSystmMain();
	if(m_bNewtask_flg)
	{
		//NEW�͈��̂�
		m_bNewtask_flg = false ;
		if(m_starting_flg == false)
		{
			StopSound(BGM_MAIN);
			StopSound(BGM_GAMEOVER);
		}
		PlaySound(BGM_TITLE,TRUE);
		m_g_pCTaskCtrl->SetStartFlg(FALSE);
		new Cursor(m_pt_Texture ,m_g_pCTaskCtrl , m_Mpt, m_pDxi , GAME_TITLE , m_starting_flg,m_ps_Sound);
		new GameTitle(m_g_pCTaskCtrl , m_pt_Texture , m_pDxi , m_Mpt , m_starting_flg);
		m_starting_flg = false ;
	}
	m_character_count++;
	if(m_character_count >= 100)
	{
		m_character_count = 0;
		new CharacterTitle(m_pt_Texture , m_g_pCTaskCtrl,m_Mpt,m_pDxi,m_ps_Sound);
	}
};
/*========================================================

			GameSystemask
			�Q�[�����C���֐�

========================================================*/
void GameSystem::GameMain(){
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		MouseSystmMain();
	}
	if(m_bNewtask_flg)
	{ 
		m_character_count = 0;
		//NEW�͈��̂�
		m_bNewtask_flg = false ;
		StopSound(BGM_TITLE);
		PlaySound(BGM_MAIN,TRUE);
		//�w�i��NEW
		new Bg(m_pt_Texture , m_g_pCTaskCtrl);
		//���E��
		new BorderLine( m_g_pCTaskCtrl ,m_pt_Texture,m_ps_Sound);
		//���̑�
		new NibuAvis(m_pt_Texture , m_g_pCTaskCtrl,m_ps_Sound);
		//�X�^�[�g����
		new StartLetter(m_pt_Texture , m_g_pCTaskCtrl,m_ps_Sound);
		//�X�R�A�Ǘ��N���X�̏�����
		m_pScore_Control->Init();
		//�c�@�Ǘ��N���X�̏�����
		m_pLife_Control->Init();
	}
	//�X�R�A�Ǘ��N���X�̃��C��
	m_pScore_Control->main();
	//�c�@�Ǘ��N���X�̃��C��
	m_pLife_Control->main();
	//�Q�[���̃|�[�Y�Ǘ��N���X�̃��C��
	m_pGamePose_Control->main();
};
/*========================================================

			GameSystemask
			�Q�[���I�[�o�[�֐�

========================================================*/
void GameSystem::GameOverMain(){
	
	if(m_bNewtask_flg)
	{
		//NEW�͈��̂�
		m_bNewtask_flg = false ;
		StopSound(BGM_MAIN);
		PlaySound(BGM_GAMEOVER,TRUE);
		m_g_pCTaskCtrl->SetStartFlg(FALSE);
		new GameOver(m_g_pCTaskCtrl,m_pt_Texture ,m_pDxi,m_Mpt);
		m_pScore_Control->GameOverScoreDisplay();
	}
};

/*========================================================

			MouseSysytem
			�}�E�X�̃V�X�e���֐�

========================================================*/
void GameSystem::MouseSystmMain(){

	//�}�E�X�����߂ĉ����ꂽ��I
	if(	m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT) && m_iMousemode == MOUSE_NO ) 
	{
		//�}�E�X���[�h�̕ύX
		m_iMousemode = MOUSE_START;

		//�N���b�N���ꂽ�ꏊ��ێ����Ă���
		m_PushMpt_x = m_Mpt->x;
		m_PushMpt_y = m_Mpt->y;

		//���̎n�܂��NEW����
		new Line(m_pDxi,m_pt_Texture , m_g_pCTaskCtrl,m_PushMpt_x,m_PushMpt_y);
	}
	//�N���b�N�����ꂽ��
	else if(m_pDxi,m_pDxi->isMouseRelease(DXI_MOUSE_LEFT) && m_iMousemode == MOUSE_START)
	{
		//�}�E�X���[�h�̕ύX
		m_iMousemode++;
		//�N���b�N�������ꂽ���̏ꏊ��ێ����Ă���
		m_Mpt_Release_x = m_Mpt->x;
		m_Mpt_Release_y = m_Mpt->y;
		//���̃V�X�e�����Ăяo��
		LineNewSystem();
		//�}�E�X�̃��[�h��������
		m_iMousemode = MOUSE_NO;
	}
};
/*========================================================

			LineNewSystem
			����NEW����֐�

========================================================*/
void GameSystem::LineNewSystem(){

	//��_�̍��W�̒������o���B
	m_Line_Long = (LONG)(sqrt((float)((m_Mpt_Release_x - m_PushMpt_x)*(m_Mpt_Release_x - m_PushMpt_x) + (m_Mpt_Release_y - m_PushMpt_y)*(m_Mpt_Release_y - m_PushMpt_y))));
	//���̐����o���B
	m_Line_count = m_Line_Long  / LINE_WIDTH;

	//�����E�オ�肩�A�E�����肩���f����
	if(m_PushMpt_x < m_Mpt_Release_x && m_PushMpt_y > m_Mpt_Release_y || m_PushMpt_x > m_Mpt_Release_x && m_PushMpt_y < m_Mpt_Release_y)
	{
		//�E�オ��̐�
		m_g_pCTaskCtrl->SetLineTurn(true);
	}
	else
	{
		//�E������̐�
		m_g_pCTaskCtrl->SetLineTurn(false);
	}

	//���W�A�������߂邽��
	float rx = fabs( (float)(m_Mpt_Release_x - m_PushMpt_x) );
	float ry = fabs( (float)(m_Mpt_Release_y - m_PushMpt_y) );

	//���W�A�������߂�
	m_arctan = atan2f( ry , rx );

	//���W�A������̊p�x�̌v�Z
//	m_degree = m_arctan * M_TRIANGLE / M_PI;
	
	//�p�x��CTask�ɋ�����
	m_g_pCTaskCtrl->SetLineDegree(m_arctan);
	m_g_pCTaskCtrl->SetLineCount(m_Line_count);

	//����NEW���s���B
	for(int i=0 ; i < m_Line_count ; i++)
	{
		//�����g�p����NEW���s��
		new Line(m_pDxi,m_pt_Texture , m_g_pCTaskCtrl,(LONG)(m_PushMpt_x + (m_Mpt_Release_x - m_PushMpt_x) / m_Line_count * i),(LONG)(m_PushMpt_y + (m_Mpt_Release_y - m_PushMpt_y) / m_Line_count * i));
	}
};