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

//DirectInput Window�ʒ�`�N���X
class DxInput
{
	// DirectX�֘A
	LPDIRECTINPUT8			m_pDInput ;				// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	m_pDIKeyboard ;			// �L�[�{�[�h�f�o�C�X
	BYTE					m_diKeyState[256];		// �L�[�{�[�h���
	BYTE					m_diKeyStateNow[256];		// �L�[�{�[�h���
	BYTE					m_diKeyStateTrigger[256];	// �L�[�{�[�h���
	BYTE					m_diKeyStateRelease[256];	// �L�[�{�[�h���
	LPDIRECTINPUTDEVICE8	m_pDIJoypad ;			// �W���C�p�b�h�f�o�C�X
	DWORD					m_diJoyState ;			// �W���C�p�b�h���
	LPDIRECTINPUTDEVICE8	m_pDIMouse ;			// �}�E�X�f�o�C�X
	DIMOUSESTATE			m_diMouseState;			// �}�E�X���
	BYTE					m_MouseButtonNow[4];
	BYTE					m_MouseButtonTrigger[4];
	BYTE					m_MouseButtonRelease[4];

public:
	DxInput() ;	//�R���X�g���N�^
	~DxInput();	//�f�X�g���N�^

	HRESULT Create(HINSTANCE hInstApp) ;	//�쐬

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


