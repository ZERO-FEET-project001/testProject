#include "TaskFuncs.h"

SetSound::SetSound(){
	//BGM
	m_title_bgm = new DxSound(_T("Sound/Title_BGM.wav"));//�^�C�g��BGM
	m_main_bgm = new DxSound(_T("Sound/GameMain_BGM.wav"));//�^�C�g��BGM
	m_gameover_bgm = new DxSound(_T("Sound/GameOver_BGM.wav"));//�Q�[���I�[�o�[BGM
	//SE
	m_kotori_se = new DxSound(_T("Sound/kotori_SE.wav"));//����SE
	m_corsor_se = new DxSound(_T("Sound/cursormove_SE.wav"));//�J�[�\��SE
	m_corsor_ok_se = new DxSound(_T("Sound/cousor_ok_SE.wav"));//�J�[�\�����艹SE
	m_egg_se = new DxSound(_T("Sound/eggbutukaru_SE.wav"));//��SE
	m_eggbreak_se = new DxSound(_T("Sound/eggwareru_SE.wav"));//�������SE
	m_start_se = new DxSound(_T("Sound/start_SE.wav"));//�X�^�[�gSE
	m_in_se  = new DxSound(_T("Sound/in_SE.wav"));//����������SE
	m_kotorihit_se = new DxSound(_T("Sound/kotorihaneru_SE.wav"));//���������˕Ԃ��SE
	m_batu_se = new DxSound(_T("Sound/batu_SE.wav"));//����������������SE
	m_swing_se = new DxSound(_T("Sound/swing_SE.wav"));//���̑����h���SE

};
void SetSound::main(){

};