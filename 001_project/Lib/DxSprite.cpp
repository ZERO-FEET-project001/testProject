#include "DxSprite.h"
#include "Macro.h"

//---------------------------------------------------
// コンストラクタ
//---------------------------------------------------
DxSprite::DxSprite(DxWin* pDxw) {
	m_pSprite = NULL ;
	m_pDxw = pDxw ; 
}

//---------------------------------------------------
// デストラクタ
//---------------------------------------------------
DxSprite::~DxSprite() {
	// スプライト破棄
	_RELEASE( m_pSprite ) ;
}

//---------------------------------------------------
// スプライト面の作成
//---------------------------------------------------
HRESULT DxSprite::Create() {
	HRESULT hr = S_FALSE;

	m_vec2BaseScale = D3DXVECTOR2( 1.0f, 1.0f ) ;

	// スプライト情報の生成
	if (SUCCEEDED(hr)) hr = ::D3DXCreateSprite(m_pDxw->isDevice(), &m_pSprite);

	// 失敗したら破棄
	if (FAILED(hr)) DxSprite::~DxSprite();

	return hr;
}

//---------------------------------------------------
// スプライト描画開始
//---------------------------------------------------
HRESULT DxSprite::Begin(DWORD dwFlas) { return ( m_pSprite->Begin(dwFlas) ) ; }

//---------------------------------------------------
// スプライト描画終了
//---------------------------------------------------
HRESULT DxSprite::End() { return ( m_pSprite->End() ) ; }

//---------------------------------------------------
// スプライト面の変換行列の設定
//---------------------------------------------------
void DxSprite::Scale(FLOAT sx, FLOAT sy) { m_vec2BaseScale = D3DXVECTOR2( sx, sy ) ; }

//---------------------------------------------------
// オブジェクトの書き出し
//---------------------------------------------------
HRESULT DxSprite::Draw(DxTexture* pDxt, D3DXVECTOR3* pvect3Positon, D3DXVECTOR2* pvec2Scale , FLOAT fRotate, RECT *pRect ,DWORD pColor) {

	HRESULT hr ;
	D3DXMATRIX	mat;            // 変換行列

	D3DXVECTOR2 vec2Scale ;
	D3DXVECTOR3 vect3Positon ;
	D3DXVECTOR2 vect2Translation ;
	D3DXVECTOR2 vect2RotationCenter ;

	vect3Positon = D3DXVECTOR3( 0,0, pvect3Positon->z ) ;

	vec2Scale = D3DXVECTOR2( pDxt->isTureScale()->x , pDxt->isTureScale()->y ) ;
	vect2Translation = D3DXVECTOR2( pDxt->isTranslation()->x, pDxt->isTranslation()->y ) ;
	vect2RotationCenter = D3DXVECTOR2( pDxt->isRotationCenter()->x, pDxt->isRotationCenter()->y ) ;

	if ( pvec2Scale ) {
		vec2Scale = D3DXVECTOR2( vec2Scale.x * pvec2Scale->x , vec2Scale.y * pvec2Scale->y ) ; 
		vect2Translation = D3DXVECTOR2(  vect2Translation.x*pvec2Scale->x,vect2Translation.y*pvec2Scale->y ) ;
		vect2RotationCenter = D3DXVECTOR2(  vect2RotationCenter.x*pvec2Scale->x,vect2RotationCenter.y*pvec2Scale->y ) ;
	}
	vect2Translation = D3DXVECTOR2( vect2Translation.x + pvect3Positon->x, vect2Translation.y + pvect3Positon->y ) ;


	::D3DXMatrixIdentity(&mat);
	::D3DXMatrixTransformation2D( &mat, NULL, 0, &vec2Scale, &vect2RotationCenter, fRotate, &vect2Translation );

	hr = m_pSprite->SetTransform(&mat) ;
	if (SUCCEEDED(hr)) {
		hr = m_pSprite->Draw(
			pDxt->isTexture(),// LPDIRECT3DTEXTURE9 pTexture
			pRect,			// CONST RECT *pSrcRect
			NULL,			// CONST D3DXVECTOR3 *pvect3
			&vect3Positon,	// CONST D3DXVECTOR3 *pPosition
			pColor		// D3DCOLOR Color
		);
	}
	return ( hr ) ;
}