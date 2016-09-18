#include "DxFont.h"
#include "Macro.h"

//---------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------
DxFont::DxFont(DxWin* pDxw) {
	m_pDxw = pDxw ;
	m_pFont = NULL ;
}

//---------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------
DxFont::~DxFont() {
	// �X�v���C�g�j��
	_RELEASE( m_pFont ) ;
}

//---------------------------------------------------
// �_���t�H���g�̍쐬
//---------------------------------------------------
HRESULT DxFont::Create(int height , int width , LPCTSTR lpszFontName) {
	HRESULT hr = S_FALSE;

    //�����񃌃��_�����O�̏�����
	hr = D3DXCreateFont(m_pDxw->isDevice(),
		height,                 //����
		width,                  //��
		FW_REGULAR,         //����(BOLD:�����j
		NULL,               //����
		FALSE,              //�Α�
		SHIFTJIS_CHARSET,   //�������
		OUT_DEFAULT_PRECIS, //�Œ�
		PROOF_QUALITY,      //�Œ�
		FIXED_PITCH | FF_MODERN,
		lpszFontName,           //�t�H���g
		&m_pFont
	) ;

	return hr;
}
//---------------------------------------------------
// �t�H���g�̏����o��
//---------------------------------------------------
HRESULT DxFont::DrawW(FONT* pFont) {
	HRESULT hr = S_FALSE;

	if ( pFont->TEXT == NULL ) { return ( S_OK ) ; }

	RECT rect = {pFont->x, pFont->y, 0, 0}; //�\���̈�
	hr = m_pFont->DrawText(
		NULL,
		(LPCTSTR)pFont->TEXT,
		-1,             //�\���T�C�Y(-1�őS��)
		&rect,          //�\���͈�
		DT_CALCRECT,    //�\���͈͂ɒ���
		NULL
	);

	//���̃T�C�Y�Ń����_�����O
	hr = m_pFont->DrawText(
		NULL,
		(LPCTSTR)pFont->TEXT,
		-1,                     //�\���T�C�Y(-1�őS��)
		&rect,                  //�\���͈�
		DT_LEFT | DT_BOTTOM,    //���l�߂ŗ��[����
		pFont->color
	);            //�F

	return ( hr ) ;
}

//---------------------------------------------------
// �t�H���g�̏����o��
//---------------------------------------------------
HRESULT DxFont::DrawA(FONT* pFont) {
	HRESULT hr = S_FALSE;

	if ( pFont->TEXT == NULL ) { return ( S_OK ) ; }

	RECT rect = {pFont->x, pFont->y, 0, 0}; //�\���̈�
	hr = m_pFont->DrawTextA(
		NULL,
		(LPCSTR)pFont->TEXT,
		-1,             //�\���T�C�Y(-1�őS��)
		&rect,          //�\���͈�
		DT_CALCRECT,    //�\���͈͂ɒ���
		NULL
	);

	//���̃T�C�Y�Ń����_�����O
	hr = m_pFont->DrawTextA(
		NULL,
		(LPCSTR)pFont->TEXT,
		-1,                     //�\���T�C�Y(-1�őS��)
		&rect,                  //�\���͈�
		DT_LEFT | DT_BOTTOM,    //���l�߂ŗ��[����
		pFont->color
	);            //�F

	return ( hr ) ;
}
