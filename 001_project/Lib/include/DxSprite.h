#pragma once
#include "stdafx.h"
#include "DxWin.h"
#include "DxTexture.h"

//スプライト面定義クラス
class DxSprite
{
	// DirectX Window面
	DxWin*				m_pDxw ;

	// スプライト関連
	ID3DXSprite*        m_pSprite;        // スプライト
	D3DXVECTOR2			m_vec2BaseScale ;

public:
	DxSprite(DxWin* pDxw);	//コンストラクタ
	~DxSprite();	//デストラクタ

	HRESULT Create() ;

	HRESULT Begin(DWORD dwFlas) ;
	HRESULT End() ;

	void Scale(FLOAT sx, FLOAT sy) ;
	HRESULT Draw(DxTexture* pDxt, D3DXVECTOR3* pvect3Positon, D3DXVECTOR2* pvec2Scale , FLOAT fRotate ) {
		return ( Draw(pDxt, pvect3Positon, pvec2Scale , fRotate, NULL,NULL) ) ;
	}
	HRESULT Draw(DxTexture* pDxt, D3DXVECTOR3* pvect3Positon, D3DXVECTOR2* pvec2Scale , FLOAT fRotate, RECT *pRect,DWORD pColor) ;


	// 取得している値を返す
	DxWin* isDxWin() { return ( m_pDxw ) ; } 

};

