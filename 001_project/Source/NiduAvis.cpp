#include "TaskFuncs.h"


/*------------------------------------------------------

				鳥の巣Task

------------------------------------------------------*/
/*======================================================

			鳥の巣のコンストラクタ

=======================================================*/
NibuAvis::NibuAvis(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,SetSound* ps_Sound) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT) ;
	//NAME設定
	m_cpName = "NibuAvis" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//サウンド
	m_ps_Sound = ps_Sound;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_nibu->TextureSet() );
	//RECTの指定
	SetRect(NIBUAVIS_RECT_LEFT,NIBUAVIS_RECT_TOP,NIBUAVIS_RECT_RIGHT,NIBUAVIS_RECT_BOTTOM);
	//グループの設定
	m_iGroup = GROUP_NIBUAVIS ;
	//座標の設定
	x = NIBUAVIS_X;
	y = NIBUAVIS_Y;
	z = NIBUAVIS_Z;
	//移動量
	dx = -3;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha(0);
	//当たりのコリジョン
	colx = NIBUAVIS_COLX ;
	coly = NIBUAVIS_COLY ;

	//揺らすか揺らさないか
	m_swing_flg = false;
	//揺れてる時のカウントをする
	m_swing_count = 0;
	//揺れをスタートさせる
	m_swing_start_count = 0;
	//右か左か
	m_swing_left_right_flg = true;
};
/*======================================================

			鳥の巣のMain

=======================================================*/
void NibuAvis::main() {
	ModeNew(m_g_pCTaskCtrl,TRUE);
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose() && m_bNew_Flg == false && m_g_pCTaskCtrl->isGetStartFlg())
	{
		Swing();
		Move();
	}
};
/*======================================================

			鳥の巣の動き

=======================================================*/
void NibuAvis::Move() {
	if(x <= 80 || x > 700)
	{
		dx = -dx;
	}
};
/*======================================================

			鳥の巣の揺れ関数

=======================================================*/
void NibuAvis::Swing() {

	//揺らし開始
	if(m_swing_start_count >= NIBUAVIS_SWING_COUNT_RAND)
	{
		if(m_swing_flg == false)
		{
			m_tmp_dx = dx;
			//移動ストップ
			dx = 0;
		}
		m_swing_flg = true ;
	}
	else
	{
		//揺らしカウント
		m_swing_start_count++;
	}

	//揺らし開始だったら
	if(m_swing_flg)
	{
		//揺らしている時間
		m_swing_count++;
		if(m_swing_count % 5 == 1)
		{
			//SE再生
			SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_swing_se);
			//ループしないで再生
			m_se->Play(FALSE);
		}
		//右に揺れる
		if(m_swing_left_right_flg)
		{
			//左に揺れるようにする
			m_swing_left_right_flg = false ;
			//左に座標を変更
			this->x = NIBUAVIS_SWING_X_MIN;
		}
		else 
		{
			//右に揺れるようにする
			m_swing_left_right_flg = true ;
			//右に座標をセットする
			this->x = NIBUAVIS_SWING_X_MAX;
		}
		//揺れてるカウントが一定にいったら
		if(m_swing_count >= NIBUAVIS_SWING_COUNT_MAX)
		{
			dx = m_tmp_dx ;
			int kind = rand()%5;
			switch(kind)
			{
				case 0:
					//小鳥を出現させる
					new SmallBird(m_pt_Texture , m_g_pCTaskCtrl , x , y,m_ps_Sound);
					break;
				default:
					//卵を出現させる
					new Egg(m_pt_Texture , m_g_pCTaskCtrl , x , y,m_ps_Sound);
					break;
			}
			//他のものはすべて初期化
			m_swing_count = 0;
			m_swing_start_count = 0;
			m_swing_flg = false ;
		}
	}

};
/*======================================================

			鳥の巣の当たり

=======================================================*/
void NibuAvis::Hit(CTaskFunc* task) {

	switch(task->m_iGroup)
	{
		case GROUP_EGG:
			
			break;
		case GROUP_SMALLBIRD:
			
			break;
	}
};