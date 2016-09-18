#include "TaskFuncs.h"
#include <math.h> 

/*========================================================

				ScoreControl

========================================================*/

class ScoreControl {

	//�^�X�N�R���g���[���̃|�C���^�̕ێ�
	CTaskCtrl*	m_g_pCTaskCtrl;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	//�摜�p�|�C���^�̕ێ�
	SetTexture* m_pt_Texture ;

	//�����݂̃X�R�A
	INT m_Score;
	//�X�R�A�ǉ������
	INT m_ScoreDisplay;


public:

	//�R���X�g���N�^
	ScoreControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* m_pt_Texture);
	//�������֐�
	void	Init();
	//main�֐�
	void	main();
	//GameOver����Display(�\��)
	void	GameOverScoreDisplay();
};

