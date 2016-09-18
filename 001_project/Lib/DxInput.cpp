#include "DxInput.h"
#include "Macro.h"

#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

//-----------------------------------------------------------------------------
// Joypad用設定値
//-----------------------------------------------------------------------------
#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値

//---------------------------------------------------
// コンストラクタ
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
// デストラクタ
//---------------------------------------------------
DxInput::~DxInput() {
	_RELEASE( m_pDInput ) ;
	_RELEASE( m_pDIJoypad ) ;
	_RELEASE( m_pDIMouse ) ;
}

//-----------------------------------------------------------------------------
// Direct Input 初期化
//-----------------------------------------------------------------------------
HRESULT DxInput::Create(HINSTANCE hInstApp) {
	HRESULT		hr;

	hr = DirectInput8Create(hInstApp, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pDInput, NULL);
	return ( hr ) ;

}
//-----------------------------------------------------------------------------
// キーボード用オブジェクト作成
//-----------------------------------------------------------------------------
HRESULT DxInput::InitKeyboard(HWND hWnd) {
	HRESULT		hr;

	//キーボード用にデバイスオブジェクトを作成
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIKeyboard, NULL); 
	if (FAILED(hr)) return ( hr ) ;  // デバイスの作成に失敗

	//キーボード用のデータ・フォーマットを設定
	hr = m_pDIKeyboard->SetDataFormat(&c_dfDIKeyboard);	
	if (FAILED(hr)) return ( hr ) ; // デバイスの作成に失敗

	//モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) return ( hr ) ; // モードの設定に失敗

	//キーボード入力制御開始
	m_pDIKeyboard->Acquire();

	return ( hr ) ;
}

//-----------------------------------------------------------------------------
// 関数名　：　GetKeyboard()
// 機能概要：　キーボードの状態を取得
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
// 関数名　：　isKey()
// 機能概要：　キーボードの状態をチェック
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
// 関数名　：　isKeyTrigger()
// 機能概要：　キーボードの状態をチェック（単発）
//-----------------------------------------------------------------------------
BOOL DxInput::isKeyTrigger( int key ) {
	if ( m_diKeyStateTrigger[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}
//-----------------------------------------------------------------------------
// 関数名　：　isKeyRelease()
// 機能概要：　キーボードの状態をチェック（離した時）
//-----------------------------------------------------------------------------
BOOL DxInput::isKeyRelease( int key ) {
	if ( m_diKeyStateRelease[key] & 0x80 ) { return ( TRUE ) ; }
	else { return ( FALSE ) ; }
}

/*
//-----------------------------------------------------------------------------
//	ジョイスティック・デバイスを列挙（コールバック関数）
//-----------------------------------------------------------------------------
BOOL CALLBACK GetJoystickCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT hr;

	hr = pDInput->CreateDevice(lpddi->guidInstance, &pDIJoypad, NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;	// 次のデバイスを列挙

	return DIENUM_STOP;	// デバイスの列挙を中止

}

//-----------------------------------------------------------------------------
// Joypad用オブジェクト作成
//-----------------------------------------------------------------------------
HRESULT DxInput::InitJoypad(HWND hWnd) {
	HRESULT		hr;

	// ジョイパッドを探す
	pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)GetJoystickCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (!pDIJoypad)
		return false;

	// ジョイスティック用のデータ・フォーマットを設定
	hr = pDIJoypad->SetDataFormat(&c_dfDIJoystick);
	if (FAILED(hr))
		return false; // データフォーマットの設定に失敗

	// モードを設定（フォアグラウンド＆非排他モード）
	hr = pDIJoypad->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
		return false; // モードの設定に失敗

	// 軸の値の範囲を設定
	// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
	// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
	// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドは、関係なし)
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize	= sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwHow	= DIPH_BYOFFSET; 
	diprg.lMin	= RANGE_MIN;
	diprg.lMax	= RANGE_MAX;
	// X軸の範囲を設定
	diprg.diph.dwObj	= DIJOFS_X; 
	pDIJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
	// Y軸の範囲を設定
	diprg.diph.dwObj	= DIJOFS_Y;
	pDIJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

	// 各軸ごとに、無効のゾーン値を設定する。
	// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
	// 指定する値は、10000に対する相対値(2000なら20パーセント)。
	DIPROPDWORD				dipdw;
	dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize	= sizeof(dipdw.diph);
	dipdw.diph.dwHow		= DIPH_BYOFFSET;
	dipdw.dwData			= DEADZONE;
	//X軸の無効ゾーンを設定
	dipdw.diph.dwObj		= DIJOFS_X;
	pDIJoypad->SetProperty( DIPROP_DEADZONE, &dipdw.diph);
	//Y軸の無効ゾーンを設定
	dipdw.diph.dwObj		= DIJOFS_Y;
	pDIJoypad->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		
	//ジョイスティック入力制御開始
	pDIJoypad->Acquire();
		
	return true;

}

//-----------------------------------------------------------------------------
// 関数名　：　GetJoypadState()
// 機能概要：　ジョイパッドの状態を取得
//-----------------------------------------------------------------------------
void GetJoypadState(void)
{
	HRESULT			hr;
	DIJOYSTATE		dijs;

	diJoyState = 0x00000000l;	// 初期化

	pDIJoypad->Poll();	// ジョイスティックにポールをかける
	hr = pDIJoypad->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
	if (hr == DIERR_INPUTLOST)
		pDIJoypad->Acquire();

	// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
	// y-axis (forward)
	if(dijs.lY < 0)					diJoyState |= BUTTON_UP;
	// y-axis (backward)
	if(dijs.lY > 0)					diJoyState |= BUTTON_DOWN;
	// x-axis (left)
	if(dijs.lX < 0)					diJoyState |= BUTTON_LEFT;
	// x-axis (right)
	if(dijs.lX > 0)					diJoyState |= BUTTON_RIGHT;
	// Ａボタン
	if(dijs.rgbButtons[0] & 0x80)	diJoyState |= BUTTON_A;
	// Ｂボタン
	if(dijs.rgbButtons[1] & 0x80)	diJoyState |= BUTTON_B;
	// Ｃボタン
	if(dijs.rgbButtons[2] & 0x80)	diJoyState |= BUTTON_C;
	// Ｘボタン
	if(dijs.rgbButtons[3] & 0x80)	diJoyState |= BUTTON_X;
	// Ｙボタン
	if(dijs.rgbButtons[4] & 0x80)	diJoyState |= BUTTON_Y;
	// Ｚボタン
	if(dijs.rgbButtons[5] & 0x80)	diJoyState |= BUTTON_Z;
    // Ｌボタン
    if(dijs.rgbButtons[6] & 0x80)	diJoyState |= BUTTON_L;
	// Ｒボタン
	if(dijs.rgbButtons[7] & 0x80)	diJoyState |= BUTTON_R;
	// ＳＴＡＲＴボタン
	if(dijs.rgbButtons[8] & 0x80)	diJoyState |= BUTTON_START;
	// Ｍボタン
	if(dijs.rgbButtons[9] & 0x80)	diJoyState |= BUTTON_M;

}
*/

//-----------------------------------------------------------------------------
// マウス用オブジェクト作成
//-----------------------------------------------------------------------------
HRESULT DxInput::InitMouse(HWND hWnd) {
	HRESULT		hr;

	// マウス用にデバイスオブジェクトを作成
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL);
	if (FAILED(hr)) return ( hr ) ;	// デバイスの作成に失敗

	// データフォーマットを設定
	hr = m_pDIMouse->SetDataFormat(&c_dfDIMouse);	// マウス用のデータ・フォーマットを設定
	if (FAILED(hr))	return ( hr ) ;	// データフォーマットに失敗

	// モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) return ( hr ) ;	// モードの設定に失敗

	// デバイスの設定
	DIPROPDWORD		diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
	diprop.dwData = DIPROPAXISMODE_ABS;
	hr = m_pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(hr)) return ( hr ) ;	// デバイスの設定に失敗

	// 入力制御開始
	m_pDIMouse->Acquire();

	return ( hr ) ;

}

//-----------------------------------------------------------------------------
// 関数名　：　GetMouseState()
// 機能概要：　マウスの状態を取得
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
//	strOut(200, 0, buf, RGB(255, 255, 255), 10, "ＭＳ 明朝", FALSE);
//#endif

}

//-----------------------------------------------------------------------------
// 関数名　：　isMouse()
// 機能概要：　マウスのボタンの状態をチェック
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
