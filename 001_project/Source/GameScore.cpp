#include "TaskFuncs.h"
/*========================================================

			GameOverの時のスコアコンストラクタ

========================================================*/
GameScore::GameScore(SetTexture* pt_Texture ,int kurai , CTaskCtrl* g_pCTaskCtrl )
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
	m_place = (  m_g_pCTaskCtrl->isGetScore() / (int)( pow((float)GAMEOVER_SCORE_PLACE,(float)m_kurai))) % GAMEOVER_SCORE_PLACE ;

	//RECTの指定
	ChangeRect();

	//自分が存在するゲームモードの設定
	m_iMode = GAME_OVER;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(0);

	m_scale = D3DXVECTOR2(2.0f,2.0f) ;

	//スコア初期位置の設定（）
	this->x = (FLOAT)(GAMEOVER_SCORE_X - kurai % GAMEOVER_SCORE_MAX * GAMEOVER_SCORE_GAP_X);
	this->y = GAMEOVER_SCORE_Y ;
	this->z = GAMEOVER_SCORE_Z ;

};
/*========================================================

			GameOverの時のスコアメイン関数

========================================================*/
void GameScore::main()
{
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);

};
/*========================================================

			RECT変更関数

========================================================*/
void GameScore::ChangeRect()
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