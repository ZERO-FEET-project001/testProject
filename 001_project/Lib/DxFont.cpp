#include "DxFont.h"
#include "Macro.h"

//---------------------------------------------------
// コンストラクタ
//---------------------------------------------------
DxFont::DxFont(DxWin* pDxw) {
	m_pDxw = pDxw ;
	m_pFont = NULL ;
}

//---------------------------------------------------
// デストラクタ
//---------------------------------------------------
DxFont::~DxFont() {
	// スプライト破棄
	_RELEASE( m_pFont ) ;
}

//---------------------------------------------------
// 論理フォントの作成
//---------------------------------------------------
HRESULT DxFont::Create(int height , int width , LPCTSTR lpszFontName) {
	HRESULT hr = S_FALSE;

    //文字列レンダリングの初期化
	hr = D3DXCreateFont(m_pDxw->isDevice(),
		height,                 //高さ
		width,                  //幅
		FW_REGULAR,         //普通(BOLD:太字）
		NULL,               //下線
		FALSE,              //斜体
		SHIFTJIS_CHARSET,   //文字ｾｯﾄ
		OUT_DEFAULT_PRECIS, //固定
		PROOF_QUALITY,      //固定
		FIXED_PITCH | FF_MODERN,
		lpszFontName,           //フォント
		&m_pFont
	) ;

	return hr;
}
//---------------------------------------------------
// フォントの書き出し
//---------------------------------------------------
HRESULT DxFont::DrawW(FONT* pFont) {
	HRESULT hr = S_FALSE;

	if ( pFont->TEXT == NULL ) { return ( S_OK ) ; }

	RECT rect = {pFont->x, pFont->y, 0, 0}; //表示領域
	hr = m_pFont->DrawText(
		NULL,
		(LPCTSTR)pFont->TEXT,
		-1,             //表示サイズ(-1で全部)
		&rect,          //表示範囲
		DT_CALCRECT,    //表示範囲に調整
		NULL
	);

	//そのサイズでレンダリング
	hr = m_pFont->DrawText(
		NULL,
		(LPCTSTR)pFont->TEXT,
		-1,                     //表示サイズ(-1で全部)
		&rect,                  //表示範囲
		DT_LEFT | DT_BOTTOM,    //左詰めで両端揃え
		pFont->color
	);            //色

	return ( hr ) ;
}

//---------------------------------------------------
// フォントの書き出し
//---------------------------------------------------
HRESULT DxFont::DrawA(FONT* pFont) {
	HRESULT hr = S_FALSE;

	if ( pFont->TEXT == NULL ) { return ( S_OK ) ; }

	RECT rect = {pFont->x, pFont->y, 0, 0}; //表示領域
	hr = m_pFont->DrawTextA(
		NULL,
		(LPCSTR)pFont->TEXT,
		-1,             //表示サイズ(-1で全部)
		&rect,          //表示範囲
		DT_CALCRECT,    //表示範囲に調整
		NULL
	);

	//そのサイズでレンダリング
	hr = m_pFont->DrawTextA(
		NULL,
		(LPCSTR)pFont->TEXT,
		-1,                     //表示サイズ(-1で全部)
		&rect,                  //表示範囲
		DT_LEFT | DT_BOTTOM,    //左詰めで両端揃え
		pFont->color
	);            //色

	return ( hr ) ;
}
