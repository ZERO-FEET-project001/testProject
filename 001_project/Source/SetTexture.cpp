#include "TaskFuncs.h"

SetTexture::SetTexture(){

	//�摜�̃Z�b�g
	m_pg_bg = new TextureFuncs(_T("Images/bg.png"));//�w�i
	m_pg_line = new TextureFuncs(_T("Images/circle.png"));//��
	m_pg_nibu = new TextureFuncs(_T("Images/nibusavis.png"));//���̑�
	m_pg_egg = new TextureFuncs(_T("Images/egg.png"));//��
	m_pg_eggshell = new TextureFuncs(_T("Images/eggshell.png"));//���̊k
	m_pg_smallbird =new TextureFuncs(_T("Images/smallbird.png"));//����
	m_pg_point =new TextureFuncs(_T("Images/Point.png"));//���������̃|�C���g
	m_pg_scorenumber =new TextureFuncs(_T("Images/number.png"));//����
	m_pg_life = new TextureFuncs(_T("Images/life.png"));//�c�@
	m_pg_cross = new TextureFuncs(_T("Images/batu.png"));//�o�c
	m_pg_pose = new TextureFuncs(_T("Images/pose.png"));//�|�[�Y
	m_pg_cursor = new TextureFuncs(_T("Images/corsor.png"));//�J�[�\��
	m_pg_title = new TextureFuncs(_T("Images/title.png"));//�^�C�g��
	m_pg_black = new TextureFuncs(_T("Images/black.png"));//��
	m_pg_border = new TextureFuncs(_T("Images/border.png"));//���E��
	m_pg_gameover = new TextureFuncs(_T("Images/Gameover.png"));//�Q�[���I�[�o�[
	m_pg_char = new TextureFuncs(_T("Images/Char.png"));//����
	m_pg_start =  new TextureFuncs(_T("Images/Start.png"));//�X�^�[�g����
};
void SetTexture::main(){

};