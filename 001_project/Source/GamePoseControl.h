#include "TaskFuncs.h"
#include <math.h> 

/*========================================================

				ScoreControl

========================================================*/

class GamePoseControl {

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

public:

	//�R���X�g���N�^
	GamePoseControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt,SetSound* ps_Sound);
	//main�֐�
	void	main();
};

