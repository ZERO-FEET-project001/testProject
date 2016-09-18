#include "TaskFuncs.h"


/*------------------------------------------------------

				小鳥

------------------------------------------------------*/
/*======================================================

			小鳥のコンストラクタ

=======================================================*/
SmallBird::SmallBird(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl, float nibus_x ,float nibus_y,SetSound* ps_Sound) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT  | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT ) ;
	//NAME設定
	m_cpName = "SmallBird" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//サウンド
	m_ps_Sound = ps_Sound;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_smallbird->TextureSet() );
	//グループの設定
	m_iGroup = GROUP_SMALLBIRD ;
	//座標の設定
	x = nibus_x;
	y = nibus_y;
	z = SMALLBIRD_Z;
	//当たりのコリジョン
	colx = SMALLBIRD_COLX ;
	coly = SMALLBIRD_COLY ;

	int kind = rand()%2;
	//どっち向きかを判断いて移動量を入れる
	if(kind == 0)
	{
		dx = SMALLBIRD_DX;
	}
	else
	{
		dx = -SMALLBIRD_DX;
	}
	dy = SMALLBIRD_DY;
	if(dx <= 0)
	{
		//RECTの指定
		SetRect(SMALLBIRD_RECT_LEFT_L,SMALLBIRD_RECT_TOP_L,SMALLBIRD_RECT_RIGHT_L,SMALLBIRD_RECT_BOTTOM_L);
	}
	else
	{
		//RECTの指定
		SetRect(SMALLBIRD_RECT_LEFT_R,SMALLBIRD_RECT_TOP_R,SMALLBIRD_RECT_RIGHT_R,SMALLBIRD_RECT_BOTTOM_R);
	}
	//線との当たり判定
	m_hit_line = false;

	//鳥の巣にあたっていいよ
	m_hit_nibus = false ;
	//飛ぶフラグ
	m_fly_flg = false ;
	//飛ぶスタートカウント
	m_fly_start_count = 0;
	//飛ぶ終わりカウント
	m_fly_end_count = 0;
	
	//パターン変更の設定
	m_iPtntimer_Max = 5 ;
	m_iPtntimer = 0 ;
	m_iPtn = 0 ;
	m_iPtninit = 0 ;
	m_iPtn_Right_Max = 96 ;
	m_iPtn_Max = 2 ;
	m_rectSize.right = SMALLBIRD_RECT_RIGHT_R ;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	//アルファ値の指定引数なしで255をセット
	SetAlpha();
	//SE再生
	SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotori_se);
	//ループしないで再生
	m_se->Play(FALSE);
};
/*======================================================

			小鳥のMain

=======================================================*/
void SmallBird::main() {
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		//動き
		Move();
		//跳ね返り
		Spring();
		//飛ぶ
		Fly();
	}
};
/*======================================================

			小鳥の動き

=======================================================*/
void SmallBird::Move() {

	//アニメーション
	PtnChange();

	//重力
	dy += SMALLBIRD_GRAVITY;

	//当たっていいよ
	if(y >= m_g_pCTaskCtrl->isGetBorderLine())
	{
		m_hit_nibus = true ;//鳥の巣
		if(z == SMALLBIRD_Z)
		{
			m_hit_line = true;//線
			z = SMALLBIRD_BORDER_Z;//鳥の巣より前に
		}
	}
	else if(y <= m_g_pCTaskCtrl->isGetBorderLine() && z == SMALLBIRD_BORDER_Z)
	{
		m_hit_line = true;//線
	}

	if(y >= m_g_pCTaskCtrl->isGetBorderLine() && m_hit_line == false)
	{
		m_fly_start_count = SMALLBIRD_FLY_COUNT_MAX;
	}
	//天井より上に行かせない
	if(y <= SMALLBIRD_HI_MAX)
	{
		y += dy;
		dy = 0;
		//飛ぶフラグ
		m_fly_flg = false ;
		//飛ぶスタートカウント
		m_fly_start_count = 0;
		//飛ぶ終わりカウント
		m_fly_end_count = 0;
	}
	//画面を超えたらデリート
	if(y >= HI_MAX)
	{
		//-600と表示
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER3);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT3);//スコアの減算
		m_g_pCTaskCtrl->SetLife(FALSE);//残機をマイナス
		Delete();//削除
	}
};
/*======================================================

			小鳥の跳ね返り

=======================================================*/
void SmallBird::Spring() {
	
	//端の壁に当たったら跳ね返る
	//左
	if( x < ( SMALLBIRD_LEFT_MAX + colx ))
	{
		x = SMALLBIRD_LEFT_MAX + colx;
		dx = -dx;
		Turn();
	}
	//右
	else if(x > ( SMALLBIRD_RIGHT_MAX - colx ))
	{
		x = SMALLBIRD_RIGHT_MAX - colx;
		dx = -dx;
		Turn();
	}
};
/*======================================================

			小鳥の当たり判定

=======================================================*/
void SmallBird::Hit(CTaskFunc* task) {
	
	switch(task->m_iGroup)
	{
		//線に当たったら
		case GROUP_LINE:
			if(m_hit_line)
			{
				LineHit(task);
			}
			break;
		case GROUP_NIBUAVIS:
			if(m_hit_nibus && z == SMALLBIRD_BORDER_Z)
			{
				NibusHit(task);
			}
			break;
	}
};
/*======================================================

			小鳥の当たり（線）判定

=======================================================*/
void SmallBird::LineHit(CTaskFunc* line) {

		
	if(this->y - this->coly < line->y - line->coly
		&& this->x > line->x - line->colx 
		&& this->x < line->x + line->colx)  
	{		
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//ループしないで再生
		m_se->Play(FALSE);
		m_hit_line = false ;
		m_linecount = m_g_pCTaskCtrl->isGetLineCount();
		//右上がり
		if(m_g_pCTaskCtrl->isGetLineTurn())
		{
			x -= E_DX;
			y -= dy;
			//卵が右に向かってる時
			if(dx >= 0)
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
			//卵が左に向かってる時
			else
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
		}
		//右下がり
		else
		{
			
			x += E_DX;
			y -= dy;
			
			//卵が右に向かってる時
			if(dx >= 0)
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
				
			}
			//卵が左に向かってる時
			else
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
				
			}
		}
		dy = -dy * 1.01f;
		Turn();
		
	}
	

};
/*======================================================

			小鳥の当たり（鳥の巣）判定

=======================================================*/
void SmallBird::NibusHit(CTaskFunc* nibus) {


	//小鳥の下に鳥の巣がある
	if(this->y - this->coly < nibus->y - nibus->coly
		&& this->x > nibus->x - nibus->colx 
		&& this->x < nibus->x + nibus->colx)  
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_in_se);
		//ループしないで再生
		m_se->Play(FALSE);
		new InPoint(m_pt_Texture , m_g_pCTaskCtrl , x , y ,m_linecount);
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER1);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT1 * m_g_pCTaskCtrl->isGetLinePoint(m_linecount));
		Delete();
	}
	//小鳥の上に鳥の巣がある
	else if(this->y + this->coly > nibus->y + nibus->coly
			&& this->x > nibus->x - nibus->colx 
			&& this->x < nibus->x + nibus->colx)  
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//ループしないで再生
		m_se->Play(FALSE);
		m_hit_nibus = false ;
		y += -dy;
		dy = 0;
		//飛ぶフラグ
		m_fly_flg = false ;
		//飛ぶスタートカウント
		m_fly_start_count = 0;
		//飛ぶ終わりカウント
		m_fly_end_count = 0;
	}

	//小鳥の右に鳥の巣がある
	if(this->x - this->colx < nibus->x - nibus->colx 
		&& this->y > nibus->y - nibus->coly 
		&& this->y < nibus->y + nibus->coly)
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//ループしないで再生
		m_se->Play(FALSE);
		//m_hit_nibus = false ;
		x -= dx;
		dx = dx * E;
	}
	//小鳥の左に鳥の巣がある
	else if(this->x + this->colx > nibus->x + nibus->colx
			&& this->y > nibus->y - nibus->coly 
			&& this->y < nibus->y + nibus->coly)
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotorihit_se);
		//ループしないで再生
		m_se->Play(FALSE);
		//m_hit_nibus = false ;
		x += dx;
		dx = dx * E;
	}
};
/*======================================================

			飛ぶ

=======================================================*/
void SmallBird::Fly() {

	if(m_fly_flg)
	{
		if(dy >= 0)
		{
			dy -= 3.0f;
		}

		m_fly_end_count++;

		if(m_fly_end_count >= SMALLBIRD_FLY_COUNT_MAX)
		{
			dy = 0;
			m_fly_flg = false;
			m_fly_end_count = 0;
		}

	}
	else
	{
		m_fly_start_count ++;
		if(m_fly_start_count >= SMALLBIRD_FLY_COUNT_MAX)
		{
			m_hit_nibus = true ;
			m_fly_flg = true;
			m_fly_start_count = 0;
			
		}
	}
};
/*======================================================

			向き

=======================================================*/
void SmallBird::Turn() {

	if( dx > 0)
	{
		//向きを右に
		SetRect(SMALLBIRD_RECT_LEFT_R,SMALLBIRD_RECT_TOP_R,SMALLBIRD_RECT_RIGHT_R,SMALLBIRD_RECT_BOTTOM_R);
		m_iPtntimer = 0 ;
		m_iPtn = 0 ;
		m_iPtninit = 0 ;
	}
	else if( dx < 0)
	{
		//向きを左に
		SetRect(SMALLBIRD_RECT_LEFT_L,SMALLBIRD_RECT_TOP_L,SMALLBIRD_RECT_RIGHT_L,SMALLBIRD_RECT_BOTTOM_L);
		m_iPtntimer = 0 ;
		m_iPtn = 0 ;
		m_iPtninit = 0 ;
	}
};