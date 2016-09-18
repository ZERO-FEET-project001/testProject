#pragma once
#include "CTask.h"
#include "DxInput.h"
#include "Define.h"	
#include "DxSound.h"
#include <math.h>

/*========================================================

				�T�E���h

========================================================*/
class SoundFuncs : public CTaskFunc {
	DxSound* m_pSound;
	BOOL m_stop_flg;
	BOOL m_loop_flg;
public:
	SoundFuncs(DxSound*);
	void main();
	void Play(bool loop);
	void Stop();
	void EnableDeleteByEnd();
	void ChangeSound(DxSound*);
};

class SetSound {

public:
	//BGM
	DxSound* m_title_bgm ;//�^�C�g��BGM
	DxSound* m_main_bgm ;//�Q�[�����C��BGM
	DxSound* m_gameover_bgm;//�Q�[���I�[�o�[BGM
	//SE
	DxSound* m_kotori_se ;//����SE
	DxSound* m_corsor_se ;//�J�[�\��SE
	DxSound* m_corsor_ok_se ;//�J�[�\�����艹SE
	DxSound* m_egg_se ;//��SE
	DxSound* m_eggbreak_se ;//�������SE
	DxSound* m_start_se ;//�X�^�[�gSE
	DxSound* m_in_se ;//����������SE
	DxSound* m_kotorihit_se ;//���������˕Ԃ��SE
	DxSound* m_batu_se ;//����������������SE
	DxSound* m_swing_se ;//���̑����h���SE

	SetSound();
	void main();
};


/*========================================================

				TextureTask

========================================================*/
class TextureFuncs : public CTaskFunc {

public:
	//�R���X�g���N�^
	TextureFuncs(LPCTSTR filename);
	//main�֐�
	void	main();

};

class SetTexture{

public:
	//�w�i
	TextureFuncs* m_pg_bg ;
	//��
	TextureFuncs* m_pg_line ;
	//���̑�
	TextureFuncs* m_pg_nibu ;
	//���̗�
	TextureFuncs* m_pg_egg ;
	//���̊k
	TextureFuncs* m_pg_eggshell ;
	//����
	TextureFuncs* m_pg_smallbird ;
	//���������̃|�C���g
	TextureFuncs* m_pg_point;
	//����
	TextureFuncs* m_pg_scorenumber;
	//�c�@
	TextureFuncs* m_pg_life;
	//�o�c
	TextureFuncs* m_pg_cross;
	//�|�[�Y
	TextureFuncs* m_pg_pose;
	//�J�[�\��
	TextureFuncs* m_pg_cursor;
	//�^�C�g��
	TextureFuncs* m_pg_title;
	//��
	TextureFuncs* m_pg_black;
	//���E��
	TextureFuncs* m_pg_border;
	//�Q�[���I�[�o�[
	TextureFuncs* m_pg_gameover;
	//����
	TextureFuncs* m_pg_char;
	TextureFuncs* m_pg_start;

	//�R���X�g���N�^
	SetTexture();
	//main�֐�
	void	main();

};

/*========================================================

				�w�i

========================================================*/
class Bg : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
public:
	//�R���X�g���N�^
	Bg(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl );
	//main�֐�
	void	main();

};
/*========================================================

				��

========================================================*/
class Line : public CTaskFunc {

	//�|�C���^�ێ�
	//�L�[�{�[�h�|�C���^�̕ێ�
	DxInput* m_pDxi;
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;

	//�ϐ�
	BOOL m_hit_egg;	//���Ɠ��������I
	//���̐��̃|�C���^
	Line* m_pLineNext;
	//�O�̃|�C���^
	Line* m_pLinePrev;


public:
	//�R���X�g���N�^
	Line(DxInput* pDxi,SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,LONG Mpt_x,LONG Mpt_y);
	//main�֐�
	void	main();
	//Key����
	void	Key();
	//�����蔻��
	void	Hit(CTaskFunc* task);
	//�|�C���^�[�ێ��֐�
	void	Chain(Line* pLineNext ,Line* pLinePrev);
	//
	void	EggHit(CTaskFunc* egg);

};
/*========================================================

				���̑�

========================================================*/
class NibuAvis : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	//�h�炷���h�炳�Ȃ���
	BOOL m_swing_flg ;
	//�h��Ă鎞�̃J�E���g������
	INT m_swing_count;
	//�h����X�^�[�g������J�E���g
	INT m_swing_start_count;
	//�E������
	BOOL m_swing_left_right_flg ;
	//�ړ��ʂ�ێ����Ă���
	FLOAT m_tmp_dx;


public:
	//�R���X�g���N�^
	NibuAvis(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound);
	//main�֐�
	void	main();
	//�h��֐�
	void	Swing();
	//����
	void	Move();
	//������֐�
	void	Hit(CTaskFunc* task);

};

/*========================================================

				���̗�

========================================================*/
class Egg : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	//�ϐ�
	BOOL m_hit_line;//���ɂ��������t���O
	BOOL m_hit_nibus;//���̑��ɂ������Ă�����I
	INT m_life;//���̃��C�t
	INT m_smallbird_count;//�����z��������J�E���g
	
	INT m_linecount;
public:
	//�R���X�g���N�^
	Egg(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y,SetSound* ps_Sound);
	//main�֐�
	void	main();
	//����
	void	Move();
	//���˕Ԃ�
	void	Spring();
	//�����蔻��
	void	Hit(CTaskFunc* task);
	//���Ɠ���������
	void	LineHit(CTaskFunc* line);
	//���̑��Ƃ̓����蔻��
	void	NibusHit(CTaskFunc* nibus);
	//���̋T��
	void	EggSplit();


};
/*========================================================

				���̊k

========================================================*/
class EggShell : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	
	//�ϐ�
	BOOL m_hit_line;//���ɂ��������t���O

public:
	//�R���X�g���N�^
	EggShell(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,float egg_x,float egg_y, int gamemode);
	//main�֐�
	void	main();
	//����
	void	Move();
	//���˕Ԃ�
	void	Spring();



};
/*========================================================

				����

========================================================*/
class SmallBird : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	//�ϐ�
	BOOL m_hit_line;//���ɂ��������t���O
	BOOL m_hit_nibus;//���̑��ɂ������Ă�����I
	BOOL m_fly_flg;//��ԃt���O
	INT  m_fly_start_count;//��ԃX�^�[�g�J�E���g
	INT  m_fly_end_count;//��ԏI���J�E���g
	
	INT m_linecount;
public:
	//�R���X�g���N�^
	SmallBird(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y,SetSound* ps_Sound);
	//main�֐�
	void	main();
	//����
	void	Move();
	//���˕Ԃ�
	void	Spring();
	//�����蔻��
	void	Hit(CTaskFunc* task);
	//���Ɠ���������
	void	LineHit(CTaskFunc* line);
	//���̑��Ƃ̓����蔻��
	void	NibusHit(CTaskFunc* nibus);
	//���
	void	Fly();
	//����
	void	Turn();


};
/*========================================================

				���̑����������̃|�C���g

========================================================*/
class InPoint : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	
public:
	//�R���X�g���N�^
	InPoint(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y, int line_count);
	//main�֐�
	void	main();
	void	Move();
};
/*========================================================

				�X�R�A

========================================================*/
class ScoreNumber : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	int m_kurai;//��
	int m_place;//�l


public:
	//�R���X�g���N�^;
	ScoreNumber(SetTexture* pt_Texture , int kurai , CTaskCtrl* g_pCTaskCtrl) ;
	//main�֐�
	void	main() ;
	//RECT�̕ύX
	void	ChangeRect();
};
/*========================================================

				�X�R�A

========================================================*/
class ScoreLetter : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;

	int m_kind ;
	bool m_move_flg;
	int m_move_count;


public:
	//�R���X�g���N�^;
	ScoreLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl , int kind) ;
	//main�֐�
	void	main() ;
	//RECT�̕ύX
	void	ChangeRect();
	//����
	void	Move();
};
/*========================================================

				�c�@

========================================================*/
class Life : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	
public:
	//�R���X�g���N�^
	Life(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,int kind);
	//main�֐�
	void	main();

};
/*========================================================

				�o�c

========================================================*/
class Cross : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;

public:
	//�R���X�g���N�^
	Cross(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,int kind,SetSound* ps_Sound);
	//main�֐�
	void	main();
};
/*========================================================

				�Q�[���̃|�[�Y

========================================================*/
class GamePose: public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//�L�[�{�[�h�|�C���^�̕ێ�
	DxInput* m_pDxi;
	//�}�E�X�̃|�C���^�[�Z�b�g
	POINT* m_Mpt;


public:
	//�R���X�g���N�^
	GamePose(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt);
	//main�֐�
	void	main();
};
/*========================================================

				�I�����̃J�[�\��

========================================================*/
class Cursor : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//�}�E�X�̃|�C���^�[�Z�b�g
	POINT* m_Mpt;
	DxInput* m_pDxi;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	INT m_kind;
	BOOL m_starting_flg;

public:
	//�R���X�g���N�^
	Cursor(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl ,POINT* Mpt , DxInput* pDxi , int kind, BOOL starting_flg,SetSound* ps_Sound);
	//main�֐�
	void	main();
	//�A�j���[�V�����֐�
	void	Animation();
	//�}�E�X�̍��W�ŃJ�[�\���̏ꏊ��ύX����֐�
	void	PointChange();
};
/*========================================================

				�Q�[���̃^�C�g��

========================================================*/
class GameTitle: public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//�L�[�{�[�h�|�C���^�̕ێ�
	DxInput* m_pDxi;
	//�}�E�X�̃|�C���^�[�Z�b�g
	POINT* m_Mpt;

	//�ϐ�
	BOOL m_starting_flg;

public:
	//�R���X�g���N�^
	GameTitle(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt , BOOL starting_flg );
	//main�֐�
	void	main();
	//�Q�[�����[�h��ύX����֐�
	void	ModeChange();

};
/*========================================================

				�Ó]

========================================================*/
class Darken: public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//�L�[�{�[�h�|�C���^�̕ێ�
	DxInput* m_pDxi;
	//�}�E�X�̃|�C���^�[�Z�b�g
	POINT* m_Mpt;

	//�ϐ�
	BOOL m_alpha_flg;
	INT m_alpha_count;
public:
	//�R���X�g���N�^
	Darken(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi);
	//main�֐�
	void	main();
};
/*========================================================

				�Q�[���I�[�o�[

========================================================*/
class GameOver: public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//�L�[�{�[�h�|�C���^�̕ێ�
	DxInput* m_pDxi;
	//�}�E�X�̃|�C���^�[�Z�b�g
	POINT* m_Mpt;
public:
	//�R���X�g���N�^
	GameOver(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt);
	//main�֐�
	void	main();
	//�Q�[�����[�h��ύX����֐�
	void	ModeChange();

};
/*========================================================

				���E��

========================================================*/
class BorderLine: public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	//�ϐ�
	FLOAT m_move_y;//�����W�̕ύX
	BOOL  m_move_flg;
	INT m_move_count;



public:
	//�R���X�g���N�^
	BorderLine(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture,SetSound* ps_Sound);
	//main�֐�
	void	main();
	//����
	void	Move();

};
/*========================================================

				GameOver�̎��̃X�R�A

========================================================*/
class GameScore : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	int m_kurai;//��
	int m_place;//�l


public:
	//�R���X�g���N�^;
	GameScore(SetTexture* pt_Texture , int kurai , CTaskCtrl* g_pCTaskCtrl) ;
	//main�֐�
	void	main() ;
	//RECT�̕ύX
	void	ChangeRect();
};
/*========================================================

				�X�R�A

========================================================*/
class CharLetter : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	int m_kind ;
	bool m_move_flg;
	int m_move_count;


public:
	//�R���X�g���N�^;
	CharLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound) ;
	//main�֐�
	void	main() ;
	//����
	void	Move();
};
/*========================================================

				����

========================================================*/
class CharacterTitle : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;

	POINT* m_Mpt;
	DxInput* m_pDxi;
	INT m_kind;
public:
	//�R���X�g���N�^
	CharacterTitle(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl,POINT* Mpt,DxInput *pDxi,SetSound* ps_Sound);
	//main�֐�
	void	main();
	//����
	void	Move();
	//�}�E�X�ŃN���b�N�����
	void	MouseHitBird();
	void	MouseHitEgg();

};
/*========================================================

				�X�^�[�g�̕���

========================================================*/
class StartLetter : public CTaskFunc {

	//�|�C���^�ێ�
	//�^�X�N�R���g���[���̃|�C���^
	CTaskCtrl* m_g_pCTaskCtrl ;
	//�摜�̃|�C���^
	SetTexture* m_pt_Texture ;
	//���y�p�|�C���^�̕ێ�
	SetSound* m_ps_Sound ;
	int m_kind ;
	bool m_move_flg;
	int m_move_count;
	int m_start_count;


public:
	//�R���X�g���N�^;
	StartLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound) ;
	//main�֐�
	void	main() ;
	//����
	void	Move();
	void	StartMove();
};