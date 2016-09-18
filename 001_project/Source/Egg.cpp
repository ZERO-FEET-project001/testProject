#include "TaskFuncs.h"


/*------------------------------------------------------

				鳥の卵

------------------------------------------------------*/
/*======================================================

			鳥の卵のコンストラクタ

=======================================================*/
Egg::Egg(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl, float nibus_x ,float nibus_y,SetSound* ps_Sound) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT  | TASK_FLAG_COL_PSV | TASK_FLAG_COL_ACT ) ;
	//NAME設定
	m_cpName = "EGG" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_egg->TextureSet() );
	//サウンド
	m_ps_Sound = ps_Sound;
	//グループの設定
	m_iGroup = GROUP_EGG ;
	//RECTの指定
	SetRect(EGG_RECT_LEFT,EGG_RECT_TOP,EGG_RECT_RIGHT,EGG_RECT_BOTTOM);
	//座標の設定
	x = nibus_x;
	y = nibus_y;
	z = EGG_Z;
	//当たりのコリジョン
	colx = EGG_COLX ;
	coly = EGG_COLY ;

	int kind = rand()%2;
	//どっち向きかを判断いて移動量を入れる
	if(kind == 0)
	{
		dx = EGG_DX;
	}
	else
	{
		dx = -EGG_DX;
	}
	dy = EGG_DY;

	//線との当たり判定
	m_hit_line = false;

	//卵のライフ
	m_life = EGG_LIFE_MAX;

	//鳥の巣にあたっていいよ
	m_hit_nibus = false ;

	//卵が孵化をするカウント
	m_smallbird_count = 0;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_MAIN;

	m_linecount = 0;
	//アルファ値の指定引数なしで255をセット
	SetAlpha();

};
/*======================================================

			鳥の卵のMain

=======================================================*/
void Egg::main() {
	ModeDelete(m_g_pCTaskCtrl);
	if(!m_g_pCTaskCtrl->isGetGamePose())
	{
		//動き
		Move();
		//跳ね返り
		Spring();
		//亀裂
		EggSplit();
	}
};
/*======================================================

			鳥の卵の動き

=======================================================*/
void Egg::Move() {

	//当たっていいよ

	if(y >= m_g_pCTaskCtrl->isGetBorderLine())
	{
		m_hit_nibus = true ;//鳥の巣
		if(z == EGG_Z)
		{
			m_hit_line = true;//線
			z = EGG_BORDER_Z;//鳥の巣より前に
		}
	}
	else if(y <= m_g_pCTaskCtrl->isGetBorderLine() && z == EGG_BORDER_Z)
	{
		m_hit_line = true;//線
	}

	//重力
	dy += GRAVITY;

	//回転
	m_rotate += EGG_RORATE ;

	//孵化
	if(m_smallbird_count >= 5)
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_eggbreak_se);
		//ループしないで再生
		m_se->Play(FALSE);
		//削除
		Delete();
		for(int i=0 ; i < EGGSHELL_MAX ; i++)
		{
			//卵の殻
			new EggShell(m_pt_Texture , m_g_pCTaskCtrl , x , y , GAME_MAIN);
		}

		//卵が孵化をする
		new SmallBird(m_pt_Texture , m_g_pCTaskCtrl , x ,y,m_ps_Sound);
	}

	//画面を超えたらデリート
	if(y >= HI_MAX)
	{
		//－200と表示
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER2);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT2);//スコア減算
		Delete();//削除
	}
};
/*======================================================

			鳥の卵の跳ね返り

=======================================================*/
void Egg::Spring() {
	
	//端の壁に当たったら跳ね返る
	//左
	if( x < ( EGG_LEFT_MAX + colx ))
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//ループしないで再生
		m_se->Play(FALSE);
		x = EGG_LEFT_MAX + colx;
		dx = -dx;
		m_life--;
	}
	//右
	else if(x > ( EGG_RIGHT_MAX - colx ))
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//ループしないで再生
		m_se->Play(FALSE);
		x = EGG_RIGHT_MAX - colx;
		dx = -dx;
		m_life--;
	}
};
/*======================================================

			鳥の卵の当たり判定

=======================================================*/
void Egg::Hit(CTaskFunc* task) {
	
	switch(task->m_iGroup)
	{
		//線に当たったら
		case GROUP_LINE:
			if(m_hit_line)
			{
				LineHit(task);
			}
			break;
		//鳥の巣に当たったら
		case GROUP_NIBUAVIS:
			if(m_hit_nibus)
			{
				NibusHit(task);
			}
			break;
	}
};
/*======================================================

			鳥の卵の当たり（線）判定

=======================================================*/
void Egg::LineHit(CTaskFunc* line) {

		
	if(this->y - this->coly < line->y - line->coly
		&& this->x > line->x - line->colx 
		&& this->x < line->x + line->colx)  
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//ループしないで再生
		m_se->Play(FALSE);
		m_hit_line = false ;
		m_linecount = m_g_pCTaskCtrl->isGetLineCount();
		//右上がり
		if(m_g_pCTaskCtrl->isGetLineTurn())
		{
			x = x - E_DX;
			y = y - dy;
			//卵が右に向かってる時
			if(dx >= 0)
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
			//卵が左に向かってる時
			else if(dx < 0)
			{
				dx = -dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
		}
		//右下がり
		else
		{
			x = x + E_DX;
			y = y - dy;
			
			//卵が右に向かってる時
			if(dx >= 0)
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
				
			}
			//卵が左に向かってる時
			else if(dx < 0)
			{
				dx = dy * sin(m_g_pCTaskCtrl->isGetLineRadian());
			}
		}

		//当たったら高く飛ばす！
		dy = -dy * 1.03f;
		//孵化へのカウントダウン
		m_smallbird_count++;
		
	}
	

};
/*======================================================

			鳥の卵の当たり（鳥の巣）判定

=======================================================*/
void Egg::NibusHit(CTaskFunc* nibus) {

	//卵の下に鳥の巣がある
	if(this->y - this->coly < nibus->y - nibus->coly
		&& this->x > nibus->x - nibus->colx 
		&& this->x < nibus->x + nibus->colx)  
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_in_se);
		//ループしないで再生
		m_se->Play(FALSE);
		new InPoint(m_pt_Texture , m_g_pCTaskCtrl , x , y ,m_linecount);
		new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER0);
		m_g_pCTaskCtrl->SetScore(SCOREPOINT0 * m_g_pCTaskCtrl->isGetLinePoint(m_linecount));
		Delete();
	}
	//卵の上に鳥の巣がある
	else if(this->y + this->coly > nibus->y + nibus->coly
			&& this->x > nibus->x - nibus->colx 
			&& this->x < nibus->x + nibus->colx)  
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//ループしないで再生
		m_se->Play(FALSE);
		m_hit_nibus = false ;
		if(dy <= 0)
		{
			y += -dy;
			dy = 0;
		}
	}

	//卵の右に鳥の巣がある
	if(this->x - this->colx - 32< nibus->x - nibus->colx 
		&& this->y > nibus->y - nibus->coly 
		&& this->y < nibus->y + nibus->coly)
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//ループしないで再生
		m_se->Play(FALSE);
		x -= dx;
		dx = -(dx * E);
	}
	//卵の左に鳥の巣がある
	else if(this->x + this->colx + 32 > nibus->x + nibus->colx
			&& this->y > nibus->y - nibus->coly 
			&& this->y < nibus->y + nibus->coly)
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_egg_se);
		//ループしないで再生
		m_se->Play(FALSE);
		x += dx;
		dx = -(dx * E);
	}
};
/*======================================================

			鳥の卵の亀裂

=======================================================*/
void Egg::EggSplit() {

	switch(m_life)
	{
		case 2:
			//RECTの指定
			SetRect(32,0,64,32);
			break;
		case 1:
			//RECTの指定
			SetRect(64,0,96,32);

			break;
		case 0:
			//削除
			Delete();
			//スコアをマイナス
			new ScoreLetter(m_pt_Texture , m_g_pCTaskCtrl , SCORELETTER2);
			m_g_pCTaskCtrl->SetScore(SCOREPOINT2);
			//SE再生
			SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_eggbreak_se);
			//ループしないで再生
			m_se->Play(FALSE);
			//殻をいっぱい出す
			for(int i=0 ; i < EGGSHELL_MAX ; i++)
			{
				new EggShell(m_pt_Texture , m_g_pCTaskCtrl , x , y ,GAME_MAIN);
			}
			break;
	}
};