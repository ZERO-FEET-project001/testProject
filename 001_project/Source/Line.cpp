#include "TaskFuncs.h"


/*------------------------------------------------------

				線

------------------------------------------------------*/
/*======================================================

			線のコンストラクタ

=======================================================*/
Line::Line(DxInput* pDxi,SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,LONG Mpt_x,LONG Mpt_y) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT) ;
	//NAME設定
	m_cpName = "Line" ;
	//キーボードポインタの保持
	m_pDxi = pDxi;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_line->TextureSet()  );
	//グループの設定
	m_iGroup = GROUP_LINE ;
	//RECTの指定
	SetRect(LINE_RECT_LEFT,LINE_RECT_TOP,LINE_RECT_RIGHT,LINE_RECT_BOTTOM);


	//座標の設定
	x = (float)Mpt_x;
	y = (float)Mpt_y;
	z = 0.2f;
	//当たりのコリジョン
	colx = LINE_COLX ;
	coly = LINE_COLY ;

	//卵と当たった！
	m_hit_egg = false ;
	m_alpha = ALPHA_MAX;
	m_g_pCTaskCtrl->SetLineAlpha(ALPHA_MAX);
	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;
	//アルファ値の指定引数なしで255をセット
	SetAlpha();
};
/*======================================================

			線のMain

=======================================================*/
void Line::main() {

	ModeDelete(m_g_pCTaskCtrl);

	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		m_alpha = (INT)(m_g_pCTaskCtrl->isGetLineAlpha());

		//画面外なら削除する
		if(this->x <= LINE_LEFT_MAX || this->y >= HI_MAX || this->x >= LINE_RIGHT_MAX|| this->y <= m_g_pCTaskCtrl->isGetBorderLine())
		{
			Delete();
		}


		if(m_g_pCTaskCtrl->isGetLineAlpha() <= 0)
		{
			Delete();
		}

		//キー操作
		Key();

		SetAlpha(m_alpha);
	}
};
/*======================================================

			線のKey操作

=======================================================*/
void Line::Key() {


	//Dを押すと線をすべて消せる
	if(m_pDxi->isKeyTrigger(DIK_D) || m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
	{
		Delete();
	}
};
/*======================================================

			線の当たり判定

=======================================================*/
void Line::Hit(CTaskFunc* task) {

	switch(task->m_iGroup)
	{
		//線に当たったら
		case GROUP_EGG:
			EggHit(task);
			break;
		//線に当たったら
		case GROUP_SMALLBIRD:
			break;
	}
};
/*=====================================================

	隣り合っている線のチェーンのポインタの格納関数
	引数　：　次のLINEポインタ、前のLINEポインタ

=======================================================*/
void  Line::Chain(Line* pLineNext ,Line* pLinePrev){

	//次のブロックポインタの格納
	m_pLineNext = pLineNext;
	//前のブロックポインタの格納
	m_pLinePrev = pLinePrev;
};
/*======================================================

			線と卵のあたり

=======================================================*/
void  Line::EggHit(CTaskFunc* egg){

	if(this->y + this->coly > egg->y + egg->coly
		&& this->x > egg->x - egg->colx 
		&& this->x < egg->x + egg->colx)  
	{
			m_alpha -= 85;
			m_g_pCTaskCtrl->SetLineAlpha((FLOAT)m_alpha);
	}
};