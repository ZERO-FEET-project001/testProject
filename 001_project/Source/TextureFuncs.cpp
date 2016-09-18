#include "TaskFuncs.h"

/*------------------------------------------------------

				Texture Task

------------------------------------------------------*/
/*======================================================

			TextureFuncsのコンストラクタ

=======================================================*/
TextureFuncs::TextureFuncs(LPCTSTR filename) {

	// 初期化処理
	setTaskFlag( TASK_FLAG_ENABLE | TASK_FLAG_TEX) ;
	//ファイル名の格納
	m_cpName = (char*)filename ;
	//それを送る
	Texture(filename) ;

};
/*======================================================

			TextureFuncsのMain

=======================================================*/
void TextureFuncs::main(){

};
