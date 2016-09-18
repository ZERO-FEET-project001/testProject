#include "TaskFuncs.h"

SetSound::SetSound(){
	//BGM
	m_title_bgm = new DxSound(_T("Sound/Title_BGM.wav"));//タイトルBGM
	m_main_bgm = new DxSound(_T("Sound/GameMain_BGM.wav"));//タイトルBGM
	m_gameover_bgm = new DxSound(_T("Sound/GameOver_BGM.wav"));//ゲームオーバーBGM
	//SE
	m_kotori_se = new DxSound(_T("Sound/kotori_SE.wav"));//小鳥SE
	m_corsor_se = new DxSound(_T("Sound/cursormove_SE.wav"));//カーソルSE
	m_corsor_ok_se = new DxSound(_T("Sound/cousor_ok_SE.wav"));//カーソル決定音SE
	m_egg_se = new DxSound(_T("Sound/eggbutukaru_SE.wav"));//卵SE
	m_eggbreak_se = new DxSound(_T("Sound/eggwareru_SE.wav"));//卵割れるSE
	m_start_se = new DxSound(_T("Sound/start_SE.wav"));//スタートSE
	m_in_se  = new DxSound(_T("Sound/in_SE.wav"));//入った時のSE
	m_kotorihit_se = new DxSound(_T("Sound/kotorihaneru_SE.wav"));//小鳥が跳ね返るのSE
	m_batu_se = new DxSound(_T("Sound/batu_SE.wav"));//小鳥が落ちた時のSE
	m_swing_se = new DxSound(_T("Sound/swing_SE.wav"));//鳥の巣が揺れるSE

};
void SetSound::main(){

};