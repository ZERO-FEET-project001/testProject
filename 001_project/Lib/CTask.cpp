#pragma comment( lib, "winmm.lib" ) // timeGetTime() �����N�w��
#include "CTask.h"
#include "Macro.h"

/*========================================================

					�^�X�N����

========================================================*/

/*--------------------------------------------------------

			�R���X�g���N�^�E�f�X�g���N�^

--------------------------------------------------------*/
CTaskCtrl::CTaskCtrl(DWORD dwMemSize, DWORD dwFPS) {

	m_pbTaskHeap = NULL ;				// �q�[�v�G���A
	m_dwMemSize = dwMemSize ;			// �q�[�v�T�C�Y
	m_dwSize = 0 ;						// �g�p���̃q�[�v�T�C�Y
	m_dwCount = 0 ;						// �g�p���̃^�X�N��
	m_bDefrag = FALSE ;

	// �q�[�v�̈�̊m��
	m_pbTaskHeap = (BYTE*)malloc(m_dwMemSize); 
	memset(m_pbTaskHeap,0,m_dwMemSize);
	m_pbTop = NULL ;//��ԏ��߂�Task
	ClearTaskHeap() ;//�q�[�v�G���A�̊J��

	// �t���[�����[�g����
	m_dwFPS = dwFPS ;
	m_dwMSPF = 1000 / (DWORD)dwFPS ;	//�P�t���[�����ԁi�~���b�j
	m_dwMSPF++ ;
	m_dwTimePrev = 0 ;
	m_dwTimeNow = 0 ;
	m_dwTimeOver = 0 ;

	CTaskFunc::m_spCTaskCtrl = this ;		// �^�X�N�̖{�̃N���X�ɐ���N���X��ʒm
	m_pSprite = NULL ;					// �X�v���C�g�N���X
}

CTaskCtrl::~CTaskCtrl() {

	if( m_pbTaskHeap == NULL ) return ;  // �^�X�N���X�g������������Ă��Ȃ�

	ClearTaskHeap() ;					// �q�[�v�̈�̃N���A

	// �������̉��
	free(m_pbTaskHeap) ;
	m_pbTaskHeap=NULL ;
}

/*--------------------------------------------------------

			�^�X�N�p�q�[�v�G���A�̉��

--------------------------------------------------------*/
void CTaskCtrl::ClearTaskHeap(void) {
	if( m_pbTaskHeap != NULL )
	{
		// �^�X�N���X�g������������Ă���
		CTaskFunc *task,*next;
		for( task = (CTaskFunc*)m_pbTop ; m_pbTop ; task = next )
		{
			next = (CTaskFunc*)task->m_pTaskNext ;
			if ( task->isUse() == TRUE )
			{ 
				delete task;
			}
		}
	}
	m_pbFree=m_pbTaskHeap ;
	m_pbTop = NULL ;
}
/*--------------------------------------------------------
			 �S�Ẵ^�X�N�����s
--------------------------------------------------------*/
void CTaskCtrl::main(void) {

	if( m_pbTaskHeap == NULL ) return ;	// �^�X�N���X�g������������Ă��Ȃ�

	// New�ł��Ȃ������H or �t���[�̃G���A�����Ȃ��H
	if ( m_bDefrag || ((DWORD)( m_dwMemSize - ( m_pbFree - m_pbTaskHeap ) ) <= ( (DWORD)(m_dwMemSize - m_dwSize ) / 8 )) ) 
	{ 
		Defrag() ;
		m_bDefrag = FALSE ; 
	}

	CTaskFunc *task,*next;
	for( task = (CTaskFunc*)m_pbTop ; m_pbTop ; task = next) 
	{
		BYTE *pbTop = m_pbTop ;

		// �^�X�N�̎��s�̗L�������𔻒f
		if( task->isTaskFlag( TASK_FLAG_ENABLE ) )
		{

			// �^�X�N�̃N���A�t���O�������Ă��Ȃ���Ύ��s
			// �������g�ȊO�̏����ŁA�N���A�t���O���Z�b�g����Ă���ꍇ���l��
			if ( !task->isTaskFlag( TASK_FLAG_CLEAR ) )
			{
				task->main() ;			// �^�X�N��main�����s
			}

			// �^�X�N�̏����̃`�F�b�N
			if ( task->isTaskFlag( TASK_FLAG_CLEAR ) )
			{
				// �^�X�N�̏���
				delete task  ;
				pbTop = m_pbTop ;
			}
			else 
			{
				// �^�X�N�̈ړ��E�R���W��������
				task->After() ;
			}
		}

 		next = task->m_pTaskNext;

		if( next == NULL) break ;
		if ( next == (CTaskFunc*)pbTop ) break ;	// �q�[�v�G���A�̍Ō�܂Ŏ��s������I��
	}

}

/*--------------------------------------------------------

		 �^�X�N���X�g�̃f�t���O

--------------------------------------------------------*/
void CTaskCtrl::Defrag(void) {

	if( m_pbTop == NULL )
	{
		// �g�p���̃^�X�N������
		m_pbFree = m_pbTaskHeap ;
		memset( m_pbTaskHeap,0, m_dwMemSize ) ;
		return ;
	}

	BYTE *dest=m_pbTaskHeap;

	CTaskFunc *task;
	DWORD size;

	task=(CTaskFunc*)m_pbTop;

	// �^�X�N���P�����Ȃ��Ƃ�
	if(task->m_pTaskNext == task)
	{
		size=task->m_dwSize ;

		memmove( m_pbTaskHeap, m_pbTop, size );

		task = (CTaskFunc*)m_pbTaskHeap ;
		task->m_pTaskPrev  = task ;
		task->m_pTaskNext = task ;

		m_pbTop = m_pbTaskHeap ;
		dest += size ;
	}
	// �^�X�N���������݂���Ƃ�
	else
	{
		for(BYTE *source=m_pbTaskHeap; source<m_pbFree; source+=size) 
		{
			task=(CTaskFunc*)source;
			size=task->m_dwSize;
			if(task->isUse() == FALSE) continue;

			if ( dest != source )
			{ 
				memmove(dest,source,size);				// �^�X�N�̃������C���[�W���ړ�

				// �^�X�N�̃����N�̒���ւ�
				task=(CTaskFunc*)dest;
				task->m_pTaskPrev->m_pTaskNext = task;
				task->m_pTaskNext->m_pTaskPrev = task;
		
				// �^�X�N�̐e�q�֌W�̒���ւ�
				if ( task->m_pTaskParent != NULL && task->m_pTaskParent != (CTaskFunc*)source)
				{
					CTaskFunc*	pOya ;
					pOya = (CTaskFunc*)task->m_pTaskParent ;
					while( pOya != NULL )
					{
						if( pOya->m_pTaskChild == (CTaskFunc*)source ) 
						{
							pOya->m_pTaskChild = task ;
							break;
						}
						pOya = pOya->m_pTaskChild;
					}
				}

				// �q�^�X�N�ɐe�̐V�����|�C���^��ʒm
				else if ( task->m_pTaskChild != NULL ) 
				{
					CTaskFunc*	pKo ;
					pKo = (CTaskFunc*)task->m_pTaskChild ;
					while( pKo != NULL )
					{
						pKo->m_pTaskParent = task ;
						pKo = pKo->m_pTaskChild;
					}
				}
			}
			// �ŏ��Ɏ��s����^�X�N���H
			if(source==m_pbTop) m_pbTop=dest;			
			dest+=size;
		}
	}

	memset(dest,0,m_pbFree-dest);		// ���g�p�ɂȂ����̈��������
	m_pbFree=dest;
}

/*--------------------------------------------------------

				 ��������

--------------------------------------------------------*/
BOOL CTaskCtrl::isSync() {

	m_dwTimeNow = ::timeGetTime();

	if ( m_dwTimeOver < m_dwMSPF )

		if ( m_dwTimeNow - m_dwTimePrev < m_dwMSPF - m_dwTimeOver ) return TRUE ;
		
	if ( m_dwTimePrev > 0 )
	{
		m_dwTime = m_dwTimeNow - m_dwTimePrev ;
		m_dwTimeOver += m_dwTimeNow - m_dwTimePrev - m_dwMSPF ;	//����鎞�Ԃ�����Ɏ����z��
		if ( m_dwTimeOver >= m_dwMSPF*2 ) m_dwTimeOver = m_dwMSPF*2 ;
	}
	m_dwTimePrev = ::timeGetTime();	//�������v���̋N�_

	return ( FALSE ) ;
}

/*--------------------------------------------------------

		 �X�v���C�g�f�o�C�X������

--------------------------------------------------------*/
HRESULT CTaskCtrl::CreateSprite(DxWin* pDxw) {
	m_pSprite = new DxSprite(pDxw) ;
	return m_pSprite->Create() ; 
}

/*--------------------------------------------------------

			 �S�Ẵ^�X�N��`��

--------------------------------------------------------*/
HRESULT CTaskCtrl::DrawAll() {
	HRESULT hr = S_FALSE;
	if( m_pSprite == NULL ) return( hr ) ;

	hr = m_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ; if (FAILED(hr)) return( hr ) ;	// �X�v���C�g�`��J�n

	CTaskFunc *task,*next;
	for( task = (CTaskFunc*)m_pbTop ; m_pbTop ; task = next ) 
	{

		task->Draw( m_pSprite ) ;

		next = (CTaskFunc*)task->m_pTaskNext ;
		if( next == (CTaskFunc*)m_pbTop ) break ;
	}

	m_pSprite->End() ;			// �X�v���C�g�`��I��
	return ( hr ) ;
}

/*========================================================

				�^�X�N�{��

========================================================*/

CTaskCtrl* CTaskFunc::m_spCTaskCtrl = NULL ;


/*--------------------------------------------------------

			 �^�X�N�̐����E�ǉ�

--------------------------------------------------------*/
void* CTaskFunc::operator new(size_t size, float priority, int group) {

	// �^�X�N���X�g������������Ă��Ȃ�
	if( m_spCTaskCtrl->isHeap() == NULL ) return NULL;  

	// �q�[�v�G���A�̊m�F
	if( m_spCTaskCtrl->m_pbFree + size >= m_spCTaskCtrl->isHeap() + m_spCTaskCtrl->isMemSize() ) 
	{
		// �q�[�v������Ȃ��̂Ńf�t���O
		if ( m_spCTaskCtrl->isMemSize() >= m_spCTaskCtrl->isUseSize() + size ) 
		{
			m_spCTaskCtrl->setDefrag() ;
		}
		return NULL ;
	}

	// �D��x�ɂ���āA�q�[�v�G���A���ǂꂾ���g�p�ł��邩�𐧌�����
	// �D��x1.0f�̎�100%���̃q�[�v�G���A���g�p�ł��A
	// 0.5f�̎��́A50%���̃q�[�v�G���A���g�p�ł���B
	if ( m_spCTaskCtrl->m_dwSize >= (DWORD)((float)m_spCTaskCtrl->isMemSize() * priority ) ) {
		return NULL ;		// �D��x�ɑ΂���q�[�v�G���A�s��
	}

	m_spCTaskCtrl->m_dwSize += (DWORD)size;//work�G���A�̊Ǘ�
	m_spCTaskCtrl->m_dwCount++ ;

    CTaskFunc *new_task = (CTaskFunc*)m_spCTaskCtrl->m_pbFree ;
    m_spCTaskCtrl->m_pbFree += size;

	if(m_spCTaskCtrl->m_pbTop == NULL) 
	{
		// ���݃^�X�N���X�g�͋�
		m_spCTaskCtrl->m_pbTop = (BYTE*)new_task;

		//task�̑O��֌W�̊Ǘ�
		new_task->setTaskFlag( TASK_FLAG_USE ) ;
		new_task->m_dwSize	= (DWORD)size;
		new_task->m_pTaskPrev	= new_task;
		new_task->m_pTaskNext	= new_task;

		new_task->m_fPriority = priority;
		new_task->m_iGroup = group;
		new_task->m_rect.bottom = 0;
		new_task->m_rect.top = 0;
		new_task->m_rect.left = 0;
		new_task->m_rect.right = 0;

		return new_task;
	}

    // �^�X�N���X�g�ɑ}������
    CTaskFunc *task,*next;
    for( task = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ; ; task = next )
	{
        next = task->m_pTaskNext ;
		// �^�X�N�̗D��x���`�F�b�N�i!�D��x�������ƁA�\���͉��ɂȂ�j
		if( priority > task->m_fPriority )
		{
			// �D��x�������ꍇ�́A�擪�ɑ}��
			if( task == (CTaskFunc*)m_spCTaskCtrl->m_pbTop )
			{
                m_spCTaskCtrl->m_pbTop = (BYTE*)new_task ;
            }
            new_task->m_pTaskPrev = task->m_pTaskPrev;
            new_task->m_pTaskNext = task;
            break;
        }
		else if( next == (CTaskFunc*)m_spCTaskCtrl->m_pbTop ) 
		{
			// �D��x���Ⴂor�����ꍇ�́A�����ɑ}��
			new_task->m_pTaskPrev = task;
			new_task->m_pTaskNext = next;
			break;
		}
	}

	new_task->setTaskFlag( TASK_FLAG_USE ) ;
	new_task->m_dwSize		= (DWORD)size;
	new_task->m_fPriority	= priority;
	new_task->m_iGroup		= group;

 	new_task->m_pTaskPrev->m_pTaskNext = new_task;
	new_task->m_pTaskNext->m_pTaskPrev = new_task;

    return new_task;
}

/*--------------------------------------------------------

			 �^�X�N�̍폜

--------------------------------------------------------*/
void CTaskFunc::operator delete(void *pTask)
{
	if( m_spCTaskCtrl->isHeap()==NULL ) return;
	CTaskFunc *task=(CTaskFunc*)pTask;

	// �����̃G���A�͍폜���Ȃ�
	if( task->isTaskFlag( TASK_FLAG_USE ) == FALSE) return ;	
	task->resetTaskFlag( TASK_FLAG_USE ) ;
	
	// ���ۂ̃f�X�g���N�g�́A�e�I�u�W�F�N�g�s���A�q�[�v�̑���̂ݍs���B
	// �^�X�N�́um_pTaskPrev�v�ێ����邽�߂ɕϐ��̃N���A�͍s��Ȃ��B
	m_spCTaskCtrl->m_dwSize -= task->m_dwSize;
	m_spCTaskCtrl->m_dwCount--;

	// �ŏ��Ɏ��s����^�X�N���H
	if( task == (CTaskFunc*)m_spCTaskCtrl->m_pbTop ) 
	{
		// �Ō�̃^�X�N���H
		if( task->m_pTaskNext == (CTaskFunc*)m_spCTaskCtrl->m_pbTop ) 
		{
			m_spCTaskCtrl->m_pbTop = NULL;
			return;
		}
		else m_spCTaskCtrl->m_pbTop = (BYTE*)task->m_pTaskNext ;
	}

	// �^�X�N�̎��s���Ԃ��Ȃ�����
	task->m_pTaskPrev->m_pTaskNext = task->m_pTaskNext ;
	task->m_pTaskNext->m_pTaskPrev = task->m_pTaskPrev ;

	// �^�X�N�̐e�q�֌W���Ȃ�����
	if ( task->m_pTaskParent != NULL || task->m_pTaskChild != NULL ) { task->LinkOff() ; }
}

/*--------------------------------------------------------

		�R���X�g���N�^�E�f�X�g���N�^

--------------------------------------------------------*/
CTaskFunc::CTaskFunc() {
	m_pTaskParent = NULL ;	// �e�^�X�N�o�b�t�@�|�C���^
	m_pTaskChild = NULL ;		// �q�^�X�N�o�b�t�@�|�C���^


	setTaskFlag( TASK_FLAG_ENABLE ) ;
	m_cpName = "" ;

	x = 0.0f ;
	y = 0.0f ;
	z = 0.5f ;
	dx = 0.0f ;
	dy = 0.0f ;

	colx = 0.0f;
	coly = 0.0f ;

	m_rotate = 0.0f;
	m_scale = D3DXVECTOR2(1.0f,1.0f) ;
	m_alpha = 0;

	m_rectSize.left = 0;
	m_rectSize.top = 0;
	m_rectSize.right = 0;
	m_rectSize.bottom = 0 ;

	m_bPtnRetunflg = true ;

	m_fPtn_x = 0;
	m_iPtninit = 0;
	m_fPtn_y = 0;
	m_iPtntimer = 0 ;
	m_iPtn = 0 ;
	m_iPtninit = 0 ;

	m_pDxT = NULL ;
}
CTaskFunc::~CTaskFunc() {

	// �q�[�v�G���A�g�p���̃t���O�݂̂��c���A���̓N���A����A
	resetTaskFlag( ~TASK_FLAG_USE ) ;	
	if(isTaskFlag(TASK_FLAG_TEX))
	{
		_DELETE(m_pDxT) ;
	}
}
/*--------------------------------------------------------

		 �e�N�X�`���[�̓ǂݍ���

--------------------------------------------------------*/
HRESULT CTaskFunc::Texture(LPCTSTR lpszFilename, BOOL bMode) {

	HRESULT hr;

	_DELETE( m_pDxT ) ;

	m_pDxT = new DxTexture( m_spCTaskCtrl->isDxWin() ) ;
	hr = m_pDxT->Load(lpszFilename) ;

	setTaskFlag( TASK_FLAG_TEX ) ; 

	return (hr) ;
}

/*--------------------------------------------------------

		 �^�X�N�̃I�u�W�F�N�g�\��

--------------------------------------------------------*/
void CTaskFunc::Draw( DxSprite* pSprite ) {
	// Object�̕\��
	if ( isTaskFlag( TASK_FLAG_ENABLE | TASK_FLAG_OBJECT ) && m_pDxT != NULL ) 
	{
		if(m_rect.bottom == m_rect.top || m_rect.left == m_rect.right)
		{
			// �`��
			pSprite->Draw(m_pDxT,&D3DXVECTOR3(x,y,z),&m_scale,m_rotate);
		}
		else
		{
			// �`��
			pSprite->Draw(m_pDxT,&D3DXVECTOR3(x,y,z),&m_scale,m_rotate,&m_rect,m_color);
		}
	}
}

/*--------------------------------------------------------

		 �^�X�N�̌㏈����

--------------------------------------------------------*/
void CTaskFunc::After(){

	if ( isTaskFlag( TASK_FLAG_ENABLE ) )
	{
		// �ړ�����
		if ( isTaskFlag( TASK_FLAG_NOMOVE ) )
		{
			resetTaskFlag( TASK_FLAG_NOMOVE ) ;
		}
		else 
		{
			x += dx ;
			y += dy ;
		}

		// �R���W��������
		// �@�����O���[�v���m�̓�����͔��肵�Ȃ��d�l�ɂȂ��Ă���
		if ( isTaskFlag( TASK_FLAG_COL_ACT ) ) 
		{
			CTaskFunc *task,*next=NULL;
			for( task = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
				next != (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
				task = next ) 
			{
				next = (CTaskFunc*)task->m_pTaskNext ;
				// ��r�̑O��́A���ʂŊ���I�̂悢�ၫ
				if ( ( task->m_dwTaskFlag					// ���҂Ƃ��R���W�����̑Ώۂ��H
						& ( TASK_FLAG_ENABLE | TASK_FLAG_COL_PSV | TASK_FLAG_CLEAR | TASK_FLAG_HIT ) )
					!= ( TASK_FLAG_ENABLE | TASK_FLAG_COL_PSV ) ) { continue ; }

				if ( this == task ) continue;				// �������g�łȂ����H
				if ( m_iGroup == task->m_iGroup ) continue;	// �ʂ̃O���[�v���H
				if ( task->colx == 0						// �R���W�����̃T�C�Y�͗L�邩�H
					|| task->coly == 0 ) continue ;		

				if ( task->x - task->colx <= x + colx
					&& task->x + task->colx >= x - colx
					&& task->y - task->coly <= y + coly
					&& task->y + task->coly >= y - coly 
				) {
// C�ŏ�������Ȃ�A�t���O�𗧂ĂāA�e�֐��Ńt���O�̓��e�ɉ���������������
// task->m_dwTaskFlag |= TASK_FLAG_HIT ;
// m_dwTaskFlag |= TASK_FLAG_HIT ;
					task->Hit(this) ;	// ����̓����菈��
					Hit(task) ;			// ���g�̓����菈��

					// ���g�̓�����t���O�����Ă���΁A���[�v���I������
					if ( task->isTaskFlag( TASK_FLAG_HIT ) ) break ;
				}
			}
		}
	}
}
/*-----------------------------------------------------------------------------

				�^�X�N�̍폜

-----------------------------------------------------------------------------*/
void CTaskFunc::Delete() {

	setTaskFlag( TASK_FLAG_CLEAR ) ;

	// �������e�̏ꍇ�́A�q�Ƃ̃����N���폜����
	if ( m_pTaskParent == NULL && m_pTaskChild != NULL )
	{
		CTaskFunc*	pKo ;
		pKo = (CTaskFunc*)m_pTaskChild ;
		while( pKo != NULL )
		{
			pKo->m_pTaskParent = NULL ;
			pKo->m_pTaskChild = NULL ;
			pKo = pKo->m_pTaskChild;
		}
	}
}

/*-----------------------------------------------------------------------------

				 �^�X�N�̍폜(�O���[�v�P��)]

-----------------------------------------------------------------------------*/
void CTaskFunc::DeleteGroup( int group ) {
	CTaskFunc *task,*next=NULL;
	for( task = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ; 
		next != (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
		task = next )
	{
		next = (CTaskFunc*)task->m_pTaskNext ;
		
		if ( task->m_iGroup == group )
		{ 
			task->Delete() ;
		}
	}
}

/*-----------------------------------------------------------------------------

			 �S�^�X�N�̍폜

-----------------------------------------------------------------------------*/
void CTaskFunc::DeleteAll() {
	CTaskFunc *task,*next=NULL;
	for( task = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ; 
		next != (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
		task = next ) 
	{
		next = (CTaskFunc*)task->m_pTaskNext ;

		task->Delete() ;
	}
}

/*-----------------------------------------------------------------------------

			 �^�X�N�̏Փˏ���(�p���N���X�ɒ�`�������ꍇ�́A�t���O�𗧂Ă�j

-----------------------------------------------------------------------------*/
void CTaskFunc::Hit(CTaskFunc* task){

	setTaskFlag( TASK_FLAG_HIT ) ;

}
/*-----------------------------------------------------------------------------

			 �^�X�N�t���O�̐���

-----------------------------------------------------------------------------*/
void CTaskFunc::setTaskFlag( DWORD flag ) { 

	m_dwTaskFlag |= flag ; 
}

void CTaskFunc::resetTaskFlag( DWORD flag ) { m_dwTaskFlag &= ~flag ; }

BOOL CTaskFunc::isTaskFlag( DWORD flag ) { 
	if ( flag == ( m_dwTaskFlag & flag ) ) { return TRUE ; }
	else { return FALSE ; }
}
BOOL CTaskFunc::isUse() { return isTaskFlag (TASK_FLAG_USE) ; }

/*-----------------------------------------------------------------------------
			�D��x�̕ύX
-----------------------------------------------------------------------------*/
void CTaskFunc::SetPriority(float priority)
{
	m_fPriority=priority;

	// �^�X�N���X�g���珜�O����
	if( this == (CTaskFunc*)m_spCTaskCtrl->m_pbTop )
	{	
		// �ŏ��Ɏ��s����^�X�N���H
		if( m_pTaskNext == (CTaskFunc*)m_spCTaskCtrl->m_pbTop) return;		// �B��̃^�X�N���H
		m_spCTaskCtrl->m_pbTop = (BYTE*)m_pTaskPrev;
	}
	m_pTaskPrev->m_pTaskNext = m_pTaskNext ;
	m_pTaskNext->m_pTaskPrev = m_pTaskPrev ;

	// �^�X�N���X�g�ɑ}������

	CTaskFunc *active = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
	CTaskFunc *task, *next;
	for( task = active ;; task = next ) 
	{
		next=task->m_pTaskNext;

		// �^�X�N�̗D��x���`�F�b�N�i!�D��x�������ƁA�\���͉��ɂȂ�j
		if( priority > task->m_fPriority )	
		{
			// �D��x�������ꍇ�́A�擪�ɑ}��
			if( task == (CTaskFunc*)m_spCTaskCtrl->m_pbTop ) 
			{
				m_spCTaskCtrl->m_pbTop = (BYTE*)this;
			}
			m_pTaskPrev = task->m_pTaskPrev;
			m_pTaskNext = task;
			break;
		}
		else if( next == active ) 
		{
			// �D��x���Ⴂor�����ꍇ�́A�����ɑ}��
			m_pTaskPrev = task;
			m_pTaskNext = next;
			break;
		}
	}

	m_pTaskPrev->m_pTaskNext = this;
	m_pTaskNext->m_pTaskPrev = this;

	// �ŏ��Ɏ��s����^�X�N���w���|�C���^���Đݒ�
	if( priority > active->m_fPriority ) m_spCTaskCtrl->m_pbTop = (BYTE*)this ;
}

/*-----------------------------------------------------------------------------

			 �^�X�N�̃����N

-----------------------------------------------------------------------------*/
void CTaskFunc::Link( CTaskFunc* pTaskParent, CTaskFunc* pTaskChild ) {
	CTaskFunc*	pTask;
	if ( pTaskParent == NULL || pTaskChild == NULL ) { return ; }

	//-----------------------------------------------------
	for( pTask = pTaskParent; pTask->m_pTaskChild != NULL; pTask = pTask->m_pTaskChild ){}
	pTask->m_pTaskChild = pTaskChild;

	//-----------------------------------------------------
	for( pTask = pTaskChild; pTask->m_pTaskParent != NULL; pTask = pTask->m_pTaskParent ){}
	pTask->m_pTaskParent = pTaskParent;
}

/*-----------------------------------------------------------------------------

			�^�X�N�̃����N���玩�����͂���

-----------------------------------------------------------------------------*/
void CTaskFunc::LinkOff() {
	CTaskFunc*	pOya;
	CTaskFunc*	pKo;

	//-----------------------------------------------------
	pOya = m_pTaskParent;
	while( pOya != NULL )
	{
		if( pOya->m_pTaskChild == this )
		{
			pOya->m_pTaskChild = m_pTaskChild;
			break;
		}
		pOya = pOya->m_pTaskChild;
	}

	//-----------------------------------------------------
	pKo = m_pTaskChild;
	while( pKo != NULL )
	{
		//LinkOff���e�̏ꍇ���ׂĂ̂��̐e������������
		if( pKo->m_pTaskParent == this || m_pTaskParent == NULL )
		{
			pOya = m_pTaskChild;
			while( pOya != NULL)
			{
				pOya->m_pTaskParent = m_pTaskChild;
				pOya = pOya->m_pTaskChild;
			}
		}
		//LinkOff���q�̏ꍇ
		else
		{
			pKo->m_pTaskParent = m_pTaskParent;
		}
		break;

		if(pKo == pKo->m_pTaskParent) { break; }
		else { pKo = pKo->m_pTaskParent; }
	}
}
/*-----------------------------------------------------------------------------

			 �q�^�X�N�̍폜

-----------------------------------------------------------------------------*/
void CTaskFunc::DeleteOwnChild() {
	while( m_pTaskChild != NULL ) 
	{
		CTaskFunc* p = m_pTaskChild;
		m_pTaskChild = m_pTaskChild->m_pTaskChild;

		if( m_pTaskChild != NULL ) 
		{
			m_pTaskChild->m_pTaskParent = this ;
		}
		p->Delete() ;
	}
}
/*-----------------------------------------------------------------------------

			 �q�^�X�N�̓�����

-----------------------------------------------------------------------------*/
void CTaskFunc::HitOwnChild() {
	while( m_pTaskChild != NULL ) 
	{
		CTaskFunc* p = m_pTaskChild;
		m_pTaskChild = m_pTaskChild->m_pTaskChild;

		if( m_pTaskChild != NULL ) 
		{
			m_pTaskChild->m_pTaskParent = this ;
		}
		if ( !(p->isTaskFlag( TASK_FLAG_HIT )) ) 
		{ 
			p->Hit(this) ;
		}
	}
}
/*-----------------------------------------------------------------------------

			 �e�^�X�N�̍폜

-----------------------------------------------------------------------------*/
void CTaskFunc::DeleteOwnParent() {
	if( m_pTaskParent != NULL ) 
	{
		CTaskFunc* p = m_pTaskParent;
		m_pTaskParent = m_pTaskParent->m_pTaskParent;
		if( m_pTaskParent != NULL )
		{
			m_pTaskParent->m_pTaskChild = this ;
		}
		p->Delete() ;
	}
}
/*-----------------------------------------------------------------------------

			 �e�^�X�N�̓�����
			 
-----------------------------------------------------------------------------*/
void CTaskFunc::HitOwnParent() {
	if( m_pTaskParent != NULL )
	{
		CTaskFunc* p = m_pTaskParent;
		if ( !p->isTaskFlag(TASK_FLAG_HIT) ) 
		{
			m_pTaskParent = m_pTaskParent->m_pTaskParent;
			if( m_pTaskParent != NULL ) 
			{
				m_pTaskParent->m_pTaskChild = this ;
			}
			p->Hit(this) ;
		}
	}
}
/*--------------------------------------------------------
// �e�N�X�`���[�̃f�[�^�̃Z�b�g
--------------------------------------------------------*/
DxTexture* CTaskFunc::GetTexture( ){

	return m_pDxT;

}
/*--------------------------------------------------------
// �e�N�X�`���[�̃f�[�^�̃Z�b�g
--------------------------------------------------------*/
void CTaskFunc::SetTexture( DxTexture* g_tex){
	if(g_tex)
	{
		m_pDxT = new DxTexture(m_spCTaskCtrl->isDxWin());
		*m_pDxT = *g_tex;
	}
};
/*--------------------------------------------------------
// rect���Z�b�g����֐�
--------------------------------------------------------*/
void CTaskFunc::SetRect(long left, long top, long right, long bottom){
	m_rect.left = left;
	m_rect.top = top;
	m_rect.right = right;
	m_rect.bottom = bottom;
	m_pDxT->SetCenter(m_rect);
}

/*=======================================================================
	�J���[�Z�b�g�֐�
	�߂�l�Fture or false
			����������-true�@���s-false
	�����F�ԍ��@�A���t�@�l�@�ԁ@�΁@��
==========================================================================*/
void CTaskFunc::SetAlpha()
{
	m_color = D3DCOLOR_ARGB(255,255,255,255);
}
/*=======================================================================
	�J���[�Z�b�g�֐�
	�߂�l�Fture or false
			����������-true�@���s-false
	�����F�ԍ��@�A���t�@�l�@�ԁ@�΁@��
==========================================================================*/
void CTaskFunc::SetAlpha(int a)
{
	m_color = D3DCOLOR_ARGB(a,255,255,255);
}
/*=======================================================================
	�p�^�[���ύX�֐�
	�߂�l�F�Ȃ�
	�����F�Ȃ�
==========================================================================*/
void CTaskFunc::PtnChange()
{
	//RECT�̐؂�ւ����ԑ����Ă��[
	m_iPtntimer++;
	//���[�v�t���OTRUE�̎�
	if(m_bPtnLoopflg)
	{

		//�p�^�[����MAX��菭�Ȃ���
		if(m_iPtntimer >= m_iPtntimer_Max)
		{
			//RECT�̐؂�ւ�����0�ɂ���
			m_iPtntimer = 0;
			//�E��RECT���E�E�E
			if(m_bPtnRetunflg)
			{
				//�p�^�[���ύX
				m_iPtn++;
				//RECT�̕ύX
				m_rect.left   += m_rectSize.right;
				m_rect.top    += m_rectSize.bottom;
				m_rect.right  += m_rectSize.right;
				m_rect.bottom += m_rectSize.bottom ;
				//�p�^�[��MAX�ɂȂ�����
				if(m_iPtn == m_iPtn_Max)
				{
					//�ւ��܂�
					m_bPtnRetunflg = false;
				}
			}
			//����RECT��
			else
			{
				//RECT�̐؂�ւ�����0�ɂ���
				m_iPtntimer = 0;
				//�p�^�[���ύX
				m_iPtn--;
				//RECT�ύX
				m_rect.left   -= m_rectSize.right;
				m_rect.top    -= m_rectSize.bottom;
				m_rect.right  -= m_rectSize.right;
				m_rect.bottom -= m_rectSize.bottom ;
				//�p�^�[�����O�ɂȂ�����
				if(m_iPtn == m_iPtninit)
				{
					//�Đ��t���O
					m_bPtnRetunflg = true;
				}
			}
		}

	}
	//FALSE
	else
	{
		//�p�^�[����MAX��菭�Ȃ���
		if(m_iPtntimer == m_iPtntimer_Max)
		{
			//RECT�̐؂�ւ�����0�ɂ���
			m_iPtntimer = 0;
			//�p�^�[���ύX
			m_iPtn++;
			
			//RECT�ύX
			m_rect.left   += m_rectSize.right;
			m_rect.right  += m_rectSize.right;

			//�p�^�[����MAX�ɂȂ�����
			if(m_iPtn % m_iPtn_Right_Max == 0)
			{
				//RECT�ύX
				m_rect.left   = (m_rectSize.right * m_iPtninit);
				m_rect.right  = (m_rectSize.right * (m_iPtninit+1)) ;
				m_rect.top   += m_rectSize.bottom;
				m_rect.bottom  += m_rectSize.bottom;
			}
			if(m_iPtn == m_iPtn_Max)
			{
				m_iPtn = m_iPtninit;
				//�E�̕ύX�摜�̎�
				if(m_rectSize.right != 0)
				{
					m_rect.left   = (m_rectSize.right * m_iPtninit);
					m_rect.right  = (m_rectSize.right * (m_iPtninit+1)) ;
				}
				//���̕ύX�摜�̎�
				if(m_rectSize.bottom != 0)
				{
					m_rect.top    = (m_rectSize.bottom * m_iPtninit);
					m_rect.bottom =  (m_rectSize.bottom * (m_iPtninit+1)) ;
				}
			}
		}
	}

	SetRect(m_rect.left,m_rect.top,m_rect.right,m_rect.bottom);
};