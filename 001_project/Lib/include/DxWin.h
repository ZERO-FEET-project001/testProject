#pragma once
#include "stdafx.h"

//DirectX Window�ʒ�`�N���X
class DxWin
{
	// Winddow�֘A
	HWND		m_hWnd ;
	LRESULT*	m_pWndProc ;

	// DirectX�֘A
	IDirect3D9*         m_pD3D;                // D3D�I�u�W�F�N�g
	IDirect3DDevice9*   m_pd3dDevice;          // D3DDevice�I�u�W�F�N�g
	D3DCOLOR            m_clrBackgroundColor;  // �w�i�F

public:
	DxWin(void* pWndProc) ;	//�R���X�g���N�^
	~DxWin();	//�f�X�g���N�^

	HWND Create(HINSTANCE hInst, LPCWSTR szWinName, int width, int height, BOOL bWin) ;	//�쐬
	HRESULT Init() { 
		return ( Init( D3DDEVTYPE_HAL, D3DADAPTER_DEFAULT, D3DCREATE_HARDWARE_VERTEXPROCESSING, D3DSWAPEFFECT_DISCARD )) ; 
	}
	HRESULT Init( D3DDEVTYPE dwDeviceType, UINT nAdapter, DWORD dwBehaviorFlags, D3DSWAPEFFECT dwSwapEffect ) ;

	HRESULT Begin() ;
	void End() ;

	// �擾���Ă���l��Ԃ�
//	HWND hWnd() { return ( m_hWnd ) ; }
	IDirect3DDevice9* isDevice() { return ( m_pd3dDevice ) ; }

};

