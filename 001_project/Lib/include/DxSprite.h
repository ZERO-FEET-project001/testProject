#pragma once
#include "stdafx.h"
#include "DxWin.h"
#include "DxTexture.h"

//�X�v���C�g�ʒ�`�N���X
class DxSprite
{
	// DirectX Window��
	DxWin*				m_pDxw ;

	// �X�v���C�g�֘A
	ID3DXSprite*        m_pSprite;        // �X�v���C�g
	D3DXVECTOR2			m_vec2BaseScale ;

public:
	DxSprite(DxWin* pDxw);	//�R���X�g���N�^
	~DxSprite();	//�f�X�g���N�^

	HRESULT Create() ;

	HRESULT Begin(DWORD dwFlas) ;
	HRESULT End() ;

	void Scale(FLOAT sx, FLOAT sy) ;
	HRESULT Draw(DxTexture* pDxt, D3DXVECTOR3* pvect3Positon, D3DXVECTOR2* pvec2Scale , FLOAT fRotate ) {
		return ( Draw(pDxt, pvect3Positon, pvec2Scale , fRotate, NULL,NULL) ) ;
	}
	HRESULT Draw(DxTexture* pDxt, D3DXVECTOR3* pvect3Positon, D3DXVECTOR2* pvec2Scale , FLOAT fRotate, RECT *pRect,DWORD pColor) ;


	// �擾���Ă���l��Ԃ�
	DxWin* isDxWin() { return ( m_pDxw ) ; } 

};

