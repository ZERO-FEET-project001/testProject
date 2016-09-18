#include "TaskFuncs.h"
/*========================================================

			Scoreコンストラクタ

========================================================*/
CharLetter::CharLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl ,SetSound* ps_Sound)
{
	// 初期化処理
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME設定
	m_cpName = "CharLetter" ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_char->TextureSet());
	//サウンド
	m_ps_Sound = ps_Sound;
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	//サウンド
	m_ps_Sound = ps_Sound;	
	//RECTの指定
	SetRect(0,0,520,80);
	
	//スコア初期位置の設定（）
	this->x = CHARLETTER_X;
	this->y = CHARLETTER_Y ;
	this->z = CHARLETTER_Z ;

	dy = CHARLETTER_SOEED ;

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
void CharLetter::main()
{
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		Move();
	}
};
/*========================================================

			動き関数

========================================================*/
void CharLetter::Move()
{
	//アルファ値の指定引数なしで255をセット
	SetAlpha(m_alpha);

	//動くフラグがFALSEの時
	if(m_move_flg == false)
	{
		//アルファ値を増やしていく
		m_alpha +=	CHARLETTER_APLHA;
	}

	//ｙ座標が一定に行ってさらに動くフラグがFALSEの時
	if(y <= CHARLETTER_Y_MAX && m_move_flg == false)
	{
		//動くカウントを足していく
		m_move_count++;
		//動きを止める
		dy = 0;
		//アルファを255に指定
		m_alpha = ALPHA_MAX;
		//カウントがMAXを超えたら
		if(m_move_count >= CHARLETTER_COUNT_MAX)
		{
			//TRUEに設定
			m_move_flg = true;
		}
	}

	//動くフラグがTRUEの時
	if(m_move_flg)
	{
		//移動量を設定
		dy = CHARLETTER_SOEED;
		//アルファを減らしていく
		m_alpha -= CHARLETTER_APLHA;
		//アルファが0になったら削除
		if(m_alpha <= 0)
		{
			Delete();
		}

	}

};