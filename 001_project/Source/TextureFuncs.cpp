#include "TaskFuncs.h"

/*------------------------------------------------------

				Texture Task

------------------------------------------------------*/
/*======================================================

			TextureFuncs�̃R���X�g���N�^

=======================================================*/
TextureFuncs::TextureFuncs(LPCTSTR filename) {

	// ����������
	setTaskFlag( TASK_FLAG_ENABLE | TASK_FLAG_TEX) ;
	//�t�@�C�����̊i�[
	m_cpName = (char*)filename ;
	//����𑗂�
	Texture(filename) ;

};
/*======================================================

			TextureFuncs��Main

=======================================================*/
void TextureFuncs::main(){

};
