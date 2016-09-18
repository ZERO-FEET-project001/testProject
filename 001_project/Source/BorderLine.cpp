#include "TaskFuncs.h"


/*------------------------------------------------------

				ゲームオーバー

------------------------------------------------------*/
/*======================================================

			ゲームオーバーのコンストラクタ

=======================================================*/
BorderLine::BorderLine(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture,SetSound* ps_Sound) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "BORDERLINE" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//サウンド
	m_ps_Sound = ps_Sound;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_border->TextureSet() );
	//レクトの設定
	SetRect(BORDERLINE_RECT_LEFT,BORDERLINE_RECT_TOP,BORDERLINE_RECT_RIGHT,BORDERLINE_RECT_BOTTOM);
	//座標の設定
	x = BORDERLINE_X;
	y = BORDERLINE_Y;
	z = BORDERLINE_Z;

	//座標をセット
	m_move_y = y ;
	m_move_flg = false ;
	m_move_count = 1;
	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(0);
	
};
/*======================================================

			境界線のMain

=======================================================*/
void BorderLine::main() {

	ModeNew(m_g_pCTaskCtrl,TRUE);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}
	ModeDelete(m_g_pCTaskCtrl);
};
/*======================================================

			境界線の動き

=======================================================*/
void BorderLine::Move() {

	if(m_move_flg == false)
	{
		if(m_g_pCTaskCtrl->isGetScore() >= BORDERSCORE * m_move_count)
		{
			m_move_count++;
			m_move_flg = true ;
			m_move_y += BORDERLINE_MOVE_Y * m_move_count ;
			new CharLetter(m_pt_Texture,m_g_pCTaskCtrl,m_ps_Sound);
		}
	}

	if(m_move_flg)
	{
		if(y < m_move_y)
		{
			y += 0.5f;
			if(y >= m_move_y)
			{
				m_move_flg = false;
			}
		}
	}

	m_g_pCTaskCtrl->SetBorderLine(y);
};

