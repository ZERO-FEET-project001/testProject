#include "DxInput.h"
#include "Macro.h"

#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

//-----------------------------------------------------------------------------
// Joypad�p�ݒ�l
//-----------------------------------------------------------------------------
#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		1000			// �L���͈͂̍ő�l
#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l

//---------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------
DxInput::DxInput() {
	m_pDInput = NULL ;
	m_pDIJoypad = NULL ;
	m_diJoyState = 0x00000000L;
	m_pDIMouse = NULL ;

	::ZeroMemory(m_diKeyState, sizeof(m_diKeyState));
	::ZeroMemory(m_diKeyStateNow, sizeof(m_diKeyStateNow));
	::ZeroMemory(m_diKeyStateTrigger, sizeof(m_diKeyStateTrigger));
	::ZeroMemory(m_diKeyStateRelease, sizeof(m_diKeyStateRelease));

	::ZeroMemory(m_MouseButtonNow, sizeof(m_MouseButtonNow));
	::ZeroMemory(m_MouseButtonTrigger, sizeof(m_MouseButtonTrigger));
	::ZeroMemory(m_MouseButtonRelease, sizeof(m_MouseButtonRelease));
}

//---------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------
DxInput::~DxInput() {
	_RELEASE( m_pDInput ) ;
	_RELEASE( m_pDIJoypad ) ;
	_RELEASE( m_pDIMouse ) ;
}

//-----------------------------------------------------------------------------
// Direct Input ������
//-----------------------------------------------------------------------------
HRESULT DxInput::Create(HINSTANCE hInstApp) {
	HRESULT		hr;

	hr = DirectInput8Create(hInstApp, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pDInput, NULL);
	return ( hr ) ;

}
//-----------------------------------------------------------------------------
// �L�[�{�[�h�p�I�u�W�F�N�g�쐬
//-----------------------------------------------------------------------------
HRESULT DxInput::InitKeyboard(HWND hWnd) {
	HRESULT		hr;

	//�L�[�{�[�h�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIKeyboard, NULL); 
	if (FAILED(hr)) return ( hr ) ;  // �f�o�C�X�̍쐬�Ɏ��s

	//�L�[�{�[�h�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	hr = m_pDIKeyboard->SetDataFormat(&c_dfDIKeyboard);	
	if (FAILED(hr)) return ( hr ) ; // �f�o�C�X�̍쐬�Ɏ��s

	//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) return ( hr ) ; // ���[�h�̐ݒ�Ɏ��s

	//�L�[�{�[�h���͐���J�n
	m_pDIKeyboard->Acquire();

	return ( hr ) ;
}

//-----------------------------------------------------------------------------
// �֐����@�F�@GetKeyboard()
// �@�\�T�v�F�@�L�[�{�[�h�̏�Ԃ��擾
//-----------------------------------------------------------------------------
void DxInput::GetKeyboard()
{
	HRESULT			hr;

	hr = m_pDIKeyboard->GetDeviceState(256, m_diKeyState);
	if (hr != S_OK) m_pDIKeyboard->Acquire();
	else {
		for ( int i = 0 ; i < 256 ; i++ ){
			m_diKeyStateTrigger[i] = m_diKeyState[i] & ( m_diKeyState[i] ^ m_diKeyStateNow[i] ) ;
			m_diKeyStateRelease[i] = m_diKeyStateNow[i] & ( m_diKeyState[i] ^ m_diKeyStateNow[i] ) ;
			m_diKeyStateNow[i] = m_diKeyState[i] ;
		}
	}
}

//-----------------------------------------------------------------------------
// �֐����@�F�@isKey()
// �@�\�T�v�F�@�L�[�{�[�h�̏�Ԃ��`�F�b�N
//-----------------------------------------------------------------------------
BOOL DxInput::isKey( int key ) {
	if ( m_diKeyStateNow[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}
int DxInput::isKeyDir() {
	int dir = 0 ;
	if ( !isKey( DIK_RIGHT ) || !isKey( DIK_LEFT ) ) {
		if ( isKey( DIK_RIGHT ) )	dir |= 1 ; // 0b0001 ;
		if ( isKey( DIK_LEFT ) )	dir |= 2 ; // 0b0010 ;
	}

	if ( !isKey( DIK_UP ) || !isKey( DIK_DOWN ) ) {
		if ( isKey( DIK_UP ) )		dir |= 4 ; // 0b0100 ;
		if ( isKey( DIK_DOWN ) )	dir |= 8 ; // 0b1000
	}

	if ( !isKey( DIK_UP ) || !isKey( DIK_LEFT ) ) {
		if ( isKey( DIK_SPACE ) )		dir |= 16 ;
		if( isKey(DIK_RETURN) )			dir |= 18 ;
		if(isKey(DIK_Z))				dir |= 20 ;
	}
	return ( dir ) ;
}
//-----------------------------------------------------------------------------
// �֐����@�F�@isKeyTrigger()
// �@�\�T�v�F�@�L�[�{�[�h�̏�Ԃ��`�F�b�N�i�P���j
//-----------------------------------------------------------------------------
BOOL DxInput::isKeyTrigger( int key ) {
	if ( m_diKeyStateTrigger[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}
//-----------------------------------------------------------------------------
// �֐����@�F�@isKeyRelease()
// �@�\�T�v�F�@�L�[�{�[�h�̏�Ԃ��`�F�b�N�i���������j
//-----------------------------------------------------------------------------
BOOL DxInput::isKeyRelease( int key ) {
	if ( m_diKeyStateRelease[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}

/*
//-----------------------------------------------------------------------------
//	�W���C�X�e�B�b�N�E�f�o�C�X��񋓁i�R�[���o�b�N�֐��j
//-----------------------------------------------------------------------------
BOOL CALLBACK GetJoystickCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT hr;

	hr = pDInput->CreateDevice(lpddi->guidInstance, &pDIJoypad, NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;	// ���̃f�o�C�X���

	return DIENUM_STOP;	// �f�o�C�X�̗񋓂𒆎~

}

//-----------------------------------------------------------------------------
// Joypad�p�I�u�W�F�N�g�쐬
//-----------------------------------------------------------------------------
HRESULT DxInput::InitJoypad(HWND hWnd) {
	HRESULT		hr;

	// �W���C�p�b�h��T��
	pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)GetJoystickCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (!pDIJoypad)
		return false;

	// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	hr = pDIJoypad->SetDataFormat(&c_dfDIJoystick);
	if (FAILED(hr))
		return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = pDIJoypad->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
		return false; // ���[�h�̐ݒ�Ɏ��s

	// ���̒l�͈̔͂�ݒ�
	// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
	// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
	// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�́A�֌W�Ȃ�)
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize	= sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwHow	= DIPH_BYOFFSET; 
	diprg.lMin	= RANGE_MIN;
	diprg.lMax	= RANGE_MAX;
	// X���͈̔͂�ݒ�
	diprg.diph.dwObj	= DIJOFS_X; 
	pDIJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
	// Y���͈̔͂�ݒ�
	diprg.diph.dwObj	= DIJOFS_Y;
	pDIJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

	// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
	// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
	// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
	DIPROPDWORD				dipdw;
	dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize	= sizeof(dipdw.diph);
	dipdw.diph.dwHow		= DIPH_BYOFFSET;
	dipdw.dwData			= DEADZONE;
	//X���̖����]�[����ݒ�
	dipdw.diph.dwObj		= DIJOFS_X;
	pDIJoypad->SetProperty( DIPROP_DEADZONE, &dipdw.diph);
	//Y���̖����]�[����ݒ�
	dipdw.diph.dwObj		= DIJOFS_Y;
	pDIJoypad->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		
	//�W���C�X�e�B�b�N���͐���J�n
	pDIJoypad->Acquire();
		
	return true;

}

//-----------------------------------------------------------------------------
// �֐����@�F�@GetJoypadState()
// �@�\�T�v�F�@�W���C�p�b�h�̏�Ԃ��擾
//-----------------------------------------------------------------------------
void GetJoypadState(void)
{
	HRESULT			hr;
	DIJOYSTATE		dijs;

	diJoyState = 0x00000000l;	// ������

	pDIJoypad->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
	hr = pDIJoypad->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
	if (hr == DIERR_INPUTLOST)
		pDIJoypad->Acquire();

	// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
	// y-axis (forward)
	if(dijs.lY < 0)					diJoyState |= BUTTON_UP;
	// y-axis (backward)
	if(dijs.lY > 0)					diJoyState |= BUTTON_DOWN;
	// x-axis (left)
	if(dijs.lX < 0)					diJoyState |= BUTTON_LEFT;
	// x-axis (right)
	if(dijs.lX > 0)					diJoyState |= BUTTON_RIGHT;
	// �`�{�^��
	if(dijs.rgbButtons[0] & 0x80)	diJoyState |= BUTTON_A;
	// �a�{�^��
	if(dijs.rgbButtons[1] & 0x80)	diJoyState |= BUTTON_B;
	// �b�{�^��
	if(dijs.rgbButtons[2] & 0x80)	diJoyState |= BUTTON_C;
	// �w�{�^��
	if(dijs.rgbButtons[3] & 0x80)	diJoyState |= BUTTON_X;
	// �x�{�^��
	if(dijs.rgbButtons[4] & 0x80)	diJoyState |= BUTTON_Y;
	// �y�{�^��
	if(dijs.rgbButtons[5] & 0x80)	diJoyState |= BUTTON_Z;
    // �k�{�^��
    if(dijs.rgbButtons[6] & 0x80)	diJoyState |= BUTTON_L;
	// �q�{�^��
	if(dijs.rgbButtons[7] & 0x80)	diJoyState |= BUTTON_R;
	// �r�s�`�q�s�{�^��
	if(dijs.rgbButtons[8] & 0x80)	diJoyState |= BUTTON_START;
	// �l�{�^��
	if(dijs.rgbButtons[9] & 0x80)	diJoyState |= BUTTON_M;

}
*/

//-----------------------------------------------------------------------------
// �}�E�X�p�I�u�W�F�N�g�쐬
//-----------------------------------------------------------------------------
HRESULT DxInput::InitMouse(HWND hWnd) {
	HRESULT		hr;

	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL);
	if (FAILED(hr)) return ( hr ) ;	// �f�o�C�X�̍쐬�Ɏ��s

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIMouse->SetDataFormat(&c_dfDIMouse);	// �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	if (FAILED(hr))	return ( hr ) ;	// �f�[�^�t�H�[�}�b�g�Ɏ��s

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) return ( hr ) ;	// ���[�h�̐ݒ�Ɏ��s

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD		diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	diprop.dwData = DIPROPAXISMODE_ABS;
	hr = m_pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(hr)) return ( hr ) ;	// �f�o�C�X�̐ݒ�Ɏ��s

	// ���͐���J�n
	m_pDIMouse->Acquire();

	return ( hr ) ;

}

//-----------------------------------------------------------------------------
// �֐����@�F�@GetMouseState()
// �@�\�T�v�F�@�}�E�X�̏�Ԃ��擾
//-----------------------------------------------------------------------------
void DxInput::GetMouse()
{
	HRESULT			hr;
	
	hr = m_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_diMouseState);
	if (hr != S_OK) m_pDIMouse->Acquire();
	else {
		for ( int i = 0 ; i < 4 ; i++ ){
			m_MouseButtonTrigger[i] = m_diMouseState.rgbButtons[i] & ( m_diMouseState.rgbButtons[i] ^ m_MouseButtonNow[i] ) ;
			m_MouseButtonRelease[i] = m_MouseButtonNow[i] & ( m_diMouseState.rgbButtons[i] ^ m_MouseButtonNow[i] ) ;
			m_MouseButtonNow[i] = m_diMouseState.rgbButtons[i] ;
		}
	}

//#if DEBUG
//	char buf[80];
//	wsprintf(buf, "(%d, %d, %d) %s %s %s",
//		diMouseState.lX,
//		diMouseState.lY,
//		diMouseState.lZ,
//		(diMouseState.rgbButtons[0] & 0x80) ? "Left" : "--",
//		(diMouseState.rgbButtons[1] & 0x80) ? "Right" : "--",
//		(diMouseState.rgbButtons[2] & 0x80) ? "Center" : "--");
//	strOut(200, 0, buf, RGB(255, 255, 255), 10, "�l�r ����", FALSE);
//#endif

}

//-----------------------------------------------------------------------------
// �֐����@�F�@isMouse()
// �@�\�T�v�F�@�}�E�X�̃{�^���̏�Ԃ��`�F�b�N
//-----------------------------------------------------------------------------
BOOL DxInput::isMouse( int key ) {
	if ( m_MouseButtonNow[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}
BOOL DxInput::isMouseTrigger( int key ) {
	if ( m_MouseButtonTrigger[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}
BOOL DxInput::isMouseRelease( int key ) {
	if ( m_MouseButtonRelease[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}
