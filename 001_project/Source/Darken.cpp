#include "TaskFuncs.h"


/*------------------------------------------------------

					�Ó]

------------------------------------------------------*/
/*======================================================

			�R���X�g���N�^

=======================================================*/
Darken::Darken(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi) {

	// ����������
	setTaskFlag(TASK_FLAG_OBJECT) ;
	//NAME�ݒ�
	m_cpName = "Darken" ;
	//Texture�̃Z�b�g���s��
	GetTexture( pt_Texture->m_pg_black->TextureSet() );
	//RECT�̎w��
	SetRect(0,0,800,600);

	//�D�揇��
	m_fPriority = 0;

	//���W
	x = DARKEN_X;
	y = DARKEN_Y;
	z = DARKEN_Z;//��ʕύX�ɍ�����̂ň�Ԏ�O�ɗ��Ă��炤

	m_pDxi = pDxi ;
	m_alpha = 0;
	m_alpha_flg = false ;
	m_alpha_count = 0;
	//�A���t�@�l�̎w������Ȃ���255���Z�b�g
	SetAlpha(m_alpha);


};
/*======================================================

			�Ó]��Main

=======================================================*/
void Darken::main() {

	if(!m_alpha_flg)
	{
		if(m_alpha_count == 0)
		{
			m_alpha += 10;
		}
		if(m_alpha >= ALPHA_MAX)
		{
			m_alpha = ALPHA_MAX;
			m_alpha_count++;
			if(m_alpha_count >= 20)
			{
				m_alpha_count = 0;
				m_alpha_flg = true ;
			}
		}
	}
	else if(m_alpha_flg)
	{
		m_alpha -= 10;
		if(m_alpha <= 0)
		{
			Delete();
		}
	}

	SetAlpha(m_alpha);
};
