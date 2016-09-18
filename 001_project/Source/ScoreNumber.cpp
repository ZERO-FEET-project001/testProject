#include "TaskFuncs.h"
/*========================================================

			Scoreコンストラクタ

========================================================*/
ScoreNumber::ScoreNumber(SetTexture* pt_Texture ,int kurai , CTaskCtrl* g_pCTaskCtrl )
{
	// 初期化処理
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME設定
	m_cpName = "Score" ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_scorenumber->TextureSet());

	//位の代入
	m_kurai = kurai;
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	//自分がどのくらいかを計算する
	m_place = (  m_g_pCTaskCtrl->isGetScoreDisplay() / (int)( pow((float)COUNTER_PLACE,(float)m_kurai))) % COUNTER_PLACE ;

	//RECTの指定
	ChangeRect();

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(0);

	//スコア初期位置の設定（）
	this->x = (FLOAT)(COUNTER_X - kurai % COUNTER_MAX * COUNTER_GAP_X);
	this->y = COUNTER_Y ;
	this->z = COUNTER_Z ;

};
/*========================================================

			Scoreメイン関数

========================================================*/
void ScoreNumber::main()
{
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);
	//計算して
	m_place = ( m_g_pCTaskCtrl->isGetScoreDisplay() / (int)( pow((float)COUNTER_PLACE,(float)m_kurai))) % COUNTER_PLACE ;
	//RECTを変える
	ChangeRect();

};
/*========================================================

			RECT変更関数

========================================================*/
void ScoreNumber::ChangeRect()
{
	switch(m_place)
	{
		case 0:
			SetRect(0,0,50,50);
			break;
		case 1:
			SetRect(50,0,100,50);
			break;
		case 2:
			SetRect(100,0,150,50);
			break;
		case 3:
			SetRect(150,0,200,50);
			break;
		case 4:
			SetRect(200,0,250,50);
			break;
		case 5:
			SetRect(250,0,300,50);
			break;
		case 6:
			SetRect(300,0,350,50);
			break;
		case 7:
			SetRect(350,0,400,50);
			break;
		case 8:
			SetRect(400,0,450,50);
			break;
		case 9:
			SetRect(450,0,500,50);
			break;
		default:
			break;
		
	}
};