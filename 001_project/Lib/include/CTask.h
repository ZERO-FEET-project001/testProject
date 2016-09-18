#pragma once
#include "stdafx.h"
#include "DxSprite.h"
#include "DxTexture.h"
#include "Define.h"

//-----------------------------------------------------------------------------
// m_dwTaskFlag
#define	TASK_FLAG_NONE		(0)			// ���������
#define	TASK_FLAG_USE		( 1 <<  0 )	// Task���q�[�v�G���A���g�p��
#define	TASK_FLAG_ENABLE	( 1 <<  1 )	// Task��������������
#define	TASK_FLAG_OBJECT	( 1 <<  2 )	// Object��\������
#define	TASK_FLAG_CLEAR		( 1 <<  3 )	// TASK����(�������g�̏���)
#define	TASK_FLAG_COL_ACT	( 1 <<  4 )	// Col�ɂ����ē����茳�i�e�Ȃǁj
#define	TASK_FLAG_COL_PSV	( 1 <<  5 )	// Col�ɂ����ē��Ă��鑤�i���@�A�G�Ȃǁj
#define	TASK_FLAG_HIT		( 1 <<  6 )	// Col�ɂ����ē�����ꂽ
#define	TASK_FLAG_NOMOVE	( 1 <<  7 )	// 1�t���[���ړ����Ȃ�
#define	TASK_FLAG_TEX		( 1 <<  8 )	// �e�N�X�`���[�̎��Ԃ�ۗL���Ă���
//-----------------------------------------------------------------------------

/*--------------------------------------------------------
	�^�X�N����N���X
--------------------------------------------------------*/
class CTaskCtrl
{
	
	INT		m_iGamemode ;		//���݂̃Q�[�����[�h��ێ�
	BOOL	m_bNewDownObject ;  //������������t���O
	FLOAT	m_fLineAlpha ;		//�����A���t�@
	BOOL	m_bLineTurn ;		//���̌����@TURE���E�オ��@FALSE���E������
	FLOAT	m_fLineRadian;		//���̃��W�A��
	INT		m_iLineCount;		//���̐�
	INT		m_iScore;			//�X�R�A(�f�[�^)
	INT		m_iScoreDisplay;	//�X�R�A(�\���p)
	INT		m_iLife;			//�c�@�̕ێ�
	BOOL	m_bGamePose;		//�Q�[���̃|�[�Y�t���O
	FLOAT	m_fBorderLine;		//���E��
	BOOL	m_bStartFlg;		//�X�^�[�g�t���O

	BYTE	*m_pbTaskHeap ;		// �q�[�v�G���A
	DWORD	m_dwMemSize ;		// �q�[�v�T�C�Y		
	BOOL	m_bDefrag ;			//

	DWORD	m_dwMSPF ;
	DWORD	m_dwFPS ;
	DWORD	m_dwTime ;
	DWORD	m_dwTimePrev ;
	DWORD	m_dwTimeNow ;
	DWORD	m_dwTimeOver ; 

	DxSprite*	m_pSprite ;

public:
	BYTE	*m_pbTop	;		// ��ԍŏ��Ɏ��s����^�X�N�̊i�[�|�C���^
	BYTE	*m_pbFree ;			// �q�[�v�G���A�̋󂢂Ă���擪�|�C���^
	DWORD	m_dwSize ;			// �g�p���̃q�[�v�T�C�Y
	DWORD	m_dwCount ;			// �g�p���̃^�X�N��

public:
	CTaskCtrl(DWORD dwMemSize,DWORD dwFPS = 60) ;
	~CTaskCtrl() ;

	void ClearTaskHeap(void) ;
	void main(void) ;
	void Defrag(void) ;

	HRESULT CreateSprite(DxWin* pDxw) ;
	HRESULT DrawAll();

	BOOL isSync() ;
	DWORD isTime() { return (m_dwTime) ; }	
	DWORD isTimeOver() { return (m_dwTimeOver) ; }	

	BYTE * isHeap() { return ( m_pbTaskHeap ) ; }
	DWORD isMemSize() { return ( m_dwMemSize ) ; }
	DWORD isUseSize() { return ( m_dwSize ) ; }
	DWORD isCount() { return ( m_dwCount ) ; }

	//�Q�[�����[�h��n��
	INT isGetGameMode() { return (m_iGamemode); }
	//�Q�[�����[�h���Z�b�g����
	VOID SetGameMode(INT gamemode);
	
	//�V�����I�u�W�F�N�g���Ƃ��t���O��n��
	BOOL isGetNewDownObject() { return (m_bNewDownObject); }
	//�V�����I�u�W�F�N�g���Ƃ��t���O���Z�b�g����
	VOID SetNewDownObject(BOOL downflg);

	//���A���t�@��n��
	FLOAT isGetLineAlpha() { return (m_fLineAlpha); }
	//���A���t�@���Z�b�g����
	VOID SetLineAlpha(FLOAT linealpha);

	//���̌�����n��
	BOOL isGetLineTurn() { return (m_bLineTurn); }
	//���̌������Z�b�g����
	VOID SetLineTurn(BOOL turnflg);

	//���̃��W�A����n��
	FLOAT isGetLineRadian() { return (m_fLineRadian); }
	//���̃��W�A�����Z�b�g����
	VOID SetLineDegree(FLOAT radian);

	//�X�R�A�i�\���p�j�𐔂�n��
	INT isGetScoreDisplay() { return (m_iScoreDisplay); }
	//�X�R�A�i�\���p�j���Z�b�g����
	VOID SetScoreDisplay(INT displayscore);

	//�X�R�A(�f�[�^)��n��
	INT isGetScore() { return (m_iScore); }
	//�X�R�A(�f�[�^)���Z�b�g����
	VOID SetScore(INT score);

	//�X�R�A������������
	VOID InitScore() ;
	VOID InitScoreDisplay();

	//�c�@���擾
	INT isGetLife(){ return (m_iLife); };
	//�c�@�̂����ƁiTRUE�����Z�AFALSE�����Z�j
	VOID SetLife(BOOL life);
	//�c�@�̏�����
	VOID InitLife();

	//�Q�[���̃|�[�Y�t���O��n��
	BOOL isGetGamePose() { return (m_bGamePose); }
	//�Q�[���̃|�[�Y�t���O���Z�b�g����
	VOID SetGamePose(BOOL poseflg);

	//���E����n��
	FLOAT isGetBorderLine() { return (m_fBorderLine); }
	//���E�����Z�b�g����
	VOID SetBorderLine(FLOAT borderline);

	//���̐���n��
	INT isGetLineCount() { return (m_iLineCount); }
	FLOAT isGetLinePoint(INT linecount);
	//���̐����Z�b�g����
	VOID SetLineCount(INT linecount);


	//�Q�[���X�^�[�g�t���O��n��
	BOOL isGetStartFlg() { return (m_bStartFlg); }
	//�Q�[���X�^�[�g�t���O���Z�b�g����
	VOID SetStartFlg(BOOL startflg);

	void  setDefrag() { m_bDefrag = TRUE ; }
	DxWin* isDxWin() { return ( m_pSprite->isDxWin() ) ; } 


};


/*--------------------------------------------------------
	�^�X�N�{�̃N���X
--------------------------------------------------------*/
class CTaskFunc {
	DWORD	m_dwTaskFlag;			// �^�X�N����p�t���O

public:
	static CTaskCtrl *m_spCTaskCtrl ;

	CTaskFunc*		m_pTaskPrev;	// �O�̃^�X�N�o�b�t�@�|�C���^
	CTaskFunc*		m_pTaskNext;	// ���̃^�X�N�o�b�t�@�|�C���^
	CTaskFunc*		m_pTaskParent;	// �e�^�X�N�o�b�t�@�|�C���^
	CTaskFunc*		m_pTaskChild;	// �q�^�X�N�o�b�t�@�|�C���^

	FLOAT	m_fPriority ;			// �^�X�N�̗D��x
	BYTE	m_iGroup ;				// �^�X�N�̃O���[�v�w��
	DWORD	m_dwSize ;				// �^�X�N�N���X�̃T�C�Y

	// ���W
	FLOAT	x ;
	FLOAT	y ;
	FLOAT	z ;						//0.0f ����Ԏ�O�A1.0f ����ԉ��B�j

	// �ړ���
	FLOAT	dx ;
	FLOAT	dy ;

	RECT	m_rect ;					//RECT

	// ������̑傫��
	FLOAT	colx ;
	FLOAT	coly ;

	INT	 m_alpha;

protected:
	char*	m_cpName ;				// �^�X�N�̖���

	DWORD  m_color ;				//�J���[

	FLOAT	m_rotate ;				// ��]
	D3DXVECTOR2	m_scale ;			// �g��k��

	//RECT�؂�ւ��悤�̕ϐ�
	INT m_iPtntimer_Max ;//RECT�؂�ւ����Ԃ̍ő�
	INT m_iPtntimer ;//RECT�̐؂�ւ�����
	INT m_iPtn ;//���݂̉摜�̃p�^�[���ԍ�
	INT m_iPtninit ;
	INT m_iPtn_Right_Max ;
	INT m_iPtn_Max ;//�ő�̉摜�̃p�^�[���ԍ�
	RECT m_rectSize ;//�ύXRECT
	FLOAT m_fPtn_x ;//�p�^�[���̍��WX
	FLOAT m_fPtn_y ;//�p�^�[���̍��WY
	BOOL m_bPtnLoopflg ;//
	BOOL m_bPtnRetunflg ;//

	//��ʈڍs�̍ۂ�NEW�̃J�E���g
	FLOAT m_fNew_Count;
	//��ʈڍs�̍ۂ�DELETE�̃J�E���g
	FLOAT m_fDelete_Count;
	//��ʈڍs�̍ۂ�NEW�̃t���O
	BOOL m_bNew_Flg;
	//��ʈڍs�̍ۂ�DELETE�̃t���O
	BOOL m_bDelete_Flg;
	//�������ǂ̎��ɏo�����邩�����邩�����Ă���
	INT m_iMode;

	DxTexture*	m_pDxT ;			// �e�N�X�`���[�i�[�|�C���^

public:
	void* operator new(size_t size, float priority=1.0f, int group = 0 );
	void operator delete(void *pTask, float priority,int group){} ;	// �x���΍�
    void operator delete(void *pTask);

	CTaskFunc() ;
	~CTaskFunc() ;
	void Delete() ;
	void DeleteGroup( int group ) ;
	void DeleteAll() ;

	virtual void main() = 0 ;
	void After() ;
	virtual void Hit(CTaskFunc* task) ;
	HRESULT Texture(LPCTSTR lpszFilename) { return ( Texture(lpszFilename, TRUE) ) ; }
	HRESULT Texture(LPCTSTR lpszFilename, BOOL bMode) ;
	void Draw( DxSprite* pSprite ) ;

	void SetPriority(float priority) ;
	void Link( CTaskFunc* pTaskParent, CTaskFunc* pTaskChild ) ;
	void LinkOff() ;
	void DeleteOwnChild() ;
	void DeleteOwnParent() ;
	void HitOwnChild() ;
	void HitOwnParent() ;

	BOOL isUse() ;
	void setTaskFlag( DWORD flag ) ; 
	void resetTaskFlag( DWORD flag ) ;
	BOOL isTaskFlag( DWORD flag ) ;
	DxTexture* TextureSet( );
	void GetTexture( DxTexture* g_tex );
	void SetRect(long left, long top, long right, long bottom);
	void SetAlpha();
	void SetAlpha(int a);
	void PtnChange();
	//�Q�[�����[�h�Ŏ������o�����邩�𔻒f����֐�
	void	ModeNew(CTaskCtrl* g_pCTaskCtrl ,BOOL dispflg);
	//�Q�[�����[�h�Ŏ����������邩�����Ȃ����𔻒f����֐�
	void	ModeDelete(CTaskCtrl* g_pCTaskCtrl );
};

