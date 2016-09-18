#include "TaskFuncs.h"
#include <math.h> 

/*========================================================

				ScoreControl

========================================================*/

class GamePoseControl {

	//キーボードポインタの保持
	DxInput* m_pDxi;
	//タスクコントロールのポインタの保持
	CTaskCtrl*	m_g_pCTaskCtrl;
	//音楽用ポインタの保持
	SetSound* m_ps_Sound ;
	//画像用ポインタの保持
	SetTexture* m_pt_Texture ;
	//マウスのポインターセット
	POINT* m_Mpt;

public:

	//コンストラクタ
	GamePoseControl(CTaskCtrl* g_pCTaskCtrl,SetTexture* pt_Texture ,DxInput* pDxi,POINT* Mpt,SetSound* ps_Sound);
	//main関数
	void	main();
};

