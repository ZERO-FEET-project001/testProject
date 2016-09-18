#pragma once
#include "stdafx.h"
#include "DxWin.h"

//�I�u�W�F�N�g��`�N���X
class DxTexture
{
	// �X�v���C�g��
	DxWin*				m_pDxw ;

	// �X�v���C�g�֘A
	IDirect3DTexture9*  m_pTexture;       // �e�N�X�`��
	D3DXIMAGE_INFO		m_ImageInfo;
	D3DXVECTOR2			m_TureScale ;
	D3DXVECTOR2			m_RotationCenter ;//���S���W
	D3DXVECTOR2			m_Translation ;   //��]

	D3DSURFACE_DESC     m_sSurfaceInfo;   // �T�[�t�F�C�X���

public:
	DxTexture(DxWin* pDxw) ;	//�R���X�g���N�^
	~DxTexture();	//�f�X�g���N�^

	HRESULT Load(LPCTSTR lpszFilename){ return ( Load(lpszFilename, TRUE) ) ; }
	HRESULT Load(LPCTSTR lpszFilename, BOOL bMode) ;

	// �擾���Ă���l��Ԃ�
	IDirect3DTexture9* isTexture() { return (m_pTexture) ; }
	D3DXVECTOR2* isTureScale() { return (&m_TureScale) ; }
	D3DXVECTOR2* isRotationCenter() { return (&m_RotationCenter) ; }
	D3DXVECTOR2* isTranslation() { return (&m_Translation) ; }
	void SetCenter(RECT rect);
};

