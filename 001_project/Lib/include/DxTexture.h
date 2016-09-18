#pragma once
#include "stdafx.h"
#include "DxWin.h"

//オブジェクト定義クラス
class DxTexture
{
	// スプライト面
	DxWin*				m_pDxw ;

	// スプライト関連
	IDirect3DTexture9*  m_pTexture;       // テクスチャ
	D3DXIMAGE_INFO		m_ImageInfo;
	D3DXVECTOR2			m_TureScale ;
	D3DXVECTOR2			m_RotationCenter ;//中心座標
	D3DXVECTOR2			m_Translation ;   //回転

	D3DSURFACE_DESC     m_sSurfaceInfo;   // サーフェイス情報

public:
	DxTexture(DxWin* pDxw) ;	//コンストラクタ
	~DxTexture();	//デストラクタ

	HRESULT Load(LPCTSTR lpszFilename){ return ( Load(lpszFilename, TRUE) ) ; }
	HRESULT Load(LPCTSTR lpszFilename, BOOL bMode) ;

	// 取得している値を返す
	IDirect3DTexture9* isTexture() { return (m_pTexture) ; }
	D3DXVECTOR2* isTureScale() { return (&m_TureScale) ; }
	D3DXVECTOR2* isRotationCenter() { return (&m_RotationCenter) ; }
	D3DXVECTOR2* isTranslation() { return (&m_Translation) ; }
	void SetCenter(RECT rect);
};

