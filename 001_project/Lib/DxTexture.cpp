#include "DxTexture.h"
#include "Macro.h"
//---------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------
DxTexture::DxTexture(DxWin* pDxw) {
	m_pDxw = pDxw ; 
	m_RotationCenter = D3DXVECTOR2( 0.0f,0.0f ) ;
	m_Translation = D3DXVECTOR2( 0.0f,0.0f ) ;

	m_pTexture = NULL ;
}
//---------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------
DxTexture::~DxTexture() {
	// �I�u�W�F�N�g�j��
	_RELEASE( m_pTexture ) ;
}

//---------------------------------------------------
// �I�u�W�F�N�g�̓ǂݍ���
//
//  lpszFilename	�t�@�C����
//  uLevel			���x��
//---------------------------------------------------
HRESULT DxTexture::Load(LPCTSTR lpszFilename, BOOL bMode)
{
	HRESULT hr = S_FALSE;
	IDirect3DSurface9* pSurface = NULL ;

	// �I�u�W�F�N�g�̓ǂݍ���
	if (SUCCEEDED(hr)) hr = ::D3DXCreateTextureFromFile(m_pDxw->isDevice(), lpszFilename, &m_pTexture);

	// �T�[�t�F�C�X�擾
	if (SUCCEEDED(hr)) hr = m_pTexture->GetSurfaceLevel(0, &pSurface);
	if (SUCCEEDED(hr)) hr = pSurface->GetDesc(&m_sSurfaceInfo);
	_RELEASE( pSurface ) ;

	// �摜�t�@�C�������擾
	if (SUCCEEDED(hr)) hr= D3DXGetImageInfoFromFile(lpszFilename,&m_ImageInfo);
	m_TureScale.x = (FLOAT)(m_ImageInfo.Width) / m_sSurfaceInfo.Width ;
	m_TureScale.y = (FLOAT)(m_ImageInfo.Height) / m_sSurfaceInfo.Height ;

	// �Z���^�[�𒆐S�ɃZ�b�g����
	if ( bMode ) {
		m_RotationCenter = D3DXVECTOR2( (FLOAT)m_ImageInfo.Width/2.0f,(FLOAT)m_ImageInfo.Height/2.0f ) ;
		m_Translation = D3DXVECTOR2( -(FLOAT)m_ImageInfo.Width/2.0f,-(FLOAT)m_ImageInfo.Height/2.0f ) ;
	}

	// ���s������j��
	if (FAILED(hr)) DxTexture::~DxTexture();

	return hr;
}
//---------------------------------------------------
// �摜�̒��S�̐ݒ�
//---------------------------------------------------
void DxTexture::SetCenter(RECT rect){

	m_RotationCenter = D3DXVECTOR2( (FLOAT)(rect.right-rect.left)/2.0f,(FLOAT)(rect.bottom-rect.top)/2.0f ) ;
	m_Translation = D3DXVECTOR2( -(FLOAT)(rect.right-rect.left)/2.0f,-(FLOAT)(rect.bottom-rect.top)/2.0f ) ;	
}
