#include "TaskFuncs.h"

/*------------------------------------------------------

				鳥の巣に入った時のエフェクト

------------------------------------------------------*/
/*======================================================

			鳥の巣に入った時のエフェクトのコンストラクタ

=======================================================*/
InPoint::InPoint( SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl , float nibus_x ,float nibus_y , int line_count) {

	// 初期化処理
	setTaskFlag( TASK_FLAG_OBJECT) ;

	//NAME設定
	m_cpName = "InPoint" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_point->TextureSet() );

	//RECTの指定
	if(m_g_pCTaskCtrl->isGetLinePoint(line_count) == 2.0f)
	{
		SetRect(128,0,192,64);
	}
	else if(m_g_pCTaskCtrl->isGetLinePoint(line_count) == 1.5f)
	{
		SetRect(64,0,128,64);
	}
	else if(m_g_pCTaskCtrl->isGetLinePoint(line_count) == 1.0f)
	{
		SetRect(0,0,64,64);
	}

	//初期位置の指定
	x = nibus_x ;
	y = nibus_y ;
	z =  0.1f;

	dy = -0.5f;
	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;
	//アルファのセット
	m_alpha = ALPHA_MAX;
	//アルファ値の指定引数なしで255をセット
	SetAlpha();

};
/*======================================================

			鳥の巣に入った時のエフェクトのMain

=======================================================*/
void InPoint::main() {

	ModeDelete(m_g_pCTaskCtrl);

	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}

};
/*======================================================

			動き

=======================================================*/
void InPoint::Move() {
	SetAlpha(m_alpha);

	if(m_alpha >= 0)
	{
		m_alpha -= 5;
		if(m_alpha <= 0)
		{
			Delete();
		}
	}
};
