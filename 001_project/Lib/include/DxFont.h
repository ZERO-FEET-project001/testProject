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

//�t�H���g�e�L�X�g��`�N���X
class DxFont
{
	DxWin*		m_pDxw ;

	// �t�H���g�֘A
	LPD3DXFONT	m_pFont ;	// ID3DXFont


public:
	DxFont(DxWin* pDxw);	//�R���X�g���N�^
	~DxFont();	//�f�X�g���N�^

	HRESULT Create(int height , int width , LPCTSTR lpszFontName) ;
	HRESULT DrawW(FONT* pFont);
	HRESULT DrawA(FONT* pFont);
};

