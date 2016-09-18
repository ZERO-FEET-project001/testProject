#pragma comment( lib, "winmm.lib" ) // timeGetTime() リンク指定
#include "CTask.h"
#include "Macro.h"

/*========================================================

					タスク制御

========================================================*/

/*--------------------------------------------------------

			コンストラクタ・デストラクタ

--------------------------------------------------------*/
CTaskCtrl::CTaskCtrl(DWORD dwMemSize, DWORD dwFPS) {

	m_pbTaskHeap = NULL ;				// ヒープエリア
	m_dwMemSize = dwMemSize ;			// ヒープサイズ
	m_dwSize = 0 ;						// 使用中のヒープサイズ
	m_dwCount = 0 ;						// 使用中のタスク数
	m_bDefrag = FALSE ;

	// ヒープ領域の確保
	m_pbTaskHeap = (BYTE*)malloc(m_dwMemSize); 
	memset(m_pbTaskHeap,0,m_dwMemSize);
	m_pbTop = NULL ;//一番初めのTask
	ClearTaskHeap() ;//ヒープエリアの開放

	// フレームレート制御
	m_dwFPS = dwFPS ;
	m_dwMSPF = 1000 / (DWORD)dwFPS ;	//１フレーム時間（ミリ秒）
	m_dwMSPF++ ;
	m_dwTimePrev = 0 ;
	m_dwTimeNow = 0 ;
	m_dwTimeOver = 0 ;

	CTaskFunc::m_spCTaskCtrl = this ;		// タスクの本体クラスに制御クラスを通知
	m_pSprite = NULL ;					// スプライトクラス
}

CTaskCtrl::~CTaskCtrl() {

	if( m_pbTaskHeap == NULL ) return ;  // タスクリストが初期化されていない

	ClearTaskHeap() ;					// ヒープ領域のクリア

	// メモリの解放
	free(m_pbTaskHeap) ;
	m_pbTaskHeap=NULL ;
}

/*--------------------------------------------------------

			タスク用ヒープエリアの解放

--------------------------------------------------------*/
void CTaskCtrl::ClearTaskHeap(void) {
	if( m_pbTaskHeap != NULL )
	{
		// タスクリストが初期化されている
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
			 全てのタスクを実行
--------------------------------------------------------*/
void CTaskCtrl::main(void) {

	if( m_pbTaskHeap == NULL ) return ;	// タスクリストが初期化されていない

	// Newできなかった？ or フリーのエリアが少ない？
	if ( m_bDefrag || ((DWORD)( m_dwMemSize - ( m_pbFree - m_pbTaskHeap ) ) <= ( (DWORD)(m_dwMemSize - m_dwSize ) / 8 )) ) 
	{ 
		Defrag() ;
		m_bDefrag = FALSE ; 
	}

	CTaskFunc *task,*next;
	for( task = (CTaskFunc*)m_pbTop ; m_pbTop ; task = next) 
	{
		BYTE *pbTop = m_pbTop ;

		// タスクの実行の有効無効を判断
		if( task->isTaskFlag( TASK_FLAG_ENABLE ) )
		{

			// タスクのクリアフラグが立っていなければ実行
			// 自分自身以外の処理で、クリアフラグがセットされている場合を考慮
			if ( !task->isTaskFlag( TASK_FLAG_CLEAR ) )
			{
				task->main() ;			// タスクのmainを実行
			}

			// タスクの消去のチェック
			if ( task->isTaskFlag( TASK_FLAG_CLEAR ) )
			{
				// タスクの消去
				delete task  ;
				pbTop = m_pbTop ;
			}
			else 
			{
				// タスクの移動・コリジョン処理
				task->After() ;
			}
		}

 		next = task->m_pTaskNext;

		if( next == NULL) break ;
		if ( next == (CTaskFunc*)pbTop ) break ;	// ヒープエリアの最後まで実行したら終了
	}

}

/*--------------------------------------------------------

		 タスクリストのデフラグ

--------------------------------------------------------*/
void CTaskCtrl::Defrag(void) {

	if( m_pbTop == NULL )
	{
		// 使用中のタスクが無い
		m_pbFree = m_pbTaskHeap ;
		memset( m_pbTaskHeap,0, m_dwMemSize ) ;
		return ;
	}

	BYTE *dest=m_pbTaskHeap;

	CTaskFunc *task;
	DWORD size;

	task=(CTaskFunc*)m_pbTop;

	// タスクが１つしかないとき
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
	// タスクが複数存在するとき
	else
	{
		for(BYTE *source=m_pbTaskHeap; source<m_pbFree; source+=size) 
		{
			task=(CTaskFunc*)source;
			size=task->m_dwSize;
			if(task->isUse() == FALSE) continue;

			if ( dest != source )
			{ 
				memmove(dest,source,size);				// タスクのメモリイメージを移動

				// タスクのリンクの張り替え
				task=(CTaskFunc*)dest;
				task->m_pTaskPrev->m_pTaskNext = task;
				task->m_pTaskNext->m_pTaskPrev = task;
		
				// タスクの親子関係の張り替え
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

				// 子タスクに親の新しいポインタを通知
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
			// 最初に実行するタスクか？
			if(source==m_pbTop) m_pbTop=dest;			
			dest+=size;
		}
	}

	memset(dest,0,m_pbFree-dest);		// 未使用になった領域を初期化
	m_pbFree=dest;
}

/*--------------------------------------------------------

				 同期処理

--------------------------------------------------------*/
BOOL CTaskCtrl::isSync() {

	m_dwTimeNow = ::timeGetTime();

	if ( m_dwTimeOver < m_dwMSPF )

		if ( m_dwTimeNow - m_dwTimePrev < m_dwMSPF - m_dwTimeOver ) return TRUE ;
		
	if ( m_dwTimePrev > 0 )
	{
		m_dwTime = m_dwTimeNow - m_dwTimePrev ;
		m_dwTimeOver += m_dwTimeNow - m_dwTimePrev - m_dwMSPF ;	//ずれる時間を次回に持ち越す
		if ( m_dwTimeOver >= m_dwMSPF*2 ) m_dwTimeOver = m_dwMSPF*2 ;
	}
	m_dwTimePrev = ::timeGetTime();	//ここが計測の起点

	return ( FALSE ) ;
}

/*--------------------------------------------------------

		 スプライトデバイス初期化

--------------------------------------------------------*/
HRESULT CTaskCtrl::CreateSprite(DxWin* pDxw) {
	m_pSprite = new DxSprite(pDxw) ;
	return m_pSprite->Create() ; 
}

/*--------------------------------------------------------

			 全てのタスクを描画

--------------------------------------------------------*/
HRESULT CTaskCtrl::DrawAll() {
	HRESULT hr = S_FALSE;
	if( m_pSprite == NULL ) return( hr ) ;

	hr = m_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ; if (FAILED(hr)) return( hr ) ;	// スプライト描画開始

	CTaskFunc *task,*next;
	for( task = (CTaskFunc*)m_pbTop ; m_pbTop ; task = next ) 
	{

		task->Draw( m_pSprite ) ;

		next = (CTaskFunc*)task->m_pTaskNext ;
		if( next == (CTaskFunc*)m_pbTop ) break ;
	}

	m_pSprite->End() ;			// スプライト描画終了
	return ( hr ) ;
}

/*========================================================

				タスク本体

========================================================*/

CTaskCtrl* CTaskFunc::m_spCTaskCtrl = NULL ;


/*--------------------------------------------------------

			 タスクの生成・追加

--------------------------------------------------------*/
void* CTaskFunc::operator new(size_t size, float priority, int group) {

	// タスクリストが初期化されていない
	if( m_spCTaskCtrl->isHeap() == NULL ) return NULL;  

	// ヒープエリアの確認
	if( m_spCTaskCtrl->m_pbFree + size >= m_spCTaskCtrl->isHeap() + m_spCTaskCtrl->isMemSize() ) 
	{
		// ヒープが足りないのでデフラグ
		if ( m_spCTaskCtrl->isMemSize() >= m_spCTaskCtrl->isUseSize() + size ) 
		{
			m_spCTaskCtrl->setDefrag() ;
		}
		return NULL ;
	}

	// 優先度によって、ヒープエリアをどれだけ使用できるかを制限する
	// 優先度1.0fの時100%分のヒープエリアを使用でき、
	// 0.5fの時は、50%分のヒープエリアを使用できる。
	if ( m_spCTaskCtrl->m_dwSize >= (DWORD)((float)m_spCTaskCtrl->isMemSize() * priority ) ) {
		return NULL ;		// 優先度に対するヒープエリア不足
	}

	m_spCTaskCtrl->m_dwSize += (DWORD)size;//workエリアの管理
	m_spCTaskCtrl->m_dwCount++ ;

    CTaskFunc *new_task = (CTaskFunc*)m_spCTaskCtrl->m_pbFree ;
    m_spCTaskCtrl->m_pbFree += size;

	if(m_spCTaskCtrl->m_pbTop == NULL) 
	{
		// 現在タスクリストは空
		m_spCTaskCtrl->m_pbTop = (BYTE*)new_task;

		//taskの前後関係の管理
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

    // タスクリストに挿入する
    CTaskFunc *task,*next;
    for( task = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ; ; task = next )
	{
        next = task->m_pTaskNext ;
		// タスクの優先度をチェック（!優先度が高いと、表示は下になる）
		if( priority > task->m_fPriority )
		{
			// 優先度が高い場合は、先頭に挿入
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
			// 優先度が低いor同じ場合は、末尾に挿入
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

			 タスクの削除

--------------------------------------------------------*/
void CTaskFunc::operator delete(void *pTask)
{
	if( m_spCTaskCtrl->isHeap()==NULL ) return;
	CTaskFunc *task=(CTaskFunc*)pTask;

	// 無効のエリアは削除しない
	if( task->isTaskFlag( TASK_FLAG_USE ) == FALSE) return ;	
	task->resetTaskFlag( TASK_FLAG_USE ) ;
	
	// 実際のデストラクトは、各オブジェクト行い、ヒープの操作のみ行う。
	// タスクの「m_pTaskPrev」保持するために変数のクリアは行わない。
	m_spCTaskCtrl->m_dwSize -= task->m_dwSize;
	m_spCTaskCtrl->m_dwCount--;

	// 最初に実行するタスクか？
	if( task == (CTaskFunc*)m_spCTaskCtrl->m_pbTop ) 
	{
		// 最後のタスクか？
		if( task->m_pTaskNext == (CTaskFunc*)m_spCTaskCtrl->m_pbTop ) 
		{
			m_spCTaskCtrl->m_pbTop = NULL;
			return;
		}
		else m_spCTaskCtrl->m_pbTop = (BYTE*)task->m_pTaskNext ;
	}

	// タスクの実行順番をつなぎ直す
	task->m_pTaskPrev->m_pTaskNext = task->m_pTaskNext ;
	task->m_pTaskNext->m_pTaskPrev = task->m_pTaskPrev ;

	// タスクの親子関係をつなぎ直す
	if ( task->m_pTaskParent != NULL || task->m_pTaskChild != NULL ) { task->LinkOff() ; }
}

/*--------------------------------------------------------

		コンストラクタ・デストラクタ

--------------------------------------------------------*/
CTaskFunc::CTaskFunc() {
	m_pTaskParent = NULL ;	// 親タスクバッファポインタ
	m_pTaskChild = NULL ;		// 子タスクバッファポインタ


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

	// ヒープエリア使用中のフラグのみを残し、他はクリアする、
	resetTaskFlag( ~TASK_FLAG_USE ) ;	
	if(isTaskFlag(TASK_FLAG_TEX))
	{
		_DELETE(m_pDxT) ;
	}
}
/*--------------------------------------------------------

		 テクスチャーの読み込み

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

		 タスクのオブジェクト表示

--------------------------------------------------------*/
void CTaskFunc::Draw( DxSprite* pSprite ) {
	// Objectの表示
	if ( isTaskFlag( TASK_FLAG_ENABLE | TASK_FLAG_OBJECT ) && m_pDxT != NULL ) 
	{
		if(m_rect.bottom == m_rect.top || m_rect.left == m_rect.right)
		{
			// 描画
			pSprite->Draw(m_pDxT,&D3DXVECTOR3(x,y,z),&m_scale,m_rotate);
		}
		else
		{
			// 描画
			pSprite->Draw(m_pDxT,&D3DXVECTOR3(x,y,z),&m_scale,m_rotate,&m_rect,m_color);
		}
	}
}

/*--------------------------------------------------------

		 タスクの後処理後

--------------------------------------------------------*/
void CTaskFunc::After(){

	if ( isTaskFlag( TASK_FLAG_ENABLE ) )
	{
		// 移動処理
		if ( isTaskFlag( TASK_FLAG_NOMOVE ) )
		{
			resetTaskFlag( TASK_FLAG_NOMOVE ) ;
		}
		else 
		{
			x += dx ;
			y += dy ;
		}

		// コリジョン処理
		// 　同じグループ同士の当たりは判定しない仕様になっている
		if ( isTaskFlag( TASK_FLAG_COL_ACT ) ) 
		{
			CTaskFunc *task,*next=NULL;
			for( task = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
				next != (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
				task = next ) 
			{
				next = (CTaskFunc*)task->m_pTaskNext ;
				// 比較の前後は、括弧で括れ！のよい例↓
				if ( ( task->m_dwTaskFlag					// 両者ともコリジョンの対象か？
						& ( TASK_FLAG_ENABLE | TASK_FLAG_COL_PSV | TASK_FLAG_CLEAR | TASK_FLAG_HIT ) )
					!= ( TASK_FLAG_ENABLE | TASK_FLAG_COL_PSV ) ) { continue ; }

				if ( this == task ) continue;				// 自分自身でないか？
				if ( m_iGroup == task->m_iGroup ) continue;	// 別のグループか？
				if ( task->colx == 0						// コリジョンのサイズは有るか？
					|| task->coly == 0 ) continue ;		

				if ( task->x - task->colx <= x + colx
					&& task->x + task->colx >= x - colx
					&& task->y - task->coly <= y + coly
					&& task->y + task->coly >= y - coly 
				) {
// Cで処理するなら、フラグを立てて、各関数でフラグの内容に沿った処理をする
// task->m_dwTaskFlag |= TASK_FLAG_HIT ;
// m_dwTaskFlag |= TASK_FLAG_HIT ;
					task->Hit(this) ;	// 相手の当たり処理
					Hit(task) ;			// 自身の当たり処理

					// 自身の当たりフラグが立てられれば、ループを終了する
					if ( task->isTaskFlag( TASK_FLAG_HIT ) ) break ;
				}
			}
		}
	}
}
/*-----------------------------------------------------------------------------

				タスクの削除

-----------------------------------------------------------------------------*/
void CTaskFunc::Delete() {

	setTaskFlag( TASK_FLAG_CLEAR ) ;

	// 自分が親の場合は、子とのリンクを削除する
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

				 タスクの削除(グループ単位)]

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

			 全タスクの削除

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

			 タスクの衝突処理(継承クラスに定義が無い場合は、フラグを立てる）

-----------------------------------------------------------------------------*/
void CTaskFunc::Hit(CTaskFunc* task){

	setTaskFlag( TASK_FLAG_HIT ) ;

}
/*-----------------------------------------------------------------------------

			 タスクフラグの制御

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
			優先度の変更
-----------------------------------------------------------------------------*/
void CTaskFunc::SetPriority(float priority)
{
	m_fPriority=priority;

	// タスクリストから除外する
	if( this == (CTaskFunc*)m_spCTaskCtrl->m_pbTop )
	{	
		// 最初に実行するタスクか？
		if( m_pTaskNext == (CTaskFunc*)m_spCTaskCtrl->m_pbTop) return;		// 唯一のタスクか？
		m_spCTaskCtrl->m_pbTop = (BYTE*)m_pTaskPrev;
	}
	m_pTaskPrev->m_pTaskNext = m_pTaskNext ;
	m_pTaskNext->m_pTaskPrev = m_pTaskPrev ;

	// タスクリストに挿入する

	CTaskFunc *active = (CTaskFunc*)m_spCTaskCtrl->m_pbTop ;
	CTaskFunc *task, *next;
	for( task = active ;; task = next ) 
	{
		next=task->m_pTaskNext;

		// タスクの優先度をチェック（!優先度が高いと、表示は下になる）
		if( priority > task->m_fPriority )	
		{
			// 優先度が高い場合は、先頭に挿入
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
			// 優先度が低いor同じ場合は、末尾に挿入
			m_pTaskPrev = task;
			m_pTaskNext = next;
			break;
		}
	}

	m_pTaskPrev->m_pTaskNext = this;
	m_pTaskNext->m_pTaskPrev = this;

	// 最初に実行するタスクを指すポインタを再設定
	if( priority > active->m_fPriority ) m_spCTaskCtrl->m_pbTop = (BYTE*)this ;
}

/*-----------------------------------------------------------------------------

			 タスクのリンク

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

			タスクのリンクから自分をはずす

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
		//LinkOffが親の場合すべてのこの親を書き換える
		if( pKo->m_pTaskParent == this || m_pTaskParent == NULL )
		{
			pOya = m_pTaskChild;
			while( pOya != NULL)
			{
				pOya->m_pTaskParent = m_pTaskChild;
				pOya = pOya->m_pTaskChild;
			}
		}
		//LinkOffが子の場合
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

			 子タスクの削除

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

			 子タスクの当たり

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

			 親タスクの削除

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

			 親タスクの当たり
			 
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
// テクスチャーのデータのセット
--------------------------------------------------------*/
DxTexture* CTaskFunc::GetTexture( ){

	return m_pDxT;

}
/*--------------------------------------------------------
// テクスチャーのデータのセット
--------------------------------------------------------*/
void CTaskFunc::SetTexture( DxTexture* g_tex){
	if(g_tex)
	{
		m_pDxT = new DxTexture(m_spCTaskCtrl->isDxWin());
		*m_pDxT = *g_tex;
	}
};
/*--------------------------------------------------------
// rectをセットする関数
--------------------------------------------------------*/
void CTaskFunc::SetRect(long left, long top, long right, long bottom){
	m_rect.left = left;
	m_rect.top = top;
	m_rect.right = right;
	m_rect.bottom = bottom;
	m_pDxT->SetCenter(m_rect);
}

/*=======================================================================
	カラーセット関数
	戻り値：ture or false
			初期化成功-true　失敗-false
	引数：番号　アルファ値　赤　緑　青
==========================================================================*/
void CTaskFunc::SetAlpha()
{
	m_color = D3DCOLOR_ARGB(255,255,255,255);
}
/*=======================================================================
	カラーセット関数
	戻り値：ture or false
			初期化成功-true　失敗-false
	引数：番号　アルファ値　赤　緑　青
==========================================================================*/
void CTaskFunc::SetAlpha(int a)
{
	m_color = D3DCOLOR_ARGB(a,255,255,255);
}
/*=======================================================================
	パターン変更関数
	戻り値：なし
	引数：なし
==========================================================================*/
void CTaskFunc::PtnChange()
{
	//RECTの切り替え時間足してくー
	m_iPtntimer++;
	//ループフラグTRUEの時
	if(m_bPtnLoopflg)
	{

		//パターンがMAXより少ない時
		if(m_iPtntimer >= m_iPtntimer_Max)
		{
			//RECTの切り替え時間0にする
			m_iPtntimer = 0;
			//右にRECTを・・・
			if(m_bPtnRetunflg)
			{
				//パターン変更
				m_iPtn++;
				//RECTの変更
				m_rect.left   += m_rectSize.right;
				m_rect.top    += m_rectSize.bottom;
				m_rect.right  += m_rectSize.right;
				m_rect.bottom += m_rectSize.bottom ;
				//パターンMAXになったら
				if(m_iPtn == m_iPtn_Max)
				{
					//へし折る
					m_bPtnRetunflg = false;
				}
			}
			//左にRECTを
			else
			{
				//RECTの切り替え時間0にする
				m_iPtntimer = 0;
				//パターン変更
				m_iPtn--;
				//RECT変更
				m_rect.left   -= m_rectSize.right;
				m_rect.top    -= m_rectSize.bottom;
				m_rect.right  -= m_rectSize.right;
				m_rect.bottom -= m_rectSize.bottom ;
				//パターンが０になったら
				if(m_iPtn == m_iPtninit)
				{
					//再生フラグ
					m_bPtnRetunflg = true;
				}
			}
		}

	}
	//FALSE
	else
	{
		//パターンがMAXより少ない時
		if(m_iPtntimer == m_iPtntimer_Max)
		{
			//RECTの切り替え時間0にする
			m_iPtntimer = 0;
			//パターン変更
			m_iPtn++;
			
			//RECT変更
			m_rect.left   += m_rectSize.right;
			m_rect.right  += m_rectSize.right;

			//パターンがMAXになったら
			if(m_iPtn % m_iPtn_Right_Max == 0)
			{
				//RECT変更
				m_rect.left   = (m_rectSize.right * m_iPtninit);
				m_rect.right  = (m_rectSize.right * (m_iPtninit+1)) ;
				m_rect.top   += m_rectSize.bottom;
				m_rect.bottom  += m_rectSize.bottom;
			}
			if(m_iPtn == m_iPtn_Max)
			{
				m_iPtn = m_iPtninit;
				//右の変更画像の時
				if(m_rectSize.right != 0)
				{
					m_rect.left   = (m_rectSize.right * m_iPtninit);
					m_rect.right  = (m_rectSize.right * (m_iPtninit+1)) ;
				}
				//下の変更画像の時
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