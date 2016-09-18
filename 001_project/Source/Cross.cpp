#include "TaskFuncs.h"


/*------------------------------------------------------

				残機

------------------------------------------------------*/
/*======================================================

			残機のコンストラクタ

=======================================================*/
Cross::Cross(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,int kind,SetSound* ps_Sound) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "Cross" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//サウンド
	m_ps_Sound = ps_Sound;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_cross->TextureSet() );
	//RECTの指定
	SetRect(CROSS_RECT_LEFT,CROSS_RECT_TOP,CROSS_RECT_RIGHT,CROSS_RECT_BOTTOM);
	//座標の設定
	x = CROSS_X;
	y = CROSS_Y;
	z = CROSS_Z;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha();
	//SE再生
	SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_batu_se);
	//ループしないで再生
	m_se->Play(FALSE);

};
/*======================================================

			残機のMain

=======================================================*/
void Cross::main() {
	ModeDelete(m_g_pCTaskCtrl);
};

