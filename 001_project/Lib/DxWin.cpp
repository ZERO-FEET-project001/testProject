#include "DxWin.h"
#include "Macro.h"
#include "resource.h"

//---------------------------------------------------
// コンストラクタ
//---------------------------------------------------
DxWin::DxWin(void* pWndProc) { 
	m_pWndProc = (LRESULT *)pWndProc ;
	m_clrBackgroundColor = D3DCOLOR_XRGB(0xff,0x00,0xff);

	m_pd3dDevice = NULL ;
	m_pD3D = NULL ;
}

//---------------------------------------------------
// デストラクタ
//---------------------------------------------------
DxWin::~DxWin() {
	// IDirect3DDevice9オブジェクトの解放
	_RELEASE( m_pd3dDevice ) ;

	// IDirect3D9オブジェクトの解放
	_RELEASE( m_pD3D ) ;
}

//---------------------------------------------------
// ウィンドウの作成
//
//  hInst		WinMainに渡される「HINSTANCE」をそのまま設定
//  szWinName	Windowの名称
//  width		Windowモード時の幅
//  height		Windowモード時の高さ
//  bWin			フルスクリーン指定（TRUE:フルスクリーン　FALSE：Windowモード)
//---------------------------------------------------
HWND DxWin::Create(HINSTANCE hInst, LPCWSTR szWinName, int width, int height, BOOL bWin) {

	WNDCLASSEX wcex;

	// ウィンドウクラス登録
	::ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize             = sizeof(WNDCLASSEX);
	wcex.style              = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc        = (WNDPROC)m_pWndProc ;
	wcex.hInstance          = hInst;
	wcex.hIcon              = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm            = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor            = LoadCursor (NULL, IDC_HAND);
	wcex.hbrBackground      = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszClassName      = szWinName;
	if (!RegisterClassEx(&wcex)) return FALSE;


	// ウィンドウ作成
	m_hWnd = CreateWindow(szWinName,szWinName,
	                    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX ,
	                    CW_USEDEFAULT, CW_USEDEFAULT, width+4*2, height+27,
	                    NULL, NULL, hInst, NULL);

	return( m_hWnd ) ;
}

//---------------------------------------------------
// デバイス初期化
//---------------------------------------------------
HRESULT DxWin::Init( D3DDEVTYPE dwDeviceType, UINT nAdapter, DWORD dwBehaviorFlags, D3DSWAPEFFECT dwSwapEffect )
{
	HRESULT hr;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE        dmode;

	// D3Dオブジェクトの作成
	m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION);

	// 現在のディスプレイモードを取得
	::ZeroMemory(&d3dpp, sizeof(d3dpp));
	hr = m_pD3D->GetAdapterDisplayMode(nAdapter, &dmode);
	if (FAILED(hr)) return hr;

	// パラメータの設定
	d3dpp.Windowed               = TRUE;                  // ウィンドウモードで表示
	d3dpp.SwapEffect             = dwSwapEffect;
	d3dpp.BackBufferFormat       = dmode.Format;          // デスクトップのフォーマットを使用
	d3dpp.BackBufferCount        = 2;                     // トリプルバッファリングを行う
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;            // 16Bit Zバッファ作成

	// IDirect3DDevice9オブジェクトの作成
	hr = m_pD3D->CreateDevice(nAdapter, dwDeviceType,
		m_hWnd, dwBehaviorFlags,
		&d3dpp, &m_pd3dDevice);
	if (FAILED(hr)) return hr;

	return S_OK;
}

//---------------------------------------------------
// DirectX Window面の描画開始
//---------------------------------------------------
HRESULT DxWin::Begin() {
	// クリア
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_clrBackgroundColor, 1.0f, 0);


	// 描画開始
	if (FAILED(m_pd3dDevice->BeginScene())) {
		m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
		return S_FALSE ;
	}

	return S_OK;
}

//---------------------------------------------------
// DirectX Window面の描画終了
//---------------------------------------------------
void DxWin::End() {
	// シーン描画の終了とバックバッファからの表示
	m_pd3dDevice->EndScene();
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
