#include "TaskFuncs.h"
/*========================================================

			Scoreコンストラクタ

========================================================*/
ScoreLetter::ScoreLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl , int kind)
{
	// 初期化処理
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME設定
	m_cpName = "ScoreLetter" ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_scorenumber->TextureSet());

	m_g_pCTaskCtrl = g_pCTaskCtrl ;

	//切り替え用変数
	m_kind = kind ;
	
	//RECTの指定
	ChangeRect();
	
	//スコア初期位置の設定（）
	this->x = SCORELETTER_X;
	this->y = SCORELETTER_Y ;
	this->z = SCORELETTER_Z ;

	dy = SCORELETTER_SOEED ;

	m_alpha = 0 ;
	m_move_count = 0 ;
	m_move_flg = false;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(m_alpha);
};
/*========================================================

			Scoreメイン関数

========================================================*/
void ScoreLetter::main()
{
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}
};
/*========================================================

			RECT変更関数

========================================================*/
void ScoreLetter::ChangeRect()
{
	switch(m_kind)
	{
		//+100
		case SCORELETTER0:
			SetRect(0,50,75,100);
			break;
		//+500
		case SCORELETTER1:
			SetRect(75,50,150,100);
			break;
		//-200
		case SCORELETTER2:
			SetRect(150,50,225,100);
			break;
		//-600
		case SCORELETTER3:
			SetRect(225,50,300,100);
			break;
		default:
			break;
		
	}
};
/*========================================================

			動き関数

========================================================*/
void ScoreLetter::Move()
{
	//アルファ値の指定引数なしで255をセット
	SetAlpha(m_alpha);
	//動くフラグがFALSEの時
	if(m_move_flg == false)
	{
		//アルファ値を増やしていく
		m_alpha += SCORELETTER_APLHA;
	}

	//ｙ座標が一定に行ってさらに動くフラグがFALSEの時
	if(y <= SCORELETTER_Y_MAX && m_move_flg == false)
	{
		//動くカウントを足していく
		m_move_count++;
		//動きを止める
		dy=0;
		//アルファを255に指定
		m_alpha = ALPHA_MAX;
		//カウントがMAXを超えたら
		if(m_move_count >= SCORELETTER_COUNT_MAX)
		{
			//TRUEに設定
			m_move_flg = true;
		}
	}
	//動くフラグがTRUEの時
	if(m_move_flg)
	{
		//移動量を設定
		dy = SCORELETTER_SOEED;
		//アルファを減らしていく
		m_alpha -= SCORELETTER_APLHA;
		//アルファが0になったら削除
		if(m_alpha <= 0)
		{
			Delete();
		}

	}

};