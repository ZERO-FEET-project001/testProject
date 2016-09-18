#include "DxWin.h"
#include "Macro.h"
#include "resource.h"

//---------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------
DxWin::DxWin(void* pWndProc) { 
	m_pWndProc = (LRESULT *)pWndProc ;
	m_clrBackgroundColor = D3DCOLOR_XRGB(0xff,0x00,0xff);

	m_pd3dDevice = NULL ;
	m_pD3D = NULL ;
}

//---------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------
DxWin::~DxWin() {
	// IDirect3DDevice9�I�u�W�F�N�g�̉��
	_RELEASE( m_pd3dDevice ) ;

	// IDirect3D9�I�u�W�F�N�g�̉��
	_RELEASE( m_pD3D ) ;
}

//---------------------------------------------------
// �E�B���h�E�̍쐬
//
//  hInst		WinMain�ɓn�����uHINSTANCE�v�����̂܂ܐݒ�
//  szWinName	Window�̖���
//  width		Window���[�h���̕�
//  height		Window���[�h���̍���
//  bWin			�t���X�N���[���w��iTRUE:�t���X�N���[���@FALSE�FWindow���[�h)
//---------------------------------------------------
HWND DxWin::Create(HINSTANCE hInst, LPCWSTR szWinName, int width, int height, BOOL bWin) {

	WNDCLASSEX wcex;

	// �E�B���h�E�N���X�o�^
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


	// �E�B���h�E�쐬
	m_hWnd = CreateWindow(szWinName,szWinName,
	                    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX ,
	                    CW_USEDEFAULT, CW_USEDEFAULT, width+4*2, height+27,
	                    NULL, NULL, hInst, NULL);

	return( m_hWnd ) ;
}

//---------------------------------------------------
// �f�o�C�X������
//---------------------------------------------------
HRESULT DxWin::Init( D3DDEVTYPE dwDeviceType, UINT nAdapter, DWORD dwBehaviorFlags, D3DSWAPEFFECT dwSwapEffect )
{
	HRESULT hr;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE        dmode;

	// D3D�I�u�W�F�N�g�̍쐬
	m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION);

	// ���݂̃f�B�X�v���C���[�h���擾
	::ZeroMemory(&d3dpp, sizeof(d3dpp));
	hr = m_pD3D->GetAdapterDisplayMode(nAdapter, &dmode);
	if (FAILED(hr)) return hr;

	// �p�����[�^�̐ݒ�
	d3dpp.Windowed               = TRUE;                  // �E�B���h�E���[�h�ŕ\��
	d3dpp.SwapEffect             = dwSwapEffect;
	d3dpp.BackBufferFormat       = dmode.Format;          // �f�X�N�g�b�v�̃t�H�[�}�b�g���g�p
	d3dpp.BackBufferCount        = 2;                     // �g���v���o�b�t�@�����O���s��
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;            // 16Bit Z�o�b�t�@�쐬

	// IDirect3DDevice9�I�u�W�F�N�g�̍쐬
	hr = m_pD3D->CreateDevice(nAdapter, dwDeviceType,
		m_hWnd, dwBehaviorFlags,
		&d3dpp, &m_pd3dDevice);
	if (FAILED(hr)) return hr;

	return S_OK;
}

//---------------------------------------------------
// DirectX Window�ʂ̕`��J�n
//---------------------------------------------------
HRESULT DxWin::Begin() {
	// �N���A
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_clrBackgroundColor, 1.0f, 0);


	// �`��J�n
	if (FAILED(m_pd3dDevice->BeginScene())) {
		m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
		return S_FALSE ;
	}

	return S_OK;
}

//---------------------------------------------------
// DirectX Window�ʂ̕`��I��
//---------------------------------------------------
void DxWin::End() {
	// �V�[���`��̏I���ƃo�b�N�o�b�t�@����̕\��
	m_pd3dDevice->EndScene();
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
