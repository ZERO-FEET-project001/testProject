#include "TaskFuncs.h"


/*------------------------------------------------------

				残機

------------------------------------------------------*/
/*======================================================

			残機のコンストラクタ

=======================================================*/
Life::Life(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,int kind) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "Life" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_life->TextureSet() );
	//RECTの指定
	SetRect(LIFE_RECT_LEFT,LIFE_RECT_TOP,LIFE_RECT_RIGHT,LIFE_RECT_BOTTOM);
	//座標の設定
	x = LIFE_X;
	y = LIFE_Y;
	z = LIFE_Z;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(0);

};
/*======================================================

			残機のMain

=======================================================*/
void Life::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);
};

