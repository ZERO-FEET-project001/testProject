#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>     // time�g�p

#include "macro.h"
#include "DxWin.h"
#include "DxInput.h"
#include "DxFont.h"
#include "DxSound.h"
#include "CTask.h"
#include "GameSystem.h"
#include "TaskFuncs.h"


// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
CTaskCtrl*	g_pCTaskCtrl ;
BOOL		g_bLoop = TRUE ;	// ���C�����[�v����
HRESULT		draw(DxWin* pDxw, DxFont* pDxf,FONT pTEXT) ;

int APIENTRY _tWinMain(HINSTANCE hInstance,
          HINSTANCE hPrevInstance,
          LPTSTR    lpCmdLine,
          int       nCmdShow)
{
	srand((unsigned) time(NULL));


	DxWin*		pDxw ;
	DxInput*	pDxi ;
	DxFont*		pDxf ;
	DxSound*	pDxs ;
	GameSystem* game;

	MSG msg;
	HWND hWnd;
	HRESULT hr;
	POINT Mpt;//�}�E�X�̍��W
	FONT pTEXT ;

	// �E�B���h�E�쐬
	pDxw = new DxWin((void*)&WndProc) ;//�N���G�C�g
	hWnd = pDxw->Create(hInstance, _T("LineTest"), 800,600, FALSE) ; if (!hWnd) return FALSE ;
	hr = pDxw->Init() ; if (FAILED(hr)) return FALSE;		// D3D�̏�����

	// �e�L�X�g�ʂ̏�����
	pTEXT.x = 0 ; pTEXT.y = 0 ;//�N���G�C�g
	char byteText[4800] ; byteText[0] = byteText[1] = '\0' ;
	pTEXT.color = D3DCOLOR_XRGB(255,255,255) ; pTEXT.TEXT = byteText ;

	// �t�H���g�̏�����
	pDxf = new DxFont(pDxw) ;//�N���G�C�g
	hr = pDxf->Create(16,0,_T("�l�r �o�S�V�b�N")) ; if (FAILED(hr)) return FALSE ;

	// ���͂̏�����
	pDxi = new DxInput() ;//�N���G�C�g
	hr = pDxi->Create(hInstance); if (FAILED(hr)) return FALSE;	// Dinput�̏�����
	hr = pDxi->InitKeyboard(hWnd); if (FAILED(hr)) return FALSE;
	hr = pDxi->InitMouse(hWnd); if (FAILED(hr)) return FALSE;
	//�T�E���h
	pDxs = new DxSound() ; //�N���G�C�g
	pDxs->CreateDirectSound(hWnd);
	InitDirectSound(hWnd);
	LoadSoundData(_T("Sound/Title_BGM.wav"),BGM_TITLE);
	LoadSoundData(_T("Sound/GameMain_BGM.wav"),BGM_MAIN);
	LoadSoundData(_T("Sound/GameOver_BGM.wav"),BGM_GAMEOVER);

	//�}�E�X�J�[�\���̕ύX
	SetCursor( LoadCursorA(0,(LPCSTR)32649) );

	// Task�R���g���[���̏�����
	g_pCTaskCtrl = new CTaskCtrl(262144) ;//�q�[�v�G���A�̃T�C�Y�@/�@65536
	g_pCTaskCtrl->CreateSprite( pDxw ) ;
	//�}�E�X�J�[�\��������
	//ShowCursor( FALSE );
	game = new GameSystem(pDxi,g_pCTaskCtrl,&Mpt);

	// ���O�ɂP��`�悵�ăE�B���h�E�\��
	hr = draw( pDxw, pDxf,pTEXT ) ;
	SetWindowPos(hWnd, NULL, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
	if (FAILED(hr)) { g_bLoop = FALSE ; }

	// ���C��
	while( g_bLoop ) 
	{
		// ���C�� ���b�Z�[�W ���[�v:

		do
		{
			if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
	        }
		}  
		while ( g_pCTaskCtrl->isSync() );
		// ���̓f�o�C�X�̓ǂݍ���
		pDxi->GetKeyboard();
		pDxi->GetMouse() ;
		GetCursorPos(&Mpt);
		ScreenToClient(hWnd, &Mpt);
		game->main();

		// �`�揈��
		sprintf_s ( byteText	// �f�o�b�O�\��
			,"Time:%d\nOver=%d\nHeap use=%d\nTask count=%d\n  "
			,g_pCTaskCtrl->isTime()  
			,g_pCTaskCtrl->isTimeOver()  
			,g_pCTaskCtrl->isUseSize()  
			,g_pCTaskCtrl->isCount()
		) ;

		hr = draw( pDxw, pDxf,pTEXT ) ; if (FAILED(hr)) break ;	// �`��Ɏ��s�����烁�C�����[�v���~����
	}

	// �㏈��
	_DELETE(g_pCTaskCtrl) ;
	_DELETE(pDxf) ;
	_DELETE(pDxw) ;
	_DELETE(pDxi) ;
	_DELETE(pDxs) ;
	//Direct3DSound�I��
	ReleaseSound();
	return (int) msg.wParam;
}

// �`�揈��
HRESULT draw(DxWin* pDxw,DxFont* pDxf, FONT pTEXT) {
	HRESULT hr;

	hr = pDxw->Begin() ;	// DirectX�ʂ̕`��J�n
	if (!FAILED(hr))
	{
		hr = g_pCTaskCtrl->DrawAll() ;	// �I�u�W�F�N�g�̕`��
		if (!FAILED(hr)) 
		{
			hr = pDxf->DrawA(&pTEXT) ;	// �e�L�X�g�ʂ̕`��
		}

		pDxw->End() ;			// �V�[���`��̏I���ƃo�b�N�o�b�t�@����̕\��}
	}
	return ( hr ) ;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PAINT:
//		g_pTask->DrawAlone() ;
		break;

	case WM_ERASEBKGND:
		return FALSE;

	case WM_DESTROY:
		g_bLoop = FALSE ;
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam) {
		case VK_ESCAPE:
			//�G�X�P�[�v�ŏI��
			g_bLoop = 0;
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}