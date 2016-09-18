#include "TaskFuncs.h"
#include <math.h> 
#include "ScoreControl.h"
#include "LifeControl.h"
#include "GamePoseControl.h"

/*========================================================

				GameSystemMain

========================================================*/

class GameSystem {


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

	//�N���b�N���ꂽ�ꏊ��ێ����Ă���
	LONG m_PushMpt_x;
	LONG m_PushMpt_y;
	//�N���b�N�������ꂽ���̏ꏊ��ێ����Ă���
	LONG m_Mpt_Release_x;
	LONG m_Mpt_Release_y;

	//���̒���
	LONG m_Line_Long;
	//���̐�
	LONG m_Line_count;

	//�ϐ�
	//�Q�[�����[�h�̕ێ�
	INT	m_iGamemode_Old ;

	//�^�X�N�𐶐����邩���Ȃ����̔��f
	BOOL m_bNewtask_flg ;

	//�}�E�X�̃��[�h -1���͂Ȃ��@0���͂͂��߁@1�������@2������
	INT m_iMousemode;
	//�t����(�A�[�N�^���W�F���g)���W�A��
	FLOAT m_arctan;
	//�X�R�A�Ǘ��N���X
	ScoreControl* m_pScore_Control;
	//�c�@�Ǘ��N���X
	LifeControl* m_pLife_Control;
	//�Q�[���̃|�[�Y�Ǘ��N���X
	GamePoseControl* m_pGamePose_Control;
	//�����N�����̔��f
	BOOL m_starting_flg;

	//�L�����N�^�[�̃J�E���g
	INT m_character_count;
	SoundFuncs* m_bgm ;
public:

	//�R���X�g���N�^
	GameSystem(DxInput* pDxi,CTaskCtrl* g_pCTaskCtrl,POINT* Mpt);
	//main�֐�
	void	main();
	//��ʂ̃R���g���[���֐�
	void	PictureCtrl();
	//�^�C�g���֐�
	void	TitleMain();
	//�Q�[���̃��C���֐�
	void	GameMain();
	//�Q�[���I�[�o�[
	void	GameOverMain();
	//�Q�[���N���A
	void	GameClearMain();
	//�}�E�X�̃V�X�e��
	void	MouseSystmMain();
	//����NEW����֐�
	void	LineNewSystem();
};

