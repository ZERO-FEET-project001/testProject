#include "TaskFuncs.h"


/*------------------------------------------------------

					暗転

------------------------------------------------------*/
/*======================================================

			コンストラクタ

=======================================================*/
Darken::Darken(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi) {

	// 初期化処理
	setTaskFlag(TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "Darken" ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_black->TextureSet() );
	//RECTの指定
	SetRect(0,0,800,600);

	//優先順位
	m_fPriority = 0;

	//座標
	x = DARKEN_X;
	y = DARKEN_Y;
	z = DARKEN_Z;//画面変更に作ったので一番手前に来てもらう

	m_pDxi = pDxi ;
	m_alpha = 0;
	m_alpha_flg = false ;
	m_alpha_count = 0;
	//アルファ値の指定引数なしで255をセット
	SetAlpha(m_alpha);


};
/*======================================================

			暗転のMain

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
