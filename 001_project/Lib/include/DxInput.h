#pragma once
#include "stdafx.h"
#include <dinput.h> 

#define DXI_LEFT		2+0
#define DXI_LEFT_UP		2+4
#define DXI_UP			0+4
#define DXI_RIGHT_UP	1+4
#define DXI_RIGHT		1+0
#define DXI_RIGHT_DOWN	1+8
#define DXI_DOWN		0+8
#define DXI_LEFT_DOWN	2+8
#define DXI_SPACE		16
#define DXI_ENTER       18
#define DXI_Z	        20


#define	DXI_MOUSE_LEFT		0
#define	DXI_MOUSE_RIGHT		1
#define	DXI_MOUSE_CENTER	2

//DirectInput Window面定義クラス
class DxInput
{
	// DirectX関連
	LPDIRECTINPUT8			m_pDInput ;				// DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8	m_pDIKeyboard ;			// キーボードデバイス
	BYTE					m_diKeyState[256];		// キーボード情報
	BYTE					m_diKeyStateNow[256];		// キーボード情報
	BYTE					m_diKeyStateTrigger[256];	// キーボード情報
	BYTE					m_diKeyStateRelease[256];	// キーボード情報
	LPDIRECTINPUTDEVICE8	m_pDIJoypad ;			// ジョイパッドデバイス
	DWORD					m_diJoyState ;			// ジョイパッド情報
	LPDIRECTINPUTDEVICE8	m_pDIMouse ;			// マウスデバイス
	DIMOUSESTATE			m_diMouseState;			// マウス情報
	BYTE					m_MouseButtonNow[4];
	BYTE					m_MouseButtonTrigger[4];
	BYTE					m_MouseButtonRelease[4];

public:
	DxInput() ;	//コンストラクタ
	~DxInput();	//デストラクタ

	HRESULT Create(HINSTANCE hInstApp) ;	//作成

	HRESULT InitKeyboard(HWND hWnd) ;
	void GetKeyboard() ;
	BOOL isKey( int key ) ;
	int isKeyDir() ;
	BOOL isKeyTrigger( int key ) ;
	BOOL isKeyRelease( int key ) ;

	HRESULT InitMouse(HWND hWnd) ;
	void GetMouse() ;
	BOOL isMouse( int key ) ;
	BOOL isMouseTrigger( int key ) ;
	BOOL isMouseRelease( int key ) ;

};


