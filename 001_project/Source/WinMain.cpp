#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>     // time使用

#include "macro.h"
#include "DxWin.h"
#include "DxInput.h"
#include "DxFont.h"
#include "DxSound.h"
#include "CTask.h"


// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
CTaskCtrl*	g_pCTaskCtrl ;
BOOL		g_bLoop = TRUE ;	// メインループ制御
HRESULT		WinDraw(DxWin* pDxw, DxFont* pDxf,FONT pTEXT) ;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned) time(NULL));

	DxWin*		pDxw ;
	DxInput*	pDxi ;
	DxFont*		pDxf ;
	DxSound*	pDxs ;

	MSG msg;
	HWND hWnd;
	HRESULT hr;
	POINT Mpt;
	FONT pTEXT ;

	//--------------初期化処理--------------
	
	//ウィンドウ生成
	pDxw = new DxWin( (void*)&WndProc );
	hWnd = pDxw->Create(hInstance, _T("TestPrject"), 800,600, FALSE) ;
	
	//ウィンドウハンドル取得失敗
	if( !hWnd ){ return FALSE; }
	
	// D3Dの初期化
	hr = pDxw->Init();
	
	//D3Dオブジェクトの作成失敗
	if( FAILED(hr) ){ return FALSE; }

	//テキストの初期化
	pTEXT.x = 0 ;
	pTEXT.y = 0 ;
	char byteText[4800];
	byteText[0] = byteText[1] = '\0';
	pTEXT.color = D3DCOLOR_XRGB(255,255,255);
	pTEXT.TEXT = byteText;

	// フォントの初期化
	pDxf = new DxFont(pDxw);
	hr = pDxf->Create(16,0,_T("ＭＳ Ｐゴシック"));
	
	//フォント初期化失敗
	if( FAILED(hr) ){ return FALSE; }
	
	// 入力の初期化
	pDxi = new DxInput();
	
	hr = pDxi->Create(hInstance); 
	if( FAILED(hr) ){ return FALSE; }
	
	hr = pDxi->InitKeyboard(hWnd); 
	if( FAILED(hr) ){ return FALSE; }
	
	hr = pDxi->InitMouse(hWnd);
	if( FAILED(hr) ){ return FALSE; }
	
	//サウンド
	pDxs = new DxSound() ;
	pDxs->CreateDirectSound(hWnd);
	
	if( FAILED(pDxs) ){ return FALSE; }

	//マウスカーソルの変更
	//SetCursor( LoadCursorA(0,(LPCSTR)32649) );

	// Taskコントローラの初期化
	g_pCTaskCtrl = new CTaskCtrl(262144);//ヒープエリアのサイズ/65536
	g_pCTaskCtrl->CreateSprite( pDxw );

	//マウスカーソルを消す
	//ShowCursor( FALSE );

	// 事前に１回描画してウィンドウ表示
	hr = WinDraw( pDxw, pDxf,pTEXT ) ;
	SetWindowPos(hWnd, NULL, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);

	if( FAILED(hr) ){ g_bLoop = FALSE ; }

	//--------------ここまで--------------
	
	//メイン処理
	while( g_bLoop ) 
	{
		// メイン メッセージ ループ
		do
		{
			if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
	        }
		}  
		while ( g_pCTaskCtrl->isSync() );

		// 入力デバイスの読み込み
		pDxi->GetKeyboard();
		pDxi->GetMouse() ;
		GetCursorPos(&Mpt);
		ScreenToClient(hWnd, &Mpt);

		// デバッグ表示
		//sprintf_s ( byteText	
		//	,"Time:%d\nOver=%d\nHeap use=%d\nTask count=%d\n  "
		//	,g_pCTaskCtrl->isTime()  
		//	,g_pCTaskCtrl->isTimeOver()  
		//	,g_pCTaskCtrl->isUseSize()  
		//	,g_pCTaskCtrl->isCount()
		//) ;

		// 描画に失敗したらメインループを停止する
		hr = WinDraw( pDxw, pDxf,pTEXT ) ; 
		if( FAILED(hr) ){ break ; }
	}

	// 後処理
	_DELETE(g_pCTaskCtrl) ;
	_DELETE(pDxf) ;
	_DELETE(pDxw) ;
	_DELETE(pDxi) ;
	_DELETE(pDxs) ;
	
	return (int) msg.wParam;
}

// 描画処理
HRESULT WinDraw(DxWin* pDxw,DxFont* pDxf, FONT pTEXT) {
	HRESULT hr;

	hr = pDxw->Begin() ;	// DirectX面の描画開始
	if( !FAILED(hr) )
	{
		hr = g_pCTaskCtrl->DrawAll() ;	// オブジェクトの描画
		if( !FAILED(hr) ) 
		{
			hr = pDxf->DrawA(&pTEXT) ;	// テキスト面の描画
		}

		pDxw->End() ;			// シーン描画の終了とバックバッファからの表示}
	}
	return ( hr ) ;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message ) 
	{
		case WM_PAINT:
			break;

		case WM_ERASEBKGND:
			return FALSE;

		case WM_DESTROY:
			g_bLoop = FALSE;
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			//別にescキーで終了する必要ないのでコメントアウト
			//if( wParam == VK_ESCAPE )
			//{
			//	//エスケープで終了
			//	g_bLoop = FALSE;
			//	PostQuitMessage(0);
			//}
			break;

		default:
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
