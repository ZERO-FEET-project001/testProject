#include "TaskFuncs.h"

SetTexture::SetTexture(){

	//画像のセット
	m_pg_bg = new TextureFuncs(_T("Images/bg.png"));//背景
	m_pg_line = new TextureFuncs(_T("Images/circle.png"));//線
	m_pg_nibu = new TextureFuncs(_T("Images/nibusavis.png"));//鳥の巣
	m_pg_egg = new TextureFuncs(_T("Images/egg.png"));//卵
	m_pg_eggshell = new TextureFuncs(_T("Images/eggshell.png"));//卵の殻
	m_pg_smallbird =new TextureFuncs(_T("Images/smallbird.png"));//小鳥
	m_pg_point =new TextureFuncs(_T("Images/Point.png"));//入った時のポイント
	m_pg_scorenumber =new TextureFuncs(_T("Images/number.png"));//数字
	m_pg_life = new TextureFuncs(_T("Images/life.png"));//残機
	m_pg_cross = new TextureFuncs(_T("Images/batu.png"));//バツ
	m_pg_pose = new TextureFuncs(_T("Images/pose.png"));//ポーズ
	m_pg_cursor = new TextureFuncs(_T("Images/corsor.png"));//カーソル
	m_pg_title = new TextureFuncs(_T("Images/title.png"));//タイトル
	m_pg_black = new TextureFuncs(_T("Images/black.png"));//黒
	m_pg_border = new TextureFuncs(_T("Images/border.png"));//境界線
	m_pg_gameover = new TextureFuncs(_T("Images/Gameover.png"));//ゲームオーバー
	m_pg_char = new TextureFuncs(_T("Images/Char.png"));//文字
	m_pg_start =  new TextureFuncs(_T("Images/Start.png"));//スタート文字
};
void SetTexture::main(){

};