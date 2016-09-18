#include "TaskFuncs.h"

/*------------------------------------------------------

				カーソル

------------------------------------------------------*/
/*======================================================

			カーソルのコンストラクタ

=======================================================*/
Cursor::Cursor(SetTexture* pt_Texture ,CTaskCtrl* g_pCTaskCtrl ,POINT* Mpt , DxInput* pDxi,int kind, BOOL starting_flg,SetSound* ps_Sound) {

	// 初期化処理
	setTaskFlag( TASK_FLAG_OBJECT) ;

	//NAME設定
	m_cpName = "Cursor" ;
	//タスクコントロールのポインタ
	m_g_pCTaskCtrl = g_pCTaskCtrl;
	//サウンド
	m_ps_Sound = ps_Sound;
	//Textureのセットを行う
	GetTexture( pt_Texture->m_pg_cursor->TextureSet() );

	//RECTの指定
	SetRect(0,0,76,60);

	m_Mpt = Mpt;

	m_pDxi = pDxi;

	//初期位置の指定
	x = -100;
	y = -100 ;
	z =  0.0f;

	m_iPtntimer_Max = 5  ;//RECT切り替え時間の最大
	m_iPtntimer = 0 ;//RECTの切り替え時間
	m_iPtn = 0 ;//現在の画像のパターン番号
	m_iPtn_Max = 3 ;//最大の画像のパターン番号
	m_rectSize.right = 76;//変更RECT
	m_iPtn_Right_Max = 225;

	m_iMode = kind ;
	m_starting_flg = starting_flg ;
	//アルファ値の指定引数なしで255をセット
	if(m_starting_flg)
	{
		SetAlpha();
	}
};
/*======================================================

			カーソルのMain

=======================================================*/
void Cursor::main() {
	if(!m_starting_flg)
	{
		ModeNew(m_g_pCTaskCtrl,TRUE);
	}
	ModeDelete(m_g_pCTaskCtrl);
	Animation();
	PointChange();

};
/*======================================================

			カーソルのアニメーション

=======================================================*/
void Cursor::Animation() {
	PtnChange();
};
/*======================================================

			カーソルの座標の変更

=======================================================*/
void Cursor::PointChange() {

	//ゲーム中の画面だったら
	if(m_g_pCTaskCtrl->isGetGameMode() == GAME_MAIN)
	{
		if(m_Mpt->x >= 235 && m_Mpt->x <= 525 && m_Mpt->y >= 245 && m_Mpt->y <= 285)
		{
			x = 200 ;
			y = 250 ;
			if(m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
			{
				//SE再生
				SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_corsor_ok_se);
				//ループしないで再生
				m_se->Play(FALSE);
				Delete();
			}
		}
		else if(m_Mpt->x >= 220 && m_Mpt->x <= 550 && m_Mpt->y >= 365 && m_Mpt->y <= 400)
		{
			x = 180 ;
			y = 380 ;
			if(m_pDxi->isMouseTrigger(DXI_MOUSE_LEFT))
			{
				//SE再生
				SoundFuncs * m_se = new SoundFuncs(m_ps_Sound->m_corsor_ok_se);
				//ループしないで再生
				m_se->Play(FALSE);
				Delete();
			}
		}
	}
	//ゲーム中の画面だったら
	else if(m_g_pCTaskCtrl->isGetGameMode() == GAME_TITLE)
	{
		if(m_Mpt->x >= 280 && m_Mpt->x <= 490 && m_Mpt->y >= 320 && m_Mpt->y <= 365)
		{
			x = 250 ;
			y = 340 ;
		}
		else if(m_Mpt->x >= 280 && m_Mpt->x <= 490 && m_Mpt->y >= 390 && m_Mpt->y <= 440)
		{
			x = 250 ;
			y = 410 ;
		}	
	}
};
