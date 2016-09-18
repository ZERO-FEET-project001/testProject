#pragma once
#include "stdafx.h"
#include "DxWin.h"

typedef	struct	tagFONT	FONT;
struct tagFONT {
	int			x ;
	int			y ;
	D3DCOLOR	color ;
	char		*TEXT ;
} ;

//フォントテキスト定義クラス
class DxFont
{
	DxWin*		m_pDxw ;

	// フォント関連
	LPD3DXFONT	m_pFont ;	// ID3DXFont


public:
	DxFont(DxWin* pDxw);	//コンストラクタ
	~DxFont();	//デストラクタ

	HRESULT Create(int height , int width , LPCTSTR lpszFontName) ;
	HRESULT DrawW(FONT* pFont);
	HRESULT DrawA(FONT* pFont);
};

