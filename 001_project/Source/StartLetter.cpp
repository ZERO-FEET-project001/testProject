#include "TaskFuncs.h"
/*========================================================

			スタートの文字コンストラクタ

========================================================*/
StartLetter::StartLetter(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl ,SetSound* ps_Sound)
{
	// 初期化処理
	setTaskFlag( TASK_FLAG_OBJECT ) ;
	//NAME設定
	m_cpName = "StartLetter" ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_start->TextureSet());
	//サウンド
	m_ps_Sound = ps_Sound;
	m_g_pCTaskCtrl = g_pCTaskCtrl ;
	
	//RECTの指定
	SetRect(0,0,192,64);
	
	//スコア初期位置の設定（）
	this->x = STARTLETTER_X;
	this->y = STARTLETTER_Y ;
	this->z = STARTLETTER_Z ;

	m_alpha = 0 ;
	m_move_count = 0 ;
	m_move_flg = false;
	m_kind = 0;
	m_start_count = 0;
	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(m_alpha);
};
/*========================================================

			メイン関数

========================================================*/
void StartLetter::main()
{
	ModeNew(m_g_pCTaskCtrl,FALSE);

	if(!m_g_pCTaskCtrl->isGetGamePose()&& m_bNew_Flg == false )
	{
		if(m_kind == 0)
		{
			Move();
		}
		else if(m_kind == 1)
		{
			//RECTの指定
			SetRect(0,64,192,128);
			this->y = STARTLETTER_Y ;
			m_alpha = 0 ;
			m_move_count = 0 ;
			m_move_flg = false;
			m_kind = 2;

		}
		else if(m_kind == 2)
		{
			if(m_g_pCTaskCtrl->isGetStartFlg() == false)
			{
				//SE再生
				SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_start_se);
				//ループしないで再生
				m_se->Play(FALSE);
			}
			m_g_pCTaskCtrl->SetStartFlg(TRUE);
			StartMove();
		}
	}
	//アルファ値の指定引数なしで255をセット
	SetAlpha(m_alpha);
	ModeDelete(m_g_pCTaskCtrl);
};
/*========================================================

			動き関数

========================================================*/
void StartLetter::Move()
{
	m_start_count++;
	if(m_start_count >= 100)
	{
		//ｙ座標が一定に行ってさらに動くフラグがFALSEの時
		if(m_move_flg == false)
		{
			//アルファ値を増やしていく
			m_alpha +=	STARTLETTER_APLHA;

			//動くカウントを足していく
			m_move_count++;
			if(m_alpha > ALPHA_MAX)
			{
				//アルファを255に指定
				m_alpha = ALPHA_MAX;
			}
			//カウントがMAXを超えたら
			if(m_move_count >= STARTLETTER_COUNT_MAX)
			{
				//TRUEに設定
				m_move_flg = true;
			}
		}

		//動くフラグがTRUEの時
		if(m_move_flg)
		{
			//アルファを減らしていく
			m_alpha -= STARTLETTER_APLHA;
			//アルファが0になったら削除
			if(m_alpha <= 0)
			{
				m_kind = 1;
			}
		}
	}

};
/*========================================================

			スタートの動き関数

========================================================*/
void StartLetter::StartMove()
{
	//ｙ座標が一定に行ってさらに動くフラグがFALSEの時
	if(m_move_flg == false)
	{
		//アルファ値を増やしていく
		m_alpha +=	STARTLETTER_APLHA;

		//動くカウントを足していく
		m_move_count++;
		//アルファを255に指定
		m_alpha = ALPHA_MAX;
		//カウントがMAXを超えたら
		if(m_move_count >= STARTLETTER_COUNT_MAX)
		{
			//TRUEに設定
			m_move_flg = true;
			
		}
	}

	//動くフラグがTRUEの時
	if(m_move_flg)
	{
		//アルファを減らしていく
		m_alpha -= STARTLETTER_APLHA;
		//アルファが0になったら削除
		if(m_alpha <= 0)
		{
			Delete();
		}
	}

};