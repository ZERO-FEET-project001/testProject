#include "DxTexture.h"
#include "Macro.h"
//---------------------------------------------------
// コンストラクタ
//---------------------------------------------------
DxTexture::DxTexture(DxWin* pDxw) {
	m_pDxw = pDxw ; 
	m_RotationCenter = D3DXVECTOR2( 0.0f,0.0f ) ;
	m_Translation = D3DXVECTOR2( 0.0f,0.0f ) ;

	m_pTexture = NULL ;
}
//---------------------------------------------------
// デストラクタ
//---------------------------------------------------
DxTexture::~DxTexture() {
	// オブジェクト破棄
	_RELEASE( m_pTexture ) ;
}

//---------------------------------------------------
// オブジェクトの読み込み
//
//  lpszFilename	ファイル名
//  uLevel			レベル
//---------------------------------------------------
HRESULT DxTexture::Load(LPCTSTR lpszFilename, BOOL bMode)
{
	HRESULT hr = S_FALSE;
	IDirect3DSurface9* pSurface = NULL ;

	// オブジェクトの読み込み
	if (SUCCEEDED(hr)) hr = ::D3DXCreateTextureFromFile(m_pDxw->isDevice(), lpszFilename, &m_pTexture);

	// サーフェイス取得
	if (SUCCEEDED(hr)) hr = m_pTexture->GetSurfaceLevel(0, &pSurface);
	if (SUCCEEDED(hr)) hr = pSurface->GetDesc(&m_sSurfaceInfo);
	_RELEASE( pSurface ) ;

	// 画像ファイル情報を取得
	if (SUCCEEDED(hr)) hr= D3DXGetImageInfoFromFile(lpszFilename,&m_ImageInfo);
	m_TureScale.x = (FLOAT)(m_ImageInfo.Width) / m_sSurfaceInfo.Width ;
	m_TureScale.y = (FLOAT)(m_ImageInfo.Height) / m_sSurfaceInfo.Height ;

	// センターを中心にセットする
	if ( bMode ) {
		m_RotationCenter = D3DXVECTOR2( (FLOAT)m_ImageInfo.Width/2.0f,(FLOAT)m_ImageInfo.Height/2.0f ) ;
		m_Translation = D3DXVECTOR2( -(FLOAT)m_ImageInfo.Width/2.0f,-(FLOAT)m_ImageInfo.Height/2.0f ) ;
	}

	// 失敗したら破棄
	if (FAILED(hr)) DxTexture::~DxTexture();

	return hr;
}
//---------------------------------------------------
// 画像の中心の設定
//---------------------------------------------------
void DxTexture::SetCenter(RECT rect){

	m_RotationCenter = D3DXVECTOR2( (FLOAT)(rect.right-rect.left)/2.0f,(FLOAT)(rect.bottom-rect.top)/2.0f ) ;
	m_Translation = D3DXVECTOR2( -(FLOAT)(rect.right-rect.left)/2.0f,-(FLOAT)(rect.bottom-rect.top)/2.0f ) ;	
}
