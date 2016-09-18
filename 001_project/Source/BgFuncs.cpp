#include "TaskFuncs.h"


/*------------------------------------------------------

				背景

------------------------------------------------------*/
/*======================================================

			背景のコンストラクタ

=======================================================*/
Bg::Bg(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "Bg" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_bg->TextureSet() );
	//RECTの指定
	SetRect(BG_RECT_LEFT,BG_RECT_TOP,BG_RECT_RIGHT,BG_RECT_BOTTOM);

	//座標の設定
	x = BG_X;
	y = BG_Y;
	z = BG_Z;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(0);

};
/*======================================================

			背景のMain

=======================================================*/
void Bg::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);

	ModeDelete(m_g_pCTaskCtrl);
};
