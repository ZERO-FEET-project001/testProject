#include "TaskFuncs.h"


/*------------------------------------------------------

				タイトルのキャラクター

------------------------------------------------------*/
/*======================================================

			タイトルのキャラクターのコンストラクタ

=======================================================*/
CharacterTitle::CharacterTitle(SetTexture* pt_Texture , CTaskCtrl* g_pCTaskCtrl,POINT* Mpt,DxInput *pDxi,SetSound* ps_Sound) {

	// タスクのフラグセット
	setTaskFlag( TASK_FLAG_OBJECT) ;
	//NAME設定
	m_cpName = "CharacterTitle" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//画像のポインタ
	m_pt_Texture = pt_Texture ;
	//サウンド
	m_ps_Sound = ps_Sound;
	m_kind= CHARACTERTITLE_RAND;
	m_Mpt = Mpt ;
	m_pDxi = pDxi ;
	switch(m_kind)
	{
		case 0:
			//Textureのセットを行う
			GetTexture( pt_Texture->m_pg_egg->TextureSet() );
			//RECTの指定
			SetRect(EGG_RECT_LEFT,EGG_RECT_TOP,EGG_RECT_RIGHT,EGG_RECT_BOTTOM);
			break;
		default:
			//Textureのセットを行う
			GetTexture( pt_Texture->m_pg_smallbird->TextureSet() );
			//RECTの指定
			SetRect(SMALLBIRD_RECT_LEFT_R,SMALLBIRD_RECT_TOP_R,SMALLBIRD_RECT_RIGHT_R,SMALLBIRD_RECT_BOTTOM_R);

			break;
	}


	//座標の設定
	x = CHARACTERTITLE_X;
	y = CHARACTERTITLE_Y;
	z = CHARACTERTITLE_Z;

	dx = CHARACTERTITLE_DX;
	
	colx = SMALLBIRD_RECT_RIGHT_R;
	coly = SMALLBIRD_RECT_BOTTOM_R;

	//パターン変更の設定
	m_iPtntimer_Max = 5 ;
	m_iPtntimer = 0 ;
	m_iPtn = 0 ;
	m_iPtninit = 0 ;
	m_iPtn_Right_Max = 96 ;
	m_iPtn_Max = 2 ;
	m_rectSize.right = SMALLBIRD_RECT_RIGHT_R ;

	//自分が存在するゲームモードの設定
	m_iMode = GAME_TITLE;

	//アルファ値の指定引数なしで255をセット
	SetAlpha();

};
/*======================================================

			タイトルのキャラクターのMain

=======================================================*/
void CharacterTitle::main() {
	ModeDelete(m_g_pCTaskCtrl);
	//動き
	Move();
	switch(m_kind)
	{
		case 0:
			MouseHitEgg();
			break;
		default:
			MouseHitBird();
			break;
	}
	
};
/*======================================================

			タイトルのキャラクターの動き

=======================================================*/
void CharacterTitle::Move() {
	if(m_kind != 0)
	{
		PtnChange();
	}
	else if (m_kind == 0) 
	{
		//回転
		m_rotate += CHARACTERTITLE_ROTATE ;
	}
	if(x > ( WID_MAX + colx ))
	{
		Delete();
	}
};
/*======================================================

			タイトルのキャラクターにマウスでクリックすると（小鳥）

=======================================================*/
void CharacterTitle::MouseHitBird() {

	if(m_Mpt->x > (this->x - this->colx) && m_Mpt->x < (this->x + this->colx) 
		&& m_Mpt->y > (this->y - this->coly) && m_Mpt->y < (this->y + this->coly) && m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_kotori_se);
		//ループしないで再生
		m_se->Play(FALSE);
		dy = -3;
	}
};
/*======================================================

			タイトルのキャラクターにマウスでクリックすると（卵）

=======================================================*/
void CharacterTitle::MouseHitEgg() {

	if(m_Mpt->x > (this->x - this->colx) && m_Mpt->x < (this->x + this->colx) 
		&& m_Mpt->y > (this->y - this->coly) && m_Mpt->y < (this->y + this->coly) && m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
	{
		//SE再生
		SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_eggbreak_se);
		//ループしないで再生
		m_se->Play(FALSE);
		Delete();
		for(int i=0 ; i < EGGSHELL_MAX ; i++)
		{
			//卵の殻
			new EggShell(m_pt_Texture , m_g_pCTaskCtrl , x , y , GAME_TITLE);
		}
	}
};
