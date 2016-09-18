#pragma once
#include "stdafx.h"

//DirectX Window面定義クラス
class DxWin
{
	// Winddow関連
	HWND		m_hWnd ;
	LRESULT*	m_pWndProc ;

	// DirectX関連
	IDirect3D9*         m_pD3D;                // D3Dオブジェクト
	IDirect3DDevice9*   m_pd3dDevice;          // D3DDeviceオブジェクト
	D3DCOLOR            m_clrBackgroundColor;  // 背景色

public:
	DxWin(void* pWndProc) ;	//コンストラクタ
	~DxWin();	//デストラクタ

	HWND Create(HINSTANCE hInst, LPCWSTR szWinName, int width, int height, BOOL bWin) ;	//作成
	HRESULT Init() { 
		return ( Init( D3DDEVTYPE_HAL, D3DADAPTER_DEFAULT, D3DCREATE_HARDWARE_VERTEXPROCESSING, D3DSWAPEFFECT_DISCARD )) ; 
	}
	HRESULT Init( D3DDEVTYPE dwDeviceType, UINT nAdapter, DWORD dwBehaviorFlags, D3DSWAPEFFECT dwSwapEffect ) ;

	HRESULT Begin() ;
	void End() ;

	// 取得している値を返す
//	HWND hWnd() { return ( m_hWnd ) ; }
	IDirect3DDevice9* isDevice() { return ( m_pd3dDevice ) ; }

};

