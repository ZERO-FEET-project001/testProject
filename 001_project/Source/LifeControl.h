#include "TaskFuncs.h"
#include <math.h> 

/*========================================================

				ScoreControl

========================================================*/

class LifeControl {

	//�L�[�{�[�h�|�C���^�̕ێ�
	DxInput* m_pDxi;
	//�^�X�N�R���g���[���̃|�C���^�̕ێ�
	CTaskCtrl*	m_g_pCTaskCtrl;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	//�摜�p�|�C���^�̕ێ�
	SetTexture* m_pt_Texture ;
	//�}�E�X�̃|�C���^�[�Z�b�g
	POINT* m_Mpt;

	//�����݂̃X�R�A
	INT m_Life;

	

public:

	//�R���X�g���N�^
	LifeControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* m_pt_Texture,DxInput* pDxi,POINT* Mpt,SetSound* ps_Sound);
	//�������֐�
	void	Init();
	//main�֐�
	void	main();
};

