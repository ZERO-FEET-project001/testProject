#include "TaskFuncs.h"


/*------------------------------------------------------

				卵の殻

------------------------------------------------------*/
/*======================================================

			卵の殻のコンストラクタ

=======================================================*/
EggShell::EggShell(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,float egg_x,float egg_y , int gamemode) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "EggShell" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_eggshell->TextureSet() );
	//RECTの指定
	SetRect(EGGSHELL_RECT_LEFT,EGGSHELL_RECT_TOP,EGGSHELL_RECT_RIGHT,EGGSHELL_RECT_BOTTOM);
	//座標の設定
	x = egg_x;
	y = egg_y;
	z = EGGSHELL_Z;
	//当たりのコリジョン
	colx = EGGSHELL_COLX ;
	coly = EGGSHELL_COLY ;

	int kind = rand()%2;
	//どっち向きかを判断いて移動量を入れる
	if(kind == 0)
	{
		dx = EGGSHELL_DX;
	}
	else
	{
		dx = -EGGSHELL_DX;
	}
	dy = EGGSHELL_DY;

	//線との当たり判定
	m_hit_line = false;

	//自分が存在するゲームモードの設定
	m_iMode = gamemode;

	//アルファ値の指定引数なしで255をセット
	SetAlpha();

};
/*======================================================

			卵の殻のMain

=======================================================*/
void EggShell::main() {
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		//動き
		Move();
		//跳ね返り
		Spring();
	}
};
/*======================================================

			卵の殻の動き

=======================================================*/
void EggShell::Move() {

	if( m_hit_line == false )
	{
		//重力
		dy += GRAVITY;
	}
	else
	{
		//dy = m_tmp_dy;
		m_hit_line = false ;
	}
	//回転
	m_rotate += EGGSHELL_RORATE ;

	//画面を超えたらデリート
	if(y >= HI_MAX)
	{
		Delete();
	}
};
/*======================================================

			卵の殻の跳ね返り

=======================================================*/
void EggShell::Spring() {
	
	//端の壁に当たったら跳ね返る
	//左
	if( x < ( EGG_LEFT_MAX + colx ))
	{
		dx = -dx;
	}
	//右
	else if(x > ( EGG_RIGHT_MAX - colx ))
	{
		dx = -dx;
	}
};

